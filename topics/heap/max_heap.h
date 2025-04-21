#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "queue.h"
#include "dynarr.h"

// a max heap is a complete binary tree such that the parent >= its two children

// elements of the max heap are non-negative integers
typedef dyn_arr_t max_heap_t;

max_heap_t *max_heap_create();
bool max_heap_insert(max_heap_t *max_heap, int element);
bool max_heap_delete(max_heap_t *max_heap, int *element);

#endif