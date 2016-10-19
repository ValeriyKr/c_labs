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


void list_foreach(const list_t *list, void (*f)(T)) {
    if (NULL == list) return;
    for (list = list->next; list; list = list->next)
        f(list->data);
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
