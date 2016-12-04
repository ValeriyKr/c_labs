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
static void *root_block = (void *) NULL;
static size_t root_heap_size = 0;

static void init_block(struct mem_t *addr, struct mem_t *next,
        size_t capacity, int is_free, int is_root) {
    addr->next     = next;
    addr->capacity = capacity;
    addr->is_free  = is_free;
    addr->is_root  = is_root;
}


static void* find_free(struct mem_t *current, size_t capacity) {
    if (NULL == current) return NULL;
    if (current != root_block && IS_ROOT == current->is_root) return NULL;
    if (current->capacity <= capacity && current->is_free) return current;
    return find_free(current->next, capacity);
}


static void* make_heap(void *addr, size_t heap_size) {
    /* Try to allocate on specified place */
    void *real_addr = mmap(addr, heap_size, PROT_WRITE | PROT_READ,
            MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (MAP_FAILED == real_addr) {
        /* Fail, try to allocate anywhere */
        real_addr = mmap(NULL, heap_size, PROT_WRITE | PROT_READ,
                MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (MAP_FAILED == real_addr) return NULL;
    }
    return real_addr;
}


void* _malloc(size_t query) {
    struct mem_t *addr;
    if (blocks_count < 1) {
        root_heap_size = (sizeof(struct mem_t)+query) < HEAP_SIZE ?
                HEAP_SIZE : (sizeof(struct mem_t)+query);
        addr = make_heap(HEAP_START, root_heap_size);
        if (NULL == addr) return NULL;
        blocks_count++;
        init_block(addr, NULL, query, !IS_FREE, IS_ROOT);
        root_block = addr;
        return (void*) (addr+1);
    }
    /* There are allocated blocs. Try to find big free block for us
     * If we must create new block and last found block not in main heap,
     * create new heap for it.
     */
    if (NULL != (addr = find_free(root_block, query))) {
        /* Split&Use */
        addr->is_free = !IS_FREE;
        if (query == addr->capacity)
            return (void*) (addr+1);
        if (query+sizeof(struct mem_t) <= addr->capacity) {
            struct mem_t *new_block = (struct mem_t *)
                (((char*) (addr + 1)) + query);
            init_block(new_block, addr->next,
                    addr->capacity - query - sizeof(struct mem_t),
                    IS_FREE, !IS_ROOT);
            init_block(addr, new_block, query, !IS_FREE, addr->is_root);
            blocks_count++;
        }
        return (void *) (addr+1);
    } else {
        int in_heap = 1;
        struct mem_t *parent = root_block;
        for (; parent->next; parent = parent->next)
            if (root_block != parent && parent->is_root)
                in_heap = 0;
        if (in_heap) {
            if (root_heap_size - ((char*) (parent + 1) + parent->capacity -
                     (char*)root_block) >= sizeof(struct mem_t) + query) {
                addr = (struct mem_t *) ((char *) (parent+1) + parent->capacity);
                parent->next = addr;
                init_block(addr, NULL, query, !IS_FREE, !IS_ROOT);
                blocks_count++;
                return (void *) (addr+1);
            }
        }
        if (NULL == (addr = make_heap(NULL, sizeof(struct mem_t) + query)))
            return NULL;
        parent->next = addr;
        init_block(addr, NULL, query, !IS_FREE, IS_ROOT);
        blocks_count++;
        return (void *) (addr+1);
    }
}


void _free(void *mem) {
}
