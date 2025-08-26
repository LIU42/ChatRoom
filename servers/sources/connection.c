#include "connection.h"

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

pthread_t cleaner_thread = 0;

struct connection* head_connection = NULL;
struct connection* tail_connection = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cleaner_running = 0;

void remove_connection(struct connection* connection)
{
    if (close(connection->client_sock) == -1)
    {
        fprintf(stderr, "(system) close client sock fail: %s.\n", strerror(errno));
    }
    if (pthread_join(connection->session_thread, NULL) != 0)
    {
        fprintf(stderr, "(system) join client thread error.\n");
    }
    connection->prev->next = connection->next;
    connection->next->prev = connection->prev;

    fprintf(stdout, "(system) %s's connection has been removed.\n", connection->addr_buffer);
    free(connection);
}

void clear_connections()
{
    struct connection* curr_connection = head_connection->next;
    struct connection* next_connection = curr_connection->next;

    pthread_mutex_lock(&mutex);

    while (curr_connection != tail_connection)
    {
        remove_connection(curr_connection);

        curr_connection = next_connection;
        next_connection = next_connection->next;  
    }
    pthread_mutex_unlock(&mutex);
}

void broadcast_message(char* message, int length)
{
    struct connection* connection = head_connection->next;

    pthread_mutex_lock(&mutex);

    while (connection != tail_connection)
    {
        if (send(connection->client_sock, message, length, 0) == -1)
        {
            fprintf(stderr, "(system) send to %s fail: %s.\n", connection->addr_buffer, strerror(errno));
        }
        connection = connection->next;
    }
    pthread_mutex_unlock(&mutex);

    fprintf(stdout, "(message) '%s'.\n", message);
}

void* connection_session(void* args)
{
    struct connection* connection = (struct connection*)args;

    while (1)
    {
        int recv_length = recv(connection->client_sock, connection->recv_buffer, RECV_BUFFER_SIZE, 0);

        if (recv_length == 0)
        {
            fprintf(stdout, "(system) %s disconnect.\n", connection->addr_buffer);
            break;
        }
        if (recv_length == -1)
        {
            fprintf(stderr, "(system) %s error: %s.\n", connection->addr_buffer, strerror(errno));
            break;
        }
        connection->recv_buffer[recv_length] = '\0';
        broadcast_message(connection->recv_buffer, recv_length);
    }
    connection->client_alive = 0;
    return NULL;
}

void* connection_cleaner(void* args)
{
    while (cleaner_running)
    {
        struct connection* curr_connection = head_connection->next;
        struct connection* next_connection = curr_connection->next;

        pthread_mutex_lock(&mutex);

        while (curr_connection != tail_connection)
        {
            if (curr_connection->client_alive == 0)
            {
                remove_connection(curr_connection);
            }
            curr_connection = next_connection;
            next_connection = next_connection->next;
        }
        pthread_mutex_unlock(&mutex);
        
        sleep(CLEANER_WORKING_DELAY);
    }
    fprintf(stdout, "(system) cleaner thread stop.\n");
    return NULL;
}

int initialize_connection_pool()
{
    cleaner_running = 1;

    if (pthread_create(&cleaner_thread, NULL, connection_cleaner, NULL) != 0)
    {
        fprintf(stderr, "(system) cleaner thread create fail.\n");
        return -1;
    }
    head_connection = (struct connection*)malloc(sizeof(struct connection));
    tail_connection = (struct connection*)malloc(sizeof(struct connection));

    if (head_connection == NULL || tail_connection == NULL)
    {
        fprintf(stderr, "(system) memory allocation error.\n");
        return -1;
    }
    head_connection->client_sock = -1;
    tail_connection->client_sock = -1;

    head_connection->next = tail_connection;
    head_connection->prev = NULL;

    tail_connection->prev = head_connection;
    tail_connection->next = NULL;

    fprintf(stdout, "(system) connection pool initialize success.\n");
    return 0;
}

void close_connection_pool()
{
    cleaner_running = 0;

    if (pthread_join(cleaner_thread, NULL) != 0)
    {
        fprintf(stderr, "(system) join cleaner thread error.\n");
    }
    clear_connections();

    free(head_connection);
    free(tail_connection);

    fprintf(stdout, "(system) connection pool closed.\n");
}

int add_connection(int client_sock, struct sockaddr_in client_addr)
{
    struct connection* new_connection = (struct connection*)malloc(sizeof(struct connection));

    if (new_connection == NULL)
    {
        fprintf(stderr, "(system) memory allocation error.\n");
        return -1;
    }
    snprintf(new_connection->addr_buffer, ADDR_BUFFER_SIZE, "[%s:%d]", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    new_connection->client_alive = 1;
    new_connection->client_sock = client_sock;

    if (pthread_create(&new_connection->session_thread, NULL, connection_session, (void*)new_connection) != 0)
    {
        fprintf(stderr, "(system) new session thread create fail.\n");
        return -1;
    }
    pthread_mutex_lock(&mutex);

    new_connection->next = tail_connection;
    new_connection->prev = tail_connection->prev;

    new_connection->next->prev = new_connection;
    new_connection->prev->next = new_connection;

    pthread_mutex_unlock(&mutex);

    fprintf(stdout, "(system) %s connected.\n", new_connection->addr_buffer);
    return 0;
}
