#ifndef _MEM_H_
#define _MEM_H_

#define __USE_MISC
#define _DEFAULT_SOURCE

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)
#define HEAP_SIZE 0x800000ul
#define IS_ROOT 1
#define IS_FREE 1

struct mem_t;

#pragma pack(push, 1)
struct mem_t {
    struct mem_t* next;
    size_t capacity;
    int is_free;
    int is_root;
};
#pragma pack(pop)

void* _malloc(size_t query);
void _free(void *mem);

#endif /* _MEM_H_ */
