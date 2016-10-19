/* Made by ValeriyKr */
#ifndef _HOF_H_
#define _HOF_H_

#include "../lab4/list.h"

void list_foreach(const list_t *, void (*)(T));
list_t* list_map(const list_t *, T (*)(T));
void list_map_mut(list_t *, T (*)(T));

#endif /* _HOF_H_ */
