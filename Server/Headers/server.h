#ifndef __SERVER_H__
#define __SERVER_H__

#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <string>
#include <mutex>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

class chatroom_thread;

enum class consult_result
{
    RESULT_ACCEPT,
    RESULT_REPEAT,
    RESULT_INVALID
};

class chatroom_server
{
    private:
        static constexpr auto SERVER_PORT = 8000;
        static constexpr auto BUFFER_SIZE = 16;
        static constexpr auto QUEUE_LENGTH = 10;
        static constexpr auto GARBAGE_COLLECTION_DELAY = 1;

    public:
        static constexpr auto ONLINE_COUNT_PREFIX = '#';
        static constexpr auto USER_MESSAGE_PREFIX = '$';

    private:
        thread* garbage_collection_thread_ptr;

    private:
        unordered_map<int, chatroom_thread*> client_thread_pool;
        unordered_set<int> online_sockets;
        unordered_set<int> offline_sockets;
        unordered_set<string> online_usernames;

    private:
        sockaddr_in server_addr;
        sockaddr_in client_addr;
        socklen_t addr_length;

    private:
        mutex username_mutex;
        mutex sockets_mutex;
        mutex threads_mutex;

    private:
        char online_count_buffer[BUFFER_SIZE];
        bool is_server_running;
        int listen_socket;
        int accept_socket;

    private:
        void garbage_collection();

    public:
        consult_result consult_username(chatroom_thread* thread_ptr, string& receive_name);
        void remove_client(chatroom_thread* thread_ptr);
        void broadcast_message(chatroom_thread* thread_ptr, string message);
        void broadcast_online_user_count();

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
        static constexpr auto RESPONSE_LENGTH = 2;

    private:
        static constexpr auto ACCEPT_RESPONSE = "&0";
        static constexpr auto REPEAT_RESPONSE = "&1";
        static constexpr auto INVALID_RESPONSE = "&2";

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
