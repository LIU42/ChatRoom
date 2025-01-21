#include "server.h"

int main(int argc, char* argv[])
{
    signal(SIGINT, close_server);
    signal(SIGQUIT, close_server);
    signal(SIGKILL, close_server);
    signal(SIGTERM, close_server);
    signal(SIGSTOP, close_server);

    return start_server();
}
