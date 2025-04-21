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
} queue_t;

queue_t *create_queue();
bool enqueue(queue_t *queue, void *element);
bool front(queue_t *queue, void **element);
bool back(queue_t *queue, void **element);
bool isEmpty(queue_t *queue);
bool dequeue(queue_t *queue);
void free_queue(queue_t *queue);

#endif
