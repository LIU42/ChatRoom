#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <signal.h>

using namespace std;

class chatroom_client
{
    private:
        static constexpr auto SERVER_ADDR = "127.0.0.1";
        static constexpr auto SERVER_PORT = 8000;
        static constexpr auto BUFFER_SIZE = 2048;

    private:
        static constexpr auto ACCEPT_FLAG = "n0";
        static constexpr auto REFUSE_FLAG = "n1";

    private:
        thread* receive_thread_ptr;

    private:
        vector<string> messages;
        sockaddr_in server_addr;
        mutex message_mutex;

    private:
        string input;
        string username;
        string message;

    private:
        char receive_buffer[BUFFER_SIZE];
        int receive_length;
        int client_socket;
        int message_start_index;
        int message_show_lines;
        bool is_progess_interrupted;
        bool is_ncurses_setup;

    private:
        void init_ncurses();
        void unset_ncurses();
        void flush_screen();

    private:
        void paint_title();
        void paint_messages();
        void paint_line();
        void paint_input();

    private:
        void add_message(string message);
        void receive_handler();
        int input_interval();
        int get_message_lines(string& message);

    public:
        chatroom_client();
        ~chatroom_client();

    public:
        int run_client();
};
#endif