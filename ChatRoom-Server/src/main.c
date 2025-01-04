#include "server.h"

void terminate(int signal)
{
    close_server();
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, terminate);
    signal(SIGQUIT, terminate);
    signal(SIGKILL, terminate);
    signal(SIGTERM, terminate);
    signal(SIGSTOP, terminate);

    if (initialize_server() == 0)
    {
        start_listening();
    }
    return 0;
}
