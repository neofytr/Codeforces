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

#define TYPE int

// memory allocation method selection
// set to 1 to use custom memory allocator, 0 to use standard malloc/free
#define USE_CUSTOM_ALLOCATOR 0

// memory allocation macros that switch between allocation methods
#if USE_CUSTOM_ALLOCATOR
#define MEM_ALLOC(size) ((size) == sizeof(node_t) ? mem_alloc() : malloc(size))
#define MEM_FREE(ptr) (mem_free(ptr))
#define MEM_INIT(size) (mem_init(size))
#else
#define MEM_ALLOC(size) (malloc(size))
#define MEM_FREE(ptr) (free(ptr))
#define MEM_INIT(size) (true)
#endif

// singly linked list

typedef struct node_ {
    struct node_ *next;
    TYPE data;
} node_t;

typedef struct {
    node_t *head;
    int len;
} list_t;

list_t *list_create(size_t min_size);

bool list_insert(list_t *list, int index, const TYPE *element);

bool list_remove(list_t *list, int index, TYPE *element);

bool list_empty(const list_t *list);

bool list_append(list_t *list, const TYPE *element);

bool list_pop(list_t *list, TYPE *element);

bool list_delete(list_t *list, TYPE *element);

bool list_get(list_t *list, int index, TYPE *element);

#endif //LINKED_LIST_H
