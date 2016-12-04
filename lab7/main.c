#include <stdio.h>

#include "mem.h"

int main(void) {
    void *addr = _malloc(10);
    size_t i;
    printf("%p\n", addr);
    *((char*)addr+0) = 'a';
    *((char*)addr+1) = 'b';
    *((char*)addr+2) = 'c';
    *((char*)addr+3) = '\0';
    printf("%s\n", (char*) addr);
    addr = _malloc(10000);
    printf("%p\n", addr);
    *((char*)addr+0) = 'd';
    *((char*)addr+1) = 'e';
    *((char*)addr+2) = 'f';
    *((char*)addr+3) = '\0';
    for (i = 0; i < 10000-1; ++i) 
        *((char*)addr+i) = 'f';
    *((char*)addr+10000) = '\0';
    printf("%s\n", (char*) addr);

    return 0;
}
