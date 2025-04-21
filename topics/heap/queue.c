#include "queue.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

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

bool enqueue(queue_t *queue, void *data)
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

    node->data = data;
    node->next = NULL;

    if (queue->back)
        queue->back->next = node;
    else
        queue->front = node;

    queue->back = node;
    queue->length++;
    return true;
}

bool front(queue_t *queue, void **data)
{
    if (!queue || !data)
    {
        fprintf(stderr, "ERROR: invalid queue or data argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform front operation\n");
        return false;
    }

    *data = queue->front->data;
    return true;
}

bool back(queue_t *queue, void **data)
{
    if (!queue || !data)
    {
        fprintf(stderr, "ERROR: invalid queue or data argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform back operation\n");
        return false;
    }

    *data = queue->back->data;
    return true;
}

bool isEmpty(queue_t *queue)
{
    return !queue || queue->length == 0;
}

bool dequeue(queue_t *queue, void **data)
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

    if (data)
        *data = old_front->data;

    if (!queue->front)
        queue->back = NULL;

    free(old_front);
    queue->length--;

    return true;
}

bool destroy_queue(queue_t *queue, void (*free_data)(void *))
{
    if (!queue)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    void *item = NULL;
    while (!isEmpty(queue))
    {
        dequeue(queue, &item);
        if (free_data && item)
            free_data(item);
    }

    free(queue);
    return true;
}

void free_queue(queue_t *queue, void (*free_data)(void *))
{
    if (!queue)
        return;

    void *item = NULL;
    while (!isEmpty(queue))
    {
        dequeue(queue, &item);
        if (free_data && item)
            free_data(item);
    }

    free(queue);
}