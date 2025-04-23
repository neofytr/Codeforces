#include "dequeue.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "memalloc.h"

#if USE_CUSTOM_ALLOCATOR
#define MEM_ALLOC(size) ((size) > BLOCK_SIZE ? mem_alloc() : malloc(size))
#define MEM_FREE(ptr) (mem_free(ptr))
#define MEM_INIT(size) (mem_init(size))
#else
#define MEM_ALLOC(size) (malloc(size))
#define MEM_FREE(ptr) (free(ptr))
#define MEM_INIT(size) (true)
#endif

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

    node_t *new_node = MEM_ALLOC(sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "ERROR: couldn't allocate memory for the node: %s\n", strerror(errno));
        return false;
    }

    queue->len++;

    // handle the case when the queue is empty
    if (isEmpty(queue)) {
        new_node->next = NULL;
        new_node->prev = NULL;
        memcpy((void *) &new_node->data, element, sizeof(TYPE));

        queue->back = queue->front = new_node;

        return true;
    }

    // queue has at least one element now
    node_t *back = queue->back;
    back->next = new_node;
    new_node->prev = back;
    new_node->next = NULL;
    queue->back = new_node;

    return true;
}

bool push_front(queue_t *queue, const TYPE *element) {
    if (!queue) {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (!element) {
        fprintf(stderr, "ERROR: invalid element argument\n");
        return false;
    }

    node_t *new_node = MEM_ALLOC(sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "ERROR: couldn't allocate memory for the node: %s\n", strerror(errno));
        return false;
    }

    queue->len++;

    // handle the case when the queue is empty
    if (isEmpty(queue)) {
        new_node->next = NULL;
        new_node->prev = NULL;
        memcpy((void *) &new_node->data, element, sizeof(TYPE));

        queue->back = queue->front = new_node;

        return true;
    }

    // queue has at least one element now
    node_t *front = queue->front;
    front->prev = new_node;
    new_node->next = front;
    new_node->prev = NULL;
    queue->back = new_node;
    return true;
}

bool pop_back(queue_t *queue, TYPE *element) {
    if (!queue) {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue)) {
        fprintf(stderr, "ERROR: the queue is empty; can't pop\n");
        return false;
    }

    // queue has length of at least one now
    queue->len--;

    node_t *back = queue->back;
    queue->back = back->prev;
    queue->back->next = NULL;

    if (element) {
        memcpy((void *) element, (void *) &front->data, sizeof(TYPE));
    }

    MEM_FREE(back);
    return true;
}

bool pop_front(queue_t *queue, TYPE *element) {
    if (!queue) {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue)) {
        fprintf(stderr, "ERROR: the queue is empty; can't pop\n");
        return false;
    }

    // queue has length of at least one now
    queue->len--;

    node_t *front = queue->front;
    queue->front = front->next;
    queue->front->prev = NULL;

    if (element) {
        memcpy((void *) element, (void *) &front->data, sizeof(TYPE));
    }

    MEM_FREE(front);
    return true;
}

bool front(queue_t *queue, TYPE *element) {
}

bool back(queue_t *queue, TYPE *element);

size_t length(queue_t *queue);

bool isEmpty(queue_t *queue);
