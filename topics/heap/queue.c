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

bool enqueue(queue_t *queue, search_t search)
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

    search_t *search_data = (search_t *)malloc(sizeof(search_t));
    if (!search_data)
    {
        fprintf(stderr, "ERROR: search data allocation failed: %s\n", strerror(errno));
        free(node);
        return false;
    }

    search_data->data = search.data;
    search_data->index = search.index;

    node->data = search_data;
    node->next = NULL;

    if (queue->back)
        queue->back->next = node;
    else
        queue->front = node;

    queue->back = node;
    queue->length++;
    return true;
}

bool front(queue_t *queue, search_t *search)
{
    if (!queue || !search)
    {
        fprintf(stderr, "ERROR: invalid queue or search argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform front operation\n");
        return false;
    }

    search_t *front_data = (search_t *)queue->front->data;
    search->data = front_data->data;
    search->index = front_data->index;
    return true;
}

bool back(queue_t *queue, search_t *search)
{
    if (!queue || !search)
    {
        fprintf(stderr, "ERROR: invalid queue or search argument\n");
        return false;
    }

    if (isEmpty(queue))
    {
        fprintf(stderr, "ERROR: queue is empty; can't perform back operation\n");
        return false;
    }

    search_t *back_data = (search_t *)queue->back->data;
    search->data = back_data->data;
    search->index = back_data->index;
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

    // Free the search_t data stored in the node
    free(old_front->data);
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
        dequeue(queue);

    free(queue);
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