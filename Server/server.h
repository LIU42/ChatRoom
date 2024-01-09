#ifndef __SERVER_H__
#define __SERVER_H__

#include <unordered_set>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

using namespace std;

class chatroom_thread;

class chatroom_server
{
    private:
        static constexpr auto SERVER_PORT = 8000;
        static constexpr auto QUEUE_LENGTH = 10;

    private:
        vector<chatroom_thread*> client_thread_pool;
        unordered_set<int> online_sockets;
        unordered_set<string> online_usernames;

    private:
        sockaddr_in server_addr;
        sockaddr_in client_addr;

    private:
        mutex username_mutex;
        mutex sockets_mutex;

    private:
        int listen_socket;
        int accept_socket;
        unsigned addr_length;

    public:
        int consult_username(chatroom_thread* thread_ptr, string& receive_name);
        void remove_client(chatroom_thread* thread_ptr);
        void broadcast(chatroom_thread* thread_ptr, string message);

    public:
        chatroom_server();
        ~chatroom_server();

    public:
        int run_server();
};

class chatroom_thread
{
    friend class chatroom_server;

    private:
        static constexpr auto BUFFER_SIZE = 2048;
        static constexpr auto FLAG_LENGTH = 2;
        static constexpr auto ACCEPT_FLAG = "n0";
        static constexpr auto REFUSE_FLAG = "n1";

    private:
        chatroom_server* server_ptr;
        thread* connect_thread_ptr;

    private:
        string receive_string;
        string username;
        sockaddr_in client_addr;

    private:
        char receive_buffer[BUFFER_SIZE];
        int receive_length;
        int client_socket;

    private:
        void connection_handler();
        void receive_handler();

    public:
        chatroom_thread(chatroom_server* server_ptr, int client_socket, sockaddr_in client_addr);
        ~chatroom_thread();
};
#endif