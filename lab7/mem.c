#include <stdio.h>

#include "mem.h"

/*
 * struct mem_t {
 *     struct mem_t* next;
 *     size_t capacity;
 *     int is_free;
 * };
 */

static size_t blocks_count = 0;
static void *first_block = (void *) NULL;

static void init_block(struct mem_t *addr, struct mem_t *next,
        size_t capacity, int is_free) {
    addr->next     = next;
    addr->capacity = capacity;
    addr->is_free  = is_free;
}


static void* find_free(struct mem_t *current, size_t capacity) {
    if (NULL == current) return NULL;
    if (current->capacity <= capacity && current->is_free) return current;
    return find_free(current->next, capacity);
}


void* _malloc(size_t query) {
    struct mem_t *addr;
    if (blocks_count < 1) {
        /* Try to alloc on specified place */
        addr = (struct mem_t *) mmap(HEAP_START, query+sizeof(struct mem_t),
          PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (MAP_FAILED == addr) {
            /* Fail, try to alloc anywhere */
            addr = (struct mem_t *) mmap(NULL, query+sizeof(struct mem_t),
              PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
            if (MAP_FAILED == addr) return NULL;
        }
        blocks_count++;
        init_block(addr, NULL, query, 0);
        first_block = addr;
        return (void*) (addr+1);
    }
    /* There are allocated blocs. Try to find big free block for us */
    if (NULL != (addr = find_free(first_block, query))) {
        /* Split&Use */
        addr->is_free = 0;
        if (query == addr->capacity)
            return (void*) (addr+1);
        if (query+sizeof(struct mem_t) <= addr->capacity) {
            struct mem_t *new_block = (struct mem_t *)
                (((char*) (addr + 1)) + query);
            init_block(new_block, addr->next,
                    addr->capacity-query-sizeof(struct mem_t), 1);
            init_block(addr, new_block, query, 0);
            blocks_count++;
        }
        return (void *) (addr+1);
    } else {
        /* Find last block, create new, connect them, return new */
        struct mem_t *parent, *new_block;
        for (parent = first_block; parent->next != NULL; parent = parent->next);
        addr = (struct mem_t *) (((char*) (parent + 1)) + parent->capacity);
        new_block = (struct mem_t *) mmap(addr, query+sizeof(struct mem_t),
          PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (MAP_FAILED == new_block) {
            new_block = (struct mem_t *) mmap(NULL, query+sizeof(struct mem_t),
              PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
            if (MAP_FAILED == NULL) return NULL;
        }
        blocks_count++;
        init_block(new_block, NULL, query, 0);
        parent->next = new_block;
        return (void*) (new_block+1);
    }
}


void _free(void *mem) {

}
