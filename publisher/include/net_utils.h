#ifndef _NET_UTILS_H_
#define _NET_UTILS_H_

#include <stdint.h>

int send_string(int connection_fd, char *s);
int send_uint32(int connection_fd, uint32_t x);

int receive_string(int connection_fd, char *s, uint32_t *len);
int receive_uint32(int connection_fd, uint32_t *x);
int receive_byte(int connection_fd, uint8_t *x);

#endif
