/* Made by ValeriyKr */
#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

typedef int T;
typedef struct list_elem_t list_elem_t;
typedef struct list_t list_t;

list_t* list_create();
int list_add_front(list_t *, T);
int list_add_back(list_t *, T);
T list_get(list_t *, size_t, int*);
void list_free(list_t *);
size_t list_length(list_t *);
T list_sum(list_t *);

#endif /* _LIST_H_ */
