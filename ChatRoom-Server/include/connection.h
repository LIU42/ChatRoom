#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define RECV_BUFFER_SIZE 2048
#define ADDR_BUFFER_SIZE 32
#define CLEANER_WORKING_DELAY 5

struct connection
{
    pthread_t session_thread;
    int client_sock;
    int client_alive;
    char recv_buffer[RECV_BUFFER_SIZE];
    char addr_buffer[ADDR_BUFFER_SIZE];
    struct connection* next;
    struct connection* prev;
};

int initialize_connection_pool();
int add_connection(int client_sock, struct sockaddr_in client_addr);

void close_connection_pool();

#endif
