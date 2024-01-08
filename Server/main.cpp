#include "server.h"

chatroom_server server;

void exit_handler(int signal)
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, exit_handler);
    signal(SIGKILL, exit_handler);

    return server.run_server();
}