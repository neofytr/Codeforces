#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node_ {
    int data;
    struct node_ *next;
} node_t;

typedef struct queue_ {
    node_t *front; // deletion at front
    node_t *back; // insertion at back
    size_t length;
} queue_t;

queue_t *creat_queue();

bool enqueue(queue_t *queue, int element);

bool front(queue_t *queue, int *element);

bool back(queue_t *queue, int *element);

bool isEmpty(queue_t *queue);

bool dequeue(queue_t *queue);