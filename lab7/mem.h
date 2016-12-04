#ifndef _MEM_H_
#define _MEM_H_

#define __USE_MISC
#define _DEFAULT_SOURCE

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)

struct mem_t;

#pragma pack(push, 1)
struct mem_t {
    struct mem_t* next;
    size_t capacity;
    int is_free;
};
#pragma pack(pop)

void* _malloc(size_t query);
void _free(void *mem);

#endif /* _MEM_H_ */
