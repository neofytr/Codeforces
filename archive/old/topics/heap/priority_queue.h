#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "max_heap.h"

typedef max_heap_t priority_queue_t;

bool priority_queue_push(priority_queue_t *priority_queue, int element);
bool priority_queue_pop(priority_queue_t *priority_queue, int *element);
bool priority_queue_empty(priority_queue_t *priority_queue);

#endif
