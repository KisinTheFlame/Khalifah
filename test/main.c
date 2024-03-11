#include <gnu/libc-version.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    // method 1, use macro
    printf("%d.%d\n", __GLIBC__, __GLIBC_MINOR__);

    return 0;
}