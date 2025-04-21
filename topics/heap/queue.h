#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node_
{
    void *data;
    struct node_ *next;
} node_t;

typedef struct queue_
{
    node_t *front;
    node_t *back;
    size_t length;
    size_t elem_size;
    void *(*copy_func)(const void *);
    void (*free_func)(void *);
} queue_t;

queue_t *create_queue(size_t elem_size, void *(*copy_func)(const void *), void (*free_func)(void *));
bool enqueue(queue_t *queue, const void *data);
bool front(queue_t *queue, void *data);
bool back(queue_t *queue, void *data);
bool isEmpty(queue_t *queue);
bool dequeue(queue_t *queue, void *data);
bool destroy_queue(queue_t *queue);
void free_queue(queue_t *queue);

#endif /* QUEUE_H */