#include "server.h"

chatroom_server::chatroom_server()
{
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_socket == -1)
    {
        fprintf(stderr, "(System) Socket Error: %s\n", strerror(errno));
        return;
    }
    bzero(&server_addr, sizeof(sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(listen_socket, (sockaddr*)&server_addr, sizeof(sockaddr)) == -1)
    {
        fprintf(stderr, "(System) Bind Error: %s\n", strerror(errno));
        return;
    }
    fprintf(stdout, "(System) Server Initialize Success\n");
}

chatroom_server::~chatroom_server()
{
    sockets_mutex.lock();

    for (int client_socket : client_sockets)
    {
        shutdown(client_socket, SHUT_RDWR);
        close(client_socket);
    }
    sockets_mutex.unlock();
    close(listen_socket);

    for (thread& client_thread : client_thread_pool)
    {
        if (client_thread.joinable())
        {
            client_thread.join();
        }
    }
    fprintf(stdout, "(System) Server End\n");
}

void chatroom_server::connection_handler(client_info client)
{
    char receive_buffer[BUFFER_SIZE];
    int receive_length = 0;

    while (true)
    {
        receive_length = recv(client.socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            fprintf(stdout, "(System) %s:%d Disconnect\n", inet_ntoa(client.addr.sin_addr), client.addr.sin_port);
            break;
        }
        if (receive_length == -1)
        {
            fprintf(stderr, "(System) %s:%d %s\n", inet_ntoa(client.addr.sin_addr), client.addr.sin_port, strerror(errno));
            break;
        }
        receive_buffer[receive_length] = '\0';
        receive_handler(client, string(receive_buffer));
    }
    remove_client(client);
}

void chatroom_server::receive_handler(client_info& client, string receive_string)
{
    if (client.username.length() > 0)
    {
        broadcast(client, client.username + " Say: " + receive_string);
        return;
    }
    if (confirm_username(client, receive_string) == 0)
    {
        broadcast(client, client.username + " Joined.");
        send(client.socket, ACCEPT_FLAG, FLAG_LENGTH, 0);
        return;
    }
    send(client.socket, REFUSE_FLAG, FLAG_LENGTH, 0);
}

int chatroom_server::confirm_username(client_info& client, string& receive_name)
{
    int confirm_result = -1;
    username_mutex.lock();

    if (client_usernames.find(receive_name) == client_usernames.end())
    {
        confirm_result = 0;
        client.username = receive_name;
        client_usernames.emplace(receive_name);
    }
    username_mutex.unlock();
    return confirm_result;
}

void chatroom_server::remove_client(client_info& client)
{
    close(client.socket);
    sockets_mutex.lock();
    client_sockets.erase(client.socket);
    sockets_mutex.unlock();
    username_mutex.lock();
    client_usernames.erase(client.username);
    username_mutex.unlock();
}

void chatroom_server::broadcast(client_info& client, string message)
{
    sockets_mutex.lock();

    for (int client_socket : client_sockets)
    {
        if (client_socket != client.socket && send(client_socket, message.data(), message.length(), 0) == -1)
        {
            shutdown(client_socket, SHUT_RDWR);
            close(client_socket);
        }
    }
    sockets_mutex.unlock();
    fprintf(stdout, "%s:%d %s\n", inet_ntoa(client.addr.sin_addr), client.addr.sin_port, message.data());
}

int chatroom_server::run_server()
{
    if (listen(listen_socket, QUEUE_LENGTH) == -1)
    {
        fprintf(stderr, "(System) Listen Error: %s\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(System) Server Listening At %d\n", SERVER_PORT);
    addr_length = sizeof(sockaddr);

    while (true)
    {
        accept_socket = accept(listen_socket, (sockaddr*)&client_addr, &addr_length);

        if (accept_socket == -1)
        {
            fprintf(stderr, "(System) Accept Error: %s\n", strerror(errno));
            break;
        }
        client_thread_pool.push_back(thread(&chatroom_server::connection_handler, this, client_info{ accept_socket, client_addr }));

        sockets_mutex.lock();
        client_sockets.emplace(accept_socket);
        sockets_mutex.unlock();

        fprintf(stdout, "(System) %s:%d Connected\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
    }
    fprintf(stdout, "(System) Server Listening End\n");
    return 0;
}
