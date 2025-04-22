#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "dynarr.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define TYPE int

// this is a singly linked list
typedef struct list_ {
    dyn_arr_t *arr;
    dyn_arr_t *next;
    size_t head_index;
} list_t;

bool list_append(list_t *list, TYPE *element);

bool list_pop(list_t *list, TYPE *element);

bool list_insert(list_t *list, int index, TYPE *element);

bool list_remove(list_t *list, int index, TYPE *element);

bool list_empty(list_t *list);

list_t *list_create();

bool list_free(list_t *list);

#endif //LINKED_LIST_H
