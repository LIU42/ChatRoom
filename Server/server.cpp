#include "server.h"

chatroom_server::chatroom_server()
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == -1)
    {
        fprintf(stderr, "(System) Socket error: %s.\n", strerror(errno));
        return;
    }
    bzero(&server_addr, sizeof(sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(listen_socket, (sockaddr*)&server_addr, sizeof(sockaddr)) == -1)
    {
        fprintf(stderr, "(System) Bind error: %s.\n", strerror(errno));
        return;
    }
    fprintf(stdout, "(System) Server initialize success.\n");
}

chatroom_server::~chatroom_server()
{
    is_server_running = false;

    shutdown(listen_socket, SHUT_RDWR);
    close(listen_socket);

    if (garbage_collection_thread_ptr != nullptr && garbage_collection_thread_ptr->joinable())
    {
        garbage_collection_thread_ptr->join();
    }
    delete garbage_collection_thread_ptr;

    for (auto client_thread_pair : client_thread_pool)
    {
        delete client_thread_pair.second;
    }
    fprintf(stdout, "(System) Server end.\n");
}

void chatroom_server::garbage_collection()
{
    is_server_running = true;

    while (is_server_running)
    {
        threads_mutex.lock();
        sockets_mutex.lock();

        for (int offline_socket : offline_sockets)
        {
            delete client_thread_pool[offline_socket];
            client_thread_pool.erase(offline_socket);
        }
        offline_sockets.clear();
        threads_mutex.unlock();
        sockets_mutex.unlock();
        sleep(GARBAGE_COLLECTION_DELAY);
    }
}

consult_result chatroom_server::consult_username(chatroom_thread* thread_ptr, string& receive_name)
{
    if (receive_name.length() <= 0 || receive_name.find(' ') != receive_name.npos)
    {
        return consult_result::RESULT_INVALID;
    }
    username_mutex.lock();

    if (online_usernames.find(receive_name) != online_usernames.end())
    {
        username_mutex.unlock();
        return consult_result::RESULT_REPEAT;
    }
    online_usernames.emplace(receive_name);
    username_mutex.unlock();
    sockets_mutex.lock();
    online_sockets.emplace(thread_ptr->client_socket);
    sockets_mutex.unlock();
    thread_ptr->username = receive_name;
    return consult_result::RESULT_ACCEPT;
}

void chatroom_server::remove_client(chatroom_thread* thread_ptr)
{
    close(thread_ptr->client_socket);
    sockets_mutex.lock();
    online_sockets.erase(thread_ptr->client_socket);
    offline_sockets.emplace(thread_ptr->client_socket);
    sockets_mutex.unlock();
    username_mutex.lock();
    online_usernames.erase(thread_ptr->username);
    username_mutex.unlock();
}

void chatroom_server::broadcast_message(chatroom_thread* thread_ptr, string message)
{
    sockets_mutex.lock();

    for (auto client_socket_iter = online_sockets.begin(); client_socket_iter != online_sockets.end();)
    {
        if (*client_socket_iter != thread_ptr->client_socket)
        {
            if (send(*client_socket_iter, (USER_MESSAGE_PREFIX + message).data(), message.length() + 1, 0) == -1)
            {
                offline_sockets.emplace(*client_socket_iter);
                client_socket_iter = online_sockets.erase(client_socket_iter);
                continue;
            }
        }
        ++client_socket_iter;
    }
    sockets_mutex.unlock();
    fprintf(stdout, "%s:%d %s\n", inet_ntoa(thread_ptr->client_addr.sin_addr), thread_ptr->client_addr.sin_port, message.data());
}

void chatroom_server::broadcast_online_user_count()
{
    sockets_mutex.lock();
    snprintf(online_count_buffer, BUFFER_SIZE, "#%d", (int)online_sockets.size());

    for (int client_socket : online_sockets)
    {
        send(client_socket, online_count_buffer, strlen(online_count_buffer), 0);
    }
    fprintf(stdout, "(System) Current online users: %d.\n", (int)online_sockets.size());
    sockets_mutex.unlock();
}

int chatroom_server::run_server()
{
    garbage_collection_thread_ptr = new thread(&chatroom_server::garbage_collection, this);

    if (listen(listen_socket, QUEUE_LENGTH) == -1)
    {
        fprintf(stderr, "(System) Listen error: %s.\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(System) Server listening at %d.\n", SERVER_PORT);
    addr_length = sizeof(sockaddr);

    while (true)
    {
        accept_socket = accept(listen_socket, (sockaddr*)&client_addr, &addr_length);

        if (accept_socket == -1)
        {
            fprintf(stderr, "(System) Accept error: %s.\n", strerror(errno));
            break;
        }
        threads_mutex.lock();
        client_thread_pool[accept_socket] = new chatroom_thread(this, accept_socket, client_addr);
        threads_mutex.unlock();

        fprintf(stdout, "(System) %s:%d connected.\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
    }
    fprintf(stdout, "(System) Server listening end\n");
    return 0;
}

chatroom_thread::chatroom_thread(chatroom_server* server_ptr, int client_socket, sockaddr_in client_addr)
{
    this->server_ptr = server_ptr;
    this->client_socket = client_socket;
    this->client_addr = client_addr;
    this->connect_thread_ptr = new thread(&chatroom_thread::connection_handler, this);
}

chatroom_thread::~chatroom_thread()
{
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);

    if (connect_thread_ptr != nullptr && connect_thread_ptr->joinable())
    {
        connect_thread_ptr->join();
    }
    delete connect_thread_ptr;
}

void chatroom_thread::connection_handler()
{
    while (true)
    {
        receive_length = recv(client_socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            fprintf(stdout, "(System) %s:%d disconnect.\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
            break;
        }
        if (receive_length == -1)
        {
            fprintf(stderr, "(System) %s:%d %s.\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port, strerror(errno));
            break;
        }
        receive_buffer[receive_length] = '\0';
        receive_string = receive_buffer;
        receive_handler();
    }
    server_ptr->broadcast_message(this, username + " left.");
    server_ptr->remove_client(this);
    server_ptr->broadcast_online_user_count();
}

void chatroom_thread::receive_handler()
{
    if (username.length() > 0 && receive_string.length() > 0)
    {
        if (receive_string[0] == chatroom_server::ONLINE_COUNT_PREFIX)
        {
            server_ptr->broadcast_online_user_count();
        }
        else if (receive_string[0] == chatroom_server::USER_MESSAGE_PREFIX)
        {
            server_ptr->broadcast_message(this, username + ": " + receive_string.substr(1));
        }
        return;
    }
    consult_result consult_username_result = server_ptr->consult_username(this, receive_string);

    if (consult_username_result == consult_result::RESULT_ACCEPT)
    {
        server_ptr->broadcast_message(this, username + " joined.");
        send(client_socket, ACCEPT_RESPONSE, RESPONSE_LENGTH, 0);
    }
    else if (consult_username_result == consult_result::RESULT_REPEAT)
    {
        send(client_socket, REPEAT_RESPONSE, RESPONSE_LENGTH, 0);
    }
    else if (consult_username_result == consult_result::RESULT_INVALID)
    {
        send(client_socket, INVALID_RESPONSE, RESPONSE_LENGTH, 0);
    }
}
