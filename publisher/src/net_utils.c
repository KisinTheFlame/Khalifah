#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "net_utils.h"
#include "try.h"

int send_string(int connection_fd, char *s) {
    uint32_t len = strlen(s);
    try(send_uint32(connection_fd, len));
    ssize_t result = send(connection_fd, s, len, 0);
    return result > 0 ? 0 : result;
}

int send_uint32(int connection_fd, uint32_t x) {
    uint32_t conv = htonl(x);
    ssize_t result = send(connection_fd, &conv, sizeof(conv), 0);
    return result > 0 ? 0 : result;
}

int receive_string(int connection_fd, char *s, uint32_t *len) {
    try(receive_uint32(connection_fd, len));
    for (int i = 0; i < len; i++) {
        try(receive_byte(connection_fd, (uint8_t *)(s + i)));
    }
    return 0;
}

int receive_uint32(int connection_fd, uint32_t *x) {
    ssize_t result = recv(connection_fd, x, sizeof(x), 0);
    return result > 0 ? 0 : result;
}

int receive_byte(int connection_fd, uint8_t *x) {
    ssize_t result = recv(connection_fd, x, sizeof(x), 0);
    return result > 0 ? 0 : result;
}
