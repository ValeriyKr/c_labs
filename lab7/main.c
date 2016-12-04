#include <stdio.h>

#include "mem.h"

int main(void) {
    void *addr2;
    void *addr = _malloc(10);
    size_t i;
    addr2 = _malloc(10000);
    for (i = 0; i < 8; ++i) 
        *((char*)addr+i) = 'f';
    *((char*)addr+8) = '\0';
    *((char*)addr+0) = 'd';
    *((char*)addr+1) = 'e';
    *((char*)addr+2) = 'f';
    *((char*)addr+3) = '\0';
    for (i = 0; i < 10000-1; ++i) 
        *((char*)addr2+i) = 'f';
    *((char*)addr2+10000) = '\0';
    printf("%s\n", (char*) addr2);
    _free(addr2);
    _free(addr);

    return 0;
}
