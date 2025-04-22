//
// Created by raj on 22/4/25.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_LIST_LEN (1000000)
#define TYPE int

typedef struct {
    TYPE arr[MAX_LIST_LEN];
    int next[MAX_LIST_LEN];
    int holes[MAX_LIST_LEN];
    int head;
    int hole_index;
    int list_len;
} list_t;

list_t *list_create();

bool list_insert(list_t *list, int index, const TYPE *element);

bool list_remove(list_t *list, int index, TYPE *element);

bool list_empty(const list_t *list);

bool list_append(list_t *list, TYPE *element);

bool list_pop(list_t *list, TYPE *element);

bool list_delete(list_t *list, TYPE *element);

bool list_get(list_t *list, int index, TYPE *element);

#endif //LINKED_LIST_H
