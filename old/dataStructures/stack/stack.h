#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACKS 100

typedef struct node_ node_t;
typedef int (*compare_t)(void *data_one, void *data_two);

struct node_
{
    struct node_ *next;
    void *data;
};

typedef struct
{
    node_t *top;
    size_t stack_size;
    size_t data_size;
    compare_t compare;
    int stack_id;
} stack_t;

typedef struct
{
    stack_t *min_stack;
    stack_t *max_stack;
    bool in_use;
} stack_tracking_t;

stack_t *create_stack(size_t data_size, compare_t compare);
bool push(stack_t *stack, void *data);
bool pop(stack_t *stack);
bool top(stack_t *stack, void *data);
bool max(stack_t *stack, void *data);
bool min(stack_t *stack, void *data);
bool is_empty(stack_t *stack);
bool delete(stack_t *stack);

#endif