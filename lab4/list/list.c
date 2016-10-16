/* Made by ValeriyKr */
#include <stdlib.h>

typedef int T;
typedef struct list_elem_t {
    struct list_elem_t *prev;
    struct list_elem_t *next;
    T data;
} list_elem_t;

typedef struct list_t {
    list_elem_t *head;
    list_elem_t *tail;
    size_t size;
} list_t;

/* Creates main list node. Return NULL if fails. */
list_t* list_create() {
    list_t *list = (list_t*) malloc(sizeof(list_t));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}


static list_elem_t* list_create_node(T data) {
    list_elem_t *node = (list_elem_t*) malloc(sizeof(list_elem_t));
    if (NULL == node) return NULL;
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}


void list_free(list_t *list) {
    if (NULL == list) return;
    if (list->size) {
        list_elem_t *curr = list->head;
        while (NULL != curr->next) {
            curr = curr->next;
            free(curr->prev);
        }
        free(curr);
    }
    free(list);
}

/* Creates node in front of list. Returns 0 if success */
int list_add_front(list_t *list, T data) {
    list_elem_t *node;
    if (NULL == list || 0 == (list->size+1)) return 1;
    node = list_create_node(data);
    if (NULL == node) return 2;
    if (0 == list->size) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
    return 0;
}

/* Creates node in back of list. Returns 0 if success */
int list_add_back(list_t *list, T data) {
    list_elem_t *node;
    if (NULL == list || 0 == (list->size+1)) return 1;
    node = list_create_node(data);
    if (NULL == node) return 2;
    if (0 == list->size) {
        list->head = list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
    return 0;
}

/* Returns node by index or NULL if fails. */
static list_elem_t* list_node_at(const list_t *list, size_t i) {
    list_elem_t *curr;
    if (NULL == list) return NULL;
    for (curr = list->head; i && curr->next; i--, curr = curr->next);
    if (i) {
        return NULL;
    }
    return curr;
}


/* Return data in node[i]. Sets non-zero in err, if fails */
T list_get(const list_t *list, size_t i, int *err) {
    list_elem_t *node;
    if (NULL == list) {
        *err = 1;
        return 0;
    }
    node = list_node_at(list, i);
    if (!node) {
        *err = 2;
        return 0;
    }
    *err = 0;
    return node->data;
}


size_t list_length(const list_t *list) {
    return NULL == list ? 0 : list->size;
}


T list_sum(const list_t *list) {
    list_elem_t *curr;
    T sum = 0;
    if (NULL == list) return 0;
    for (curr = list->head; curr; curr = curr->next)
        sum += curr->data;
    return sum;
}
