#include <libex1629.h>
#include <pthread.h>
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

static void *handle_entry(void *arg);
static int handle(ConnectionArgs *args);

int server_new(Server **server, const char *host) {
    EX1629_CLIENT *client = NULL;
    try(client_new(&client, host));

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    panic_on(socket_fd < 0);

    Server *sv = (Server *)malloc(sizeof(Server));
    sv->client = client;
    sv->socket_fd = socket_fd;
    *server = sv;
    return 0;
}

int server_start(const Server *server, uint32_t port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    socklen_t addr_size = sizeof(addr);
    bind(server->socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    try(listen(server->socket_fd, 3));
    while (true) {
        int connection_fd =
            accept(server->socket_fd, (struct sockaddr *)&addr, &addr_size);
        ConnectionArgs *connectionArgs =
            (ConnectionArgs *)malloc(sizeof(ConnectionArgs));
        connectionArgs->client = server->client;
        connectionArgs->connection_fd = connection_fd;
        pthread_t thread;
        pthread_create(&thread, NULL, handle_entry, connectionArgs);
    }
    return 0;
}

static void *handle_entry(void *arg) {
    ConnectionArgs *args = (ConnectionArgs *)arg;
    int result = handle(args);
    if (result != 0) {
        printf("encountering error: %d\n", result);
    }
    return NULL;
}

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
    printf("sent.\n");
    free(args);
    return 0;
}
