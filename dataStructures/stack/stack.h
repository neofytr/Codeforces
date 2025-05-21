#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct node_ node_t;

struct node_
{
    struct node_ *next;
    void *data;
}

typedef struct
{
    node_t *top;
    size_t stack_size;
    size_t data_size;
} stack_t;

stack_t *create_stack(size_t data_size);
bool push(stack_t *stack, void *data);
bool pop(stack_t *stack);
bool top(stack_t *stack, void *data);
bool is_empty(stack_t *stack);
bool delete(stack_t *stack);

#endif