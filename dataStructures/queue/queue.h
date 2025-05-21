#include <stdlib.h>

#define TYPE int

typedef struct node_ node_t;
typedef bool (*compare_t)(TYPE *data_one, TYPE *data_two);

struct node_
{
    struct node_ *next;
    TYPE data;
};

typedef struct
{
    node_t *top;
    size_t size;
} stack_t;

typedef struct
{
    stack_t *left;
    stack_t *left_min;
    stack_t *left_max;
    stack_t *right;
    stack_t *right_max;
    stack_t *right_min;
} queue_t;

queue_t *create();
bool pop(queue_t *queue);
bool push(queue_t *queue, TYPE *data);
bool min(queue_t *queue, TYPE *data);
bool max(queue_t *queue, TYPE *data);
bool is_empty(queue_t *queue);
