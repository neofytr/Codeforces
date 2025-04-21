#include "queue.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

queue_t *create_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    if (!queue)
    {
        fprintf(stderr, "ERROR: queue creation failed: %s\n", strerror(errno));
        return NULL;
    }
    queue->front = NULL;
    queue->back = NULL;
    queue->length = 0;
    return queue;
}

bool enqueue(queue_t *queue, void *element)
{
    if (!queue)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: new node allocation failed: %s\n", strerror(errno));
        return false;
    }

    node->data = element;
    node->next = NULL;

    if (queue->back)
        queue->back->next = node;
    else
        queue->front = node;

    queue->back = node;
    queue->length++;
    return true;
}

bool front(queue_t *queue, void **element)
{
    if (!queue || !element)
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

bool back(queue_t *queue, void **element)
{
    if (!queue || !element)
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
    return !queue || queue->length == 0;
}

bool dequeue(queue_t *queue)
{
    if (!queue)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't dequeue\n");
        return false;
    }

    node_t *old_front = queue->front;
    queue->front = old_front->next;

    if (!queue->front)
        queue->back = NULL;

    free(old_front);
    queue->length--;

    return true;
}

void free_queue(queue_t *queue)
{
    if (!queue)
        return;
    while (!isEmpty(queue))
        dequeue(queue);
    free(queue);
}
