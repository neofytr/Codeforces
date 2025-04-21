#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define  INIT_STACK_CAP (16)

typedef struct stack_
{
    int* arr;
    size_t length;
    size_t capacity;
} stack_t;

stack_t* create_stack()
{
    stack_t* stack = malloc(sizeof(stack_t));
    if (!stack)
    {
        fprintf(stderr, "ERROR: stack creation failed: %s\n", strerror(errno));
        return NULL;
    }

    stack->arr = malloc((sizeof(int) * INIT_STACK_CAP));
    if (!stack->arr)
    {
        fprintf(stderr, "ERROR: stack array creation failed: %s\n", strerror(errno));
        return false;
    }

    stack->capacity = INIT_STACK_CAP;
    stack->length = 0;

    return stack;
}

bool isEmpty(stack_t* stack)
{
    if (!stack)
    {
        fprintf(stderr, "ERROR: invalid stack argument\n");
        return false;
    }

    return stack->length == 0;
}

bool pop(stack_t* stack)
{
    if (!stack || !stack->arr)
    {
        fprintf(stderr, "ERROR: invalid stack argument\n");
        return false;
    }

    if (isEmpty(stack))
    {
        fprintf(stderr, "ERROR: invalid pop operation; stack is empty\n");
        return false;
    }


}

bool push(stack_t* stack, int element)
{
}
