#include "server.h"

socklen_t addr_len = sizeof(struct sockaddr);

int listen_sock = 0;
int accept_sock = 0;

struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

int initialize_server()
{
    if (initialize_connection_pool() == -1)
    {
        fprintf(stderr, "(system) connection pool initialize fail.\n");
        return -1;
    }
    listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listen_sock == -1)
    {
        fprintf(stderr, "(system) listen sock error: %s.\n", strerror(errno));
        return -1;
    }
    bzero(&server_addr, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "(system) listen bind error: %s.\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(system) server initialize success.\n");
    return 0;
}

void close_server(int signal)
{
    if (close(listen_sock) == -1)
    {
        fprintf(stdout, "(system) close listen sock fail: %s.\n", strerror(errno));
    }
    close_connection_pool();
    fprintf(stdout, "(system) server closed. signal: %d\n", signal);
}

int start_listening()
{
    if (listen(listen_sock, MAX_WAITING_REQUESTS) == -1)
    {
        fprintf(stderr, "(system) error at start listening: %s.\n", strerror(errno));
        return -1;
    }
    fprintf(stdout, "(system) server listening at port %d.\n", SERVER_PORT);

    while (1)
    {
        accept_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addr_len);

        if (accept_sock == -1)
        {
            fprintf(stderr, "(system) accept error: %s.\n", strerror(errno));
            return -1;
        }
        add_connection(accept_sock, client_addr);
    }
    fprintf(stdout, "(system) server listening end.\n");
    return 0;
}

int start_server()
{
    if (initialize_server() != 0)
    {
        fprintf(stdout, "(system) server initialize fail.\n");
        return -1;
    }
    return start_listening();
}
