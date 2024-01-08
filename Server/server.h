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
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

struct client_info
{
    int socket;
    sockaddr_in addr;
    string username;
};

class chatroom_server
{
    private:
        static constexpr auto SERVER_PORT = 8000;
        static constexpr auto BUFFER_SIZE = 2048;
        static constexpr auto QUEUE_LENGTH = 10;

    private:
        static constexpr auto FLAG_LENGTH = 2;
        static constexpr auto ACCEPT_FLAG = "n0";
        static constexpr auto REFUSE_FLAG = "n1";

    private:
        vector<thread> client_thread_pool;
        unordered_set<string> client_usernames;
        unordered_set<int> client_sockets; 

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

    private:
        void connection_handler(client_info client);
        void receive_handler(client_info& client, string receive_string);

    private:
        int confirm_username(client_info& client, string& receive_name);
        void remove_client(client_info& client);
        void broadcast(client_info& client, string message);

    public:
        chatroom_server();
        ~chatroom_server();

    public:
        int run_server();
};
#endif