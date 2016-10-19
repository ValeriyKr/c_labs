/* Made by ValeriyKr */
#include <stdio.h>

#include "list.h"

int print_list(const list_t *list);

int main() {
    list_t *list = list_create();
    size_t count;
    int item, err;

    if (NULL == list) {
        fputs("Error: cannot create list\n", stderr);
        return 0;
    }
    puts("Number of elements to read: ");
    for (scanf("%lu", &count); count; count--) {
        int item;
        scanf("%d", &item);
        if (0 != (err = list_add_front(list, item))) {
            fprintf(stderr, "Error: cannot insert item in list (error code %d)\n", err);
            return 0;
        }
    }
    printf("Elements count: %lu, elements:\n", list_length(list));
    /* Yes, it is O(n*n) and it is bad
     * It is possible to improve this with functions for getting sublists and
     * iterating on them. */
    if (print_list(list)) {
        return 0;
    }
    printf("\nList sum: %d\nItem index: ", list_sum(list));
    scanf("%lu", &count);
    item = list_get(list, count, &err);
    if (0 == err) {
        list_t *tail = list_tail(list, count);
        printf("Item: %d\n", item);
        puts("Tail:");
        if (print_list(tail)) {
            list_free(list);
            list_free(tail);
            return 0;
        }
        puts("\nFree original…\nTail:");
        list_free(list);
        if (print_list(tail)) {
            list_free(tail);
            return 0;
        }
        puts("\nFree tail…");
        list_free(tail);
    } else {
        list_free(list);
        printf("Item not found. There are only %lu items in list.\n", list_length(list));
    }
    puts("Bye");

    return 0;
}


int print_list(const list_t *list) {
    size_t count;
    int err;
    for (count = 0; count < list_length(list); count++) {
        int item = list_get(list, count, &err);
        if (0 == err) {
            printf("%d ", item);
            fflush(stdout);
        } else {
            fprintf(stderr, "Error: cannot access to element by index (error code %d)\n", err);
            return 1;
        }
    }
    return 0;
}
