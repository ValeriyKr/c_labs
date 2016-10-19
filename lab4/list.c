/* Made by ValeriyKr */
#include <stdlib.h>

typedef int T;
typedef struct list_t {
    struct list_t *next;
    size_t refs;
    T data;
} list_t;

/* Creates list node. Return NULL if fails. */
list_t* list_create() {
    list_t *list = (list_t*) malloc(sizeof(list_t));
    list->next = NULL;
    list->refs = 1;
    return list;
}


void list_free(list_t *list) {
    list_t *next;
    if (NULL == list) return;
    for (; list->next; list = next) {
        next = list->next;
        list->refs--;
        if (!list->refs)
            free(list);
    }
    list = NULL;
}

/* Creates node in front of list. Returns 0 if success */
int list_add_front(list_t *list, T data) {
    list_t *node;
    if (NULL == list) return 1;
    node = list_create();
    if (NULL == node) return 2;
    node->data = data;
    node->next = list->next;
    list->next = node;
    return 0;
}

/* Creates node in back of list. Returns 0 if success */
int list_add_back(list_t *list, T data) {
    list_t *node;
    if (NULL == list) return 1;
    node = list_create();
    if (NULL == node) return 2;
    node->data = data;
    for (; list->next; list = list->next);
    list->next = node;
    node->refs = list->refs;
    return 0;
}

/* Returns node by index or NULL if fails. */
static list_t* list_node_at(const list_t *list, size_t i) {
    if (NULL == list) return NULL;
    for (list = list->next; i && list->next; i--, list = list->next);
    if (i) {
        return NULL;
    }
    return (list_t*) list;
}

/* Returns sublist of list from i to end or NULL if fails */
list_t* list_tail(const list_t *list, size_t i) {
    list_t *head = list_node_at(list, i);
    list_t *sublist;
    if (NULL == head) return NULL;
    sublist = list_create();
    sublist->next = head;
    for (; head->next; head = head->next) head->refs++;
    return sublist;
}


/* Return data in node[i]. Sets non-zero in err, if fails */
T list_get(const list_t *list, size_t i, int *err) {
    if (NULL == list) {
        *err = 1;
        return 0;
    }
    list = list_node_at(list, i);
    if (!list) {
        *err = 2;
        return 0;
    }
    *err = 0;
    return list->data;
}


size_t list_length(const list_t *list) {
    size_t length;
    if (NULL == list) return 0;
    for (length = 0; list->next; ++length, list = list->next);
    return length;
}


T list_sum(const list_t *list) {
    T sum = 0;
    if (NULL == list) return 0;
    for (list = list->next; list; list = list->next)
        sum += list->data;
    return sum;
}
