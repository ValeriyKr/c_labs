/* Made by ValeriyKr */
#include <stdio.h>
#include <limits.h>

#include "hof.h"

void print_int_space(int n) {
    printf("%d ", n);
}


void print_int_nl(int n) {
    printf("%d\n", n);
}


int square(int n) {
    return n*n;
}


int cubic(int n) {
    return n*n*n;
}


int sum(int a, int b) {
    return a+b;
}


int min(int a, int b) {
    return a < b ? a : b;
}


int max(int a, int b) {
    return a < b ? b : a;
}


int mul_at_2(int n) {
    return 2*n;
}


int main() {
    list_t *list = list_create(), *new_list, *degrees;
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
    if (NULL == (new_list = list_map(list, square))) {
        list_free(list);
        fputs("Error while mapping list\n", stderr);
        return 0;
    }
    list_foreach(new_list, print_int_space);
    list_map_mut(list, cubic);
    puts("");
    list_foreach(list, print_int_space);

    puts("\nNew list:");
    list_foreach(new_list, print_int_space);
    printf("\nSum: %d\n", list_foldl(new_list, sum, 0));
    printf("Min: %d\n", list_foldl(new_list, min, INT_MAX));
    printf("Max: %d\n", list_foldl(new_list, max, INT_MIN));

    list_free(new_list);
    list_free(list);

    if (NULL != (degrees = list_iterate(10, mul_at_2, 2))) {
        puts("Degrees:");
        list_foreach(degrees, print_int_space);
        list_free(degrees);
    }

    puts("\nBye");

    return 0;
}
