#include "dequeue.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "memalloc.h"

queue_t *create_queue(size_t min_blocks) {
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));
    if (!queue) {
        fprintf(stderr, "ERROR: couldn't allocate the queue structure: %s\n", strerror(errno));
        return NULL;
    }

    queue->len = 0;
    queue->back = NULL;
    queue->front = NULL;

    if (!MEM_INIT(min_blocks)) {
        fprintf(stderr, "ERROR: failed to initialize the allocator\n");
        free(queue);
        return NULL;
    }

    return queue;
}

bool isEmpty(queue_t *queue) {
    return !queue || !queue->len;
}

bool push_back(queue_t *queue, const TYPE *element) {
    if (!queue) {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    node_t *new_node = mem_alloc();
    if (!new_node) {
        fprintf(stderr, "ERROR: couldn't allocate memory for the node: %s\n", strerror(errno));
        return false;
    }

    // handle the case when the queue is empty
    if (isEmpty(queue)) {
        new_node->next = NULL;
        new_node->prev = NULL;
        memcpy((void *) &new_node->data, element, sizeof(TYPE));

        queue->back = queue->front = new_node;

        return true;
    }

    // queue has atleast one element now
    node_t *back = queue->back;
    back->next = new_node;
    new_node->prev = back;
    new_node->next = NULL;

    return true;
}

queue_t *push_front(queue_t *queue, const TYPE *element);

queue_t *pop_back(queue_t *queue, TYPE *element);

bool front(queue_t *queue, TYPE *element);

bool back(queue_t *queue, TYPE *element);

size_t length(queue_t *queue);

bool isEmpty(queue_t *queue);
