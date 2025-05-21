#include "stack.h"
#include <string.h>

bool push(stack_t *stack, void *data)
{
    if (!stack || !stack->top || !data)
    {
        return false;
    }

    node_t *node = malloc(sizeof(node_t));
    if (!node)
    {
        return false;
    }

    node->data = malloc(stack->data_size);
    if (!node->data)
    {
        free(node);
        return false;
    }
    memcpy(node->data, data, stack->data_size);

    node->next = stack->top;
    stack->top = node;
    stack->stack_size++;

    return true;
}

bool pop(stack_t *stack)
{
    if (!stack || !stack->top)
    {
        return false;
    }

    node_t *temp = stack->top;
    stack->top = stack->top->next;
    free(temp->data);
    free(temp);
    stack->stack_size--;

    return true;
}

bool top(stack_t *stack, void *data)
{
    if (!stack || !stack->top || !data)
    {
        return false;
    }

    memcpy(data, stack->top->data, stack->data_size);
    return true;
}

bool max(stack_t *stack, void *data)
{
    if (!stack || !stack->top || !data || !stack->compare)
    {
        return false;
    }

    node_t *current = stack->top;
    void *max_data = current->data;

    while (current)
    {
        if (stack->compare(current->data, max_data) > 0)
        {
            max_data = current->data;
        }
        current = current->next;
    }

    memcpy(data, max_data, stack->data_size);
    return true;
}

bool min(stack_t *stack, void *data)
{
    if (!stack || !stack->top || !data || !stack->compare)
    {
        return false;
    }

    node_t *current = stack->top;
    void *min_data = current->data;

    while (current)
    {
        if (stack->compare(current->data, min_data) < 0)
        {
            min_data = current->data;
        }
        current = current->next;
    }

    memcpy(data, min_data, stack->data_size);
    return true;
}

bool is_empty(stack_t *stack)
{
    if (!stack)
    {
        return true;
    }

    return stack->stack_size == 0 || stack->top == NULL;
}

bool delete(stack_t *stack)
{
    if (!stack)
    {
        return false;
    }

    while (stack->top)
    {
        pop(stack);
    }

    free(stack);
    return true;
}