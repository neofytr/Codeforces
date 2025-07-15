#include "priority_queue.h"

bool priority_queue_push(priority_queue_t *priority_queue, int element)
{
    return max_heap_insert(priority_queue, element);
}

bool priority_queue_pop(priority_queue_t *priority_queue, int *element)
{
    return max_heap_delete(priority_queue, element);
}

bool priority_queue_empty(priority_queue_t *priority_queue)
{
    return priority_queue->is_empty;
}