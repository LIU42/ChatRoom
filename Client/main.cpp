#include "client.h"

chatroom_client client;

void exit_handler(int signal)
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, exit_handler);
    signal(SIGKILL, exit_handler);
    
    return client.run_client();
}