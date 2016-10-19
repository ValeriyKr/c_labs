/* Made by ValeriyKr */
#include <stdio.h>

#include "hof.h"

void print_int_space(int n) {
    printf("%d ", n);
}


void print_int_nl(int n) {
    printf("%d\n", n);
}


int main() {
    list_t *list = list_create();
    size_t count;
    int err;

    if (NULL == list) {
        fputs("Error: cannot create list\n", stderr);
        return 0;
    }
    puts("Number of elements to read: ");
    for (scanf("%lu", &count); count; count--) {
        int item;
        scanf("%d", &item);
        if (0 != (err = list_add_back(list, item))) {
            fprintf(stderr, "Error: cannot insert item in list (error code %d)\n", err);
            return 0;
        }
    }
    list_foreach(list, print_int_space);
    puts("");
    list_foreach(list, print_int_nl);

    list_free(list);
    puts("Bye");

    return 0;
}
