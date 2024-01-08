#include "client.h"

chatroom_client::chatroom_client()
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1)
    {
        fprintf(stderr, "(System) Socket Error: %s\n", strerror(errno));
        return;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server_addr.sin_port = htons(SERVER_PORT);

    fprintf(stdout, "(System) Client Initialize Success.\n");
}

chatroom_client::~chatroom_client()
{
    unset_ncurses();
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);

    if (receive_thread.joinable())
    {
        receive_thread.join();
    }
    fprintf(stdout, "(System) Client Exit.\n");
}

void chatroom_client::init_ncurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
}

void chatroom_client::unset_ncurses()
{
    nocbreak();
    keypad(stdscr, true);
    curs_set(true);
    echo();
    endwin();
}

void chatroom_client::flush_screen()
{
    message_mutex.lock();
    erase();
    paint_title();
    paint_messages();
    paint_line();
    paint_input();
    refresh();
    message_mutex.unlock();
}

void chatroom_client::paint_title()
{
    mvaddstr(0, COLS / 2 - 10, "ChatRoom - ");
    addstr(username.data());
}

void chatroom_client::paint_messages()
{
    for (int i = max((int)messages.size() - (int)LINES + 6, 0), j = 2; i < messages.size(); i++, j++)
    {
        mvaddstr(j, 1, messages[i].data());
    }
}

void chatroom_client::paint_line()
{
    for (int i = 0; i < COLS; i++)
    {
        mvaddch(LINES - 3, i, '-');
    }
}

void chatroom_client::paint_input()
{
    mvaddstr(LINES - 2, 1, message.data());
    addch('_');
}

void chatroom_client::receive_handler()
{
    while (true)
    {
        receive_length = recv(client_socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            fprintf(stdout, "(System) Connection Closed.\n");
            return;
        }
        if (receive_length == -1)
        {
            fprintf(stderr, "(System) %s\n", strerror(errno));
            return;
        }
        receive_buffer[receive_length] = '\0';
        message_mutex.lock();
        messages.push_back(string(receive_buffer));
        message_mutex.unlock();
        flush_screen();
    }
}

int chatroom_client::input_interval()
{
    init_ncurses();
    flush_screen();

    while (true)
    {
        int input_char = getch();

        if (isprint(input_char))
        {
            message += (char)input_char;
        }
        else if ((input_char == KEY_BACKSPACE || input_char == '\b') && message.length() > 0)
        {
            message.erase(message.length() - 1, 1);
        }
        else if ((input_char == KEY_ENTER || input_char == '\n') && message.length() > 0)
        {
            if (send(client_socket, message.data(), message.length(), 0) == -1)
            {
                fprintf(stderr, "(System) Message Send Failure: %s\n", strerror(errno));
                return -1;
            }
            message_mutex.lock();
            messages.push_back(username + " Say: " + message);
            message_mutex.unlock();
            message.clear();
        }
        flush_screen();
    }
    return 0;
}

int chatroom_client::run_client()
{
    if (connect(client_socket, (sockaddr*)&server_addr, sizeof(sockaddr)) == -1)
    {
        fprintf(stderr, "(System) Connect Error: %s\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(System) Connect Server Success.\n");

    while (username.length() == 0)
    {
        fprintf(stdout, "Please Enter Your Username: ");
        fflush(stdout);
        getline(cin, input);

        if (send(client_socket, input.data(), input.length(), 0) == -1)
        {
            fprintf(stderr, "(System) Username Send Failure: %s\n", strerror(errno));
            return -1;
        }
        receive_length = recv(client_socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            fprintf(stdout, "(System) Connection Closed.\n");
            return 0;
        }
        if (receive_length == -1)
        {
            fprintf(stderr, "(System) %s\n", strerror(errno));
            return -1;
        }
        receive_buffer[receive_length] = '\0';

        if (strcmp(receive_buffer, ACCEPT_FLAG) == 0)
        {
            username = input;
            break;
        }
        fprintf(stdout, "(Server) This Username Is Used. Try Anothor.\n");
    }
    receive_thread = thread(&chatroom_client::receive_handler, this);
    return input_interval();
}
