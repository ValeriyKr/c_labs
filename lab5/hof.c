/* Made by ValeriyKr */

#include <stdlib.h>

typedef int T;
typedef struct list_t {
    struct list_t *next;
    size_t refs;
    T data;
} list_t;
#define _LIST_T_
#include "hof.h"


void
list_foreach(const list_t *list, void (*f)(T, size_t, void **),
             size_t argc, void **argv) {
    if (NULL == list) return;
    for (list = list->next; list; list = list->next)
        f(list->data, argc, argv);
}


list_t* list_map(const list_t *list, T (*f)(T)) {
    list_t *head, *node;
    if (NULL == list) return NULL;
    head = list_create();
    if (NULL == head) return NULL;
    node = head;
    for (list = list->next; list; list = list->next) {
        if (NULL == (node->next = list_create())) {
            list_free(head);
            return NULL;
        }
        node = node->next;
        node->data = f(list->data);
    }
    return head;
}


void list_map_mut(list_t *list, T (*f)(T)) {
    if (NULL == list) return;
    for (list = list->next; list; list = list->next)
        list->data = f(list->data);
}


T list_foldl(const list_t *list, T (*f)(T, T), T accum) {
    if (NULL == list) return accum;
    for (list = list->next; list; list = list->next)
        accum = f(accum, list->data);
    return accum;
}


list_t* list_iterate(size_t len, T (*f)(T), T accum) {
    list_t *list, *curr;
    if (0 == len || NULL == (list = list_create()))
        return NULL;
    if (NULL == (list->next = list_create())) {
        list_free(list);
        return NULL;
    }
    curr = list->next;
    curr->data = accum;
    for (len--; len; len--, curr = curr->next) {
        if (NULL == (curr->next = list_create())) {
            list_free(list);
            return NULL;
        }
        curr->next->data = f(curr->data);
    }
    return list;
}
