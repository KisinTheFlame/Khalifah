#ifndef _TRY_H_
#define _TRY_H_

#include "panic.h"

#define try(expression) \
    do { \
        int r = (expression); \
        if (r != 0) { \
            return r; \
        } \
    } while (0)

#define ex1629_try(ex1629_call) \
    do { \
        ex1629_result_t r = (ex1629_call); \
        if (r != 0) { \
            printf("error code: %d\n", r); \
            return r; \
        } \
    } while (0)

#endif
