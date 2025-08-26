#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "connection.h"

#define SERVER_PORT 8000
#define MAX_WAITING_REQUESTS 16

int start_server();
void close_server(int signal);

#endif
