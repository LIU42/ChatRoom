#include "server.h"

void exit_handler(int signal)
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    static chatroom_server server;

    signal(SIGINT, exit_handler);
    signal(SIGQUIT, exit_handler);

    return server.run_server();
}
