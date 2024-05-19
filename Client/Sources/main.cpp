#include "client.h"

void exit_handler(int signal)
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    static chatroom_client client;

    signal(SIGINT, exit_handler);
    signal(SIGQUIT, exit_handler);
    
    return client.run_client();
}