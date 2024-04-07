#ifndef _SERVER_H_
#define _SERVER_H_

#include <libex1629.h>

typedef struct {
    EX1629_CLIENT *client;
    int socket_fd;
} Server;

Server *server_new(const char *host);
void server_start(const Server *server, uint32_t port);

#endif
