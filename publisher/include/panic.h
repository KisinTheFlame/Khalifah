#ifndef _PANIC_H_
#define _PANIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define panic(message) \
    do { \
        if (strcmp(message, "") != 0) { \
            printf(message "\n"); \
        } \
        exit(1); \
    } while (0)

#define panic_on(expression) \
    do { \
        if (expression) { \
            panic(__FILE__ "panic on " #expression); \
        } \
    } while (0)

#endif
