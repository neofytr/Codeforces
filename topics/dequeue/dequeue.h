#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <stddef.h>
#include <stdbool.h>

#define TYPE int

#define USE_CUSTOM_ALLOCATOR 1 // 1 enables the custom allocator, 0 uses malloc/free

#if USE_CUSTOM_ALLOCATOR
#define MEM_ALLOC(size) ((size) == sizeof(node_t) ? mem_alloc() : malloc(size))
#define MEM_FREE(ptr) (mem_free(ptr))
#define MEM_INIT(size) (mem_init(size))
#else
#define MEM_ALLOC(size) (malloc(size))
#define MEM_FREE(ptr) (free(ptr))
#define MEM_INIT(size) (true)
#endif

typedef struct node_ {
    struct node_ *next;
    struct node_ *prev;
    TYPE data;
} node_t;

typedef struct {
    node_t *front;
    node_t *back;
    size_t len;
} queue_t;

queue_t *create_queue(size_t min_blocks);

bool push_back(queue_t *queue, const TYPE *element);

bool push_front(queue_t *queue, const TYPE *element);

bool pop_back(queue_t *queue, TYPE *element);

bool pop_front(queue_t *queue, TYPE *element);

bool front(queue_t *queue, TYPE *element);

bool back(queue_t *queue, TYPE *element);

size_t length(queue_t *queue);

bool isEmpty(queue_t *queue);

#endif //DEQUEUE_H
