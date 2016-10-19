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


void list_foreach(const list_t *list, void (*f)(const T)) {
    if (NULL == list) return;
    for (list = list->next; list; list = list->next)
        f(list->data);
}

