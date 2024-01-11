#include "client.h"

chatroom_client::chatroom_client()
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1)
    {
        fprintf(stderr, "(System) Socket error: %s.\n", strerror(errno));
        return;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server_addr.sin_port = htons(SERVER_PORT);

    fprintf(stdout, "(System) Client initialize success.\n");
}

chatroom_client::~chatroom_client()
{
    is_progess_interrupted = true;

    unset_ncurses();
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);

    if (receive_thread_ptr != nullptr && receive_thread_ptr->joinable())
    {
        receive_thread_ptr->join();
    }
    delete receive_thread_ptr;

    fprintf(stdout, "(System) Client exit.\n");
}

void chatroom_client::init_ncurses()
{
    if (!is_ncurses_setup)
    {
        initscr();
        cbreak();
        noecho();
        curs_set(false);
        keypad(stdscr, true);
    }
    is_ncurses_setup = true;
}

void chatroom_client::unset_ncurses()
{
    if (is_ncurses_setup)
    {
        nocbreak();
        keypad(stdscr, true);
        curs_set(true);
        echo();
        endwin();
    }
    is_ncurses_setup = false;
}

void chatroom_client::flush_screen()
{
    message_mutex.lock();
    clear();
    paint_title();
    paint_messages();
    paint_line();
    paint_input();
    refresh();
    message_mutex.unlock();
}

void chatroom_client::paint_title()
{
    mvprintw(0, COLS / 2 - 10, "ChatRoom - (%s)", username.data());
}

void chatroom_client::paint_messages()
{
    move(2, 0);

    for (int index = message_start_index; index < messages.size(); index++)
    {
        printw("%s\n", messages[index].data());
    }
}

void chatroom_client::paint_line()
{
    mvprintw(LINES - 3, 0, "-");

    for (int cols = 1; cols < COLS; cols++)
    {
        printw("-");
    }
}

void chatroom_client::paint_input()
{
    mvprintw(LINES - 2, 1, "%s_", message.substr(max((int)message.length() - (int)COLS + 3, 0)).data());
}

void chatroom_client::add_message(string message)
{
    message_mutex.lock();
    message_show_lines += get_message_lines(message);
    messages.emplace_back(message);

    while (message_show_lines > LINES - 6)
    {
        message_show_lines -= get_message_lines(messages[message_start_index]);
        message_start_index += 1;
    }
    message_mutex.unlock();
}

void chatroom_client::receive_handler()
{
    message_start_index = 0;
    message_show_lines = 0;
    is_progess_interrupted = false;

    while (true)
    {
        receive_length = recv(client_socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            unset_ncurses();
            fprintf(stdout, "(System) Connection closed.\n");
            break;
        }
        if (receive_length == -1)
        {
            unset_ncurses();
            fprintf(stderr, "(System) %s.\n", strerror(errno));
            break;
        }
        receive_buffer[receive_length] = '\0';
        add_message(string(receive_buffer));
        flush_screen();
    }
    if (!is_progess_interrupted)
    {
        kill(getpid(), SIGINT);
    }
}

int chatroom_client::input_interval()
{
    init_ncurses();
    flush_screen();

    while (true)
    {
        int input_char = getch();

        if (isprint(input_char) && message.length() < BUFFER_SIZE - 3)
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
                fprintf(stderr, "(System) Message send failure: %s.\n", strerror(errno));
                return -1;
            }
            add_message(username + ": " + message);
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
        fprintf(stderr, "(System) Connect error: %s.\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(System) Connect server success.\n");

    while (username.length() == 0)
    {
        fprintf(stdout, "Please enter your username: ");
        fflush(stdout);
        getline(cin, input);

        if (send(client_socket, input.data(), input.length(), 0) == -1)
        {
            fprintf(stderr, "(System) Username send failure: %s.\n", strerror(errno));
            return -1;
        }
        receive_length = recv(client_socket, receive_buffer, BUFFER_SIZE, 0);

        if (receive_length == 0)
        {
            fprintf(stdout, "(System) Connection closed.\n");
            return 0;
        }
        if (receive_length == -1)
        {
            fprintf(stderr, "(System) %s.\n", strerror(errno));
            return -1;
        }
        receive_buffer[receive_length] = '\0';

        if (strcmp(receive_buffer, ACCEPT_FLAG) == 0)
        {
            username = input;
            break;
        }
        fprintf(stdout, "(Server) This username is used. Try anothor.\n");
    }
    receive_thread_ptr = new thread(&chatroom_client::receive_handler, this);
    return input_interval();
}

int chatroom_client::get_message_lines(string& message)
{
    return ceil((double)message.length() / COLS);
}
