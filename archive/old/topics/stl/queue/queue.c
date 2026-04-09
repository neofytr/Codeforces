#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node_
{
    int data;
    struct node_ *next;
} node_t;

typedef struct queue_
{
    node_t *front; // deletion at front
    node_t *back;  // insertion at back
    size_t length;
} queue_t;

queue_t *create_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue));
    if (!queue)
    {
        fprintf(stderr, "ERROR: queue creation failed: %s\n", strerr(errno));
        return NULL;
    }

    queue->front = (node_t *)malloc(sizeof(node_t));
    if (!queue->front)
    {
        fprintf(stderr, "ERROR: queue front allocation failed: %s\n", strerr(errno));
        return NULL;
    }

    queue->back = (node_t *)malloc(sizeof(node_t));
    if (queue->back)
    {
        fprintf(stderr, "ERROR: queue back allocation failed: %s\n", strerr(errno));
        return NULL;
    }

    queue->front->next = NULL;
    queue->front->data = 0;

    queue->back->next = NULL;
    queue->back->data = 0;

    queue->length = 0;

    return queue;
}

bool enqueue(queue_t *queue, int element)
{
    if (!queue || !queue->back || !queue->front)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: new node allocation failed: %s\n", strerr(errno));
        return false;
    }

    node->data = element;
    node->next = NULL;

    queue->back->next = node;
    queue->length++;

    return true;
}

bool front(queue_t *queue, int *element)
{
    if (!queue || !queue->back || !queue->front)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform front operation\n");
        return false;
    }

    *element = queue->front->data;
    return true;
}

bool back(queue_t *queue, int *element)
{
    if (!queue || !queue->back || !queue->front)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform back operation\n");
        return false;
    }

    *element = queue->back->data;
    return true;
}

bool isEmpty(queue_t *queue)
{
    return !queue->length;
}

bool dequeue(queue_t *queue)
{
    if (!queue || !queue->back || !queue->front)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't dequeue\n");
        return false;
    }

    node_t *new_front = queue->front->next;
    free(queue->front);
    queue->front = new_front;
    queue->length--;

    return true;
}