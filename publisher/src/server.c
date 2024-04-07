#include <libex1629.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "client.h"
#include "net_utils.h"
#include "panic.h"
#include "server.h"
#include "try.h"

typedef struct {
    EX1629_CLIENT *client;
    int connection_fd;
} ConnectionArgs;

static int handle(ConnectionArgs *args) {
    EX1629_CLIENT *client = args->client;
    int connection_fd = args->connection_fd;
    char prefix[255];
    int major;
    int minor;
    int build;
    ex1629_try(
        libex1629_get_firmware_version(client, prefix, &major, &minor, &build)
    );
    printf(
        "EX1629 Firmware Version: %s.%d.%d.%d\n", prefix, major, minor, build
    );
    send_string(connection_fd, prefix);
    send_uint32(connection_fd, major);
    send_uint32(connection_fd, minor);
    send_uint32(connection_fd, build);
    free(args);
    return 0;
}

Server *server_new(const char *host) {
    EX1629_CLIENT *client = client_new(host);
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    panic_on(socket_fd < 0);

    Server *server = malloc(sizeof(Server));
    server->client = client;
    server->socket_fd = socket_fd;
    return server;
}

void server_start(const Server *server, uint32_t port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(server->socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    try(listen(server->socket_fd, 3));
    while (true) {
        int connection_fd = accept(server->socket_fd, &addr, sizeof(addr));
        ConnectionArgs *connectionArgs =
            (ConnectionArgs *)malloc(sizeof(ConnectionArgs));
        connectionArgs->client = server->client;
        connectionArgs->connection_fd = connection_fd;
        pthread_t thread;
        pthread_create(&thread, NULL, handle, connectionArgs);
    }
}
