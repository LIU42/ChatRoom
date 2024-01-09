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
    shutdown(listen_socket, SHUT_RDWR);
    close(listen_socket);

    for (chatroom_thread* client_thread_ptr : client_thread_pool)
    {
        delete client_thread_ptr;
    }
    fprintf(stdout, "(System) Server end.\n");
}

int chatroom_server::consult_username(chatroom_thread* thread_ptr, string& receive_name)
{
    int consult_result = -1;
    username_mutex.lock();

    if (online_usernames.find(receive_name) == online_usernames.end())
    {
        consult_result = 0;
        online_usernames.emplace(receive_name);
        thread_ptr->username = receive_name;
    }
    username_mutex.unlock();
    return consult_result;
}

void chatroom_server::remove_client(chatroom_thread* thread_ptr)
{
    close(thread_ptr->client_socket);
    sockets_mutex.lock();
    online_sockets.erase(thread_ptr->client_socket);
    sockets_mutex.unlock();
    username_mutex.lock();
    online_usernames.erase(thread_ptr->username);
    username_mutex.unlock();
}

void chatroom_server::broadcast(chatroom_thread* thread_ptr, string message)
{
    sockets_mutex.lock();

    for (int client_socket : online_sockets)
    {
        if (client_socket != thread_ptr->client_socket && send(client_socket, message.data(), message.length(), 0) == -1)
        {
            shutdown(client_socket, SHUT_RDWR);
            close(client_socket);
        }
    }
    sockets_mutex.unlock();
    fprintf(stdout, "%s:%d %s\n", inet_ntoa(thread_ptr->client_addr.sin_addr), thread_ptr->client_addr.sin_port, message.data());
}

int chatroom_server::run_server()
{
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
        client_thread_pool.emplace_back(new chatroom_thread(this, accept_socket, client_addr));

        sockets_mutex.lock();
        online_sockets.emplace(accept_socket);
        sockets_mutex.unlock();

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

    if (connect_thread_ptr->joinable())
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
    server_ptr->remove_client(this);
}

void chatroom_thread::receive_handler()
{
    if (username.length() > 0)
    {
        server_ptr->broadcast(this, username + ": " + receive_string);
        return;
    }
    if (server_ptr->consult_username(this, receive_string) == 0)
    {
        server_ptr->broadcast(this, username + " joined.");
        send(client_socket, ACCEPT_FLAG, FLAG_LENGTH, 0);
        return;
    }
    send(client_socket, REFUSE_FLAG, FLAG_LENGTH, 0);
}
