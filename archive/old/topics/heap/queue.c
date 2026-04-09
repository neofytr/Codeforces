#include "queue.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

queue_t *create_queue(size_t elem_size, void *(*copy_func)(const void *), void (*free_func)(void *))
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
    queue->elem_size = elem_size;
    queue->copy_func = copy_func;
    queue->free_func = free_func;
    return queue;
}

bool enqueue(queue_t *queue, const void *data)
{
    if (!queue)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    queue_node_t *node = (queue_node_t *)malloc(sizeof(queue_node_t));
    if (!node)
    {
        fprintf(stderr, "ERROR: new node allocation failed: %s\n", strerror(errno));
        return false;
    }

    void *data_copy;

    if (queue->copy_func)
    {
        data_copy = queue->copy_func(data);
    }
    else
    {
        data_copy = malloc(queue->elem_size);
        if (!data_copy)
        {
            fprintf(stderr, "ERROR: data copy allocation failed: %s\n", strerror(errno));
            free(node);
            return false;
        }
        memcpy(data_copy, data, queue->elem_size);
    }

    node->data = data_copy;
    node->next = NULL;

    if (queue->back)
        queue->back->next = node;
    else
        queue->front = node;

    queue->back = node;
    queue->length++;
    return true;
}

bool front(queue_t *queue, void *data)
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

    if (queue->copy_func)
    {
        void *data_copy = queue->copy_func(queue->front->data);
        *(void **)data = data_copy;
    }
    else
    {
        memcpy(data, queue->front->data, queue->elem_size);
    }

    return true;
}

bool back(queue_t *queue, void *data)
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

    if (queue->copy_func)
    {
        void *data_copy = queue->copy_func(queue->back->data);
        *(void **)data = data_copy;
    }
    else
    {
        memcpy(data, queue->back->data, queue->elem_size);
    }

    return true;
}

bool isEmpty(queue_t *queue)
{
    return !queue || queue->length == 0;
}

bool dequeue(queue_t *queue, void *data)
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

    queue_node_t *old_front = queue->front;
    queue->front = old_front->next;

    if (data)
    {
        if (queue->copy_func)
        {
            void *data_copy = queue->copy_func(old_front->data);
            *(void **)data = data_copy;
        }
        else
        {
            memcpy(data, old_front->data, queue->elem_size);
        }
    }

    if (queue->free_func)
    {
        queue->free_func(old_front->data);
    }
    else
    {
        free(old_front->data);
    }

    if (!queue->front)
        queue->back = NULL;

    free(old_front);
    queue->length--;

    return true;
}

bool destroy_queue(queue_t *queue)
{
    if (!queue)
    {
        fprintf(stderr, "ERROR: invalid queue argument\n");
        return false;
    }

    while (!isEmpty(queue))
    {
        dequeue(queue, NULL);
    }

    free(queue);
    return true;
}

void free_queue(queue_t *queue)
{
    if (!queue)
        return;

    while (!isEmpty(queue))
    {
        dequeue(queue, NULL);
    }

    free(queue);
}