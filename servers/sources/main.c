#include <signal.h>

#include "server.h"

void interrupt(int signal)
{
    close_server(signal);
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, interrupt);
    signal(SIGQUIT, interrupt);
    signal(SIGKILL, interrupt);
    signal(SIGTERM, interrupt);
    signal(SIGSTOP, interrupt);

    return start_server();
}
