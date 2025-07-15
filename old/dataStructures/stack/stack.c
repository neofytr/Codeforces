#include "stack.h"
#include <string.h>

// global array to track min and max stacks for each created stack
static stack_tracking_t stack_tracker[MAX_STACKS] = {0};
static int next_stack_id = 0;

static int int_compare(void *a, void *b)
{
    int *int_a = (int *)a;
    int *int_b = (int *)b;
    return *int_a - *int_b;
}

static int get_next_stack_id()
{
    for (int i = 0; i < MAX_STACKS; i++)
    {
        if (!stack_tracker[i].in_use)
        {
            stack_tracker[i].in_use = true;
            return i;
        }
    }
    return -1; // no more stack IDs available
}

stack_t *create_stack(size_t data_size, compare_t compare)
{
    int stack_id = get_next_stack_id();
    if (stack_id == -1)
    {
        return NULL; // no more available stack IDs
    }

    stack_t *stack = malloc(sizeof(stack_t));
    if (!stack)
    {
        stack_tracker[stack_id].in_use = false;
        return NULL;
    }

    stack->compare = compare ? compare : int_compare; // default to int_compare if NULL
    stack->data_size = data_size;
    stack->stack_size = 0;
    stack->top = NULL;
    stack->stack_id = stack_id;

    stack_tracker[stack_id].min_stack = malloc(sizeof(stack_t));
    stack_tracker[stack_id].max_stack = malloc(sizeof(stack_t));

    if (!stack_tracker[stack_id].min_stack || !stack_tracker[stack_id].max_stack)
    {
        if (stack_tracker[stack_id].min_stack)
            free(stack_tracker[stack_id].min_stack);
        if (stack_tracker[stack_id].max_stack)
            free(stack_tracker[stack_id].max_stack);
        free(stack);
        stack_tracker[stack_id].in_use = false;
        return NULL;
    }

    // Initialize min stack
    stack_tracker[stack_id].min_stack->compare = stack->compare;
    stack_tracker[stack_id].min_stack->data_size = data_size;
    stack_tracker[stack_id].min_stack->stack_size = 0;
    stack_tracker[stack_id].min_stack->top = NULL;
    stack_tracker[stack_id].min_stack->stack_id = -1; // special ID to avoid recursion

    stack_tracker[stack_id].max_stack->compare = stack->compare;
    stack_tracker[stack_id].max_stack->data_size = data_size;
    stack_tracker[stack_id].max_stack->stack_size = 0;
    stack_tracker[stack_id].max_stack->top = NULL;
    stack_tracker[stack_id].max_stack->stack_id = -1; // special ID to avoid recursion

    return stack;
}

static bool _push(stack_t *stack, void *data)
{
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

bool push(stack_t *stack, void *data)
{
    if (!stack || !data)
    {
        return false;
    }

    if (stack->stack_id < 0)
    {
        return _push(stack, data);
    }

    int stack_id = stack->stack_id;

    if (!_push(stack, data))
    {
        return false;
    }

    void *min_value = data;
    if (!is_empty(stack_tracker[stack_id].min_stack))
    {
        void *temp = malloc(stack->data_size);
        if (!temp)
        {
            pop(stack);
            return false;
        }

        top(stack_tracker[stack_id].min_stack, temp);
        if (stack->compare(data, temp) > 0)
        {
            min_value = temp;
        }
        else
        {
            free(temp);
        }
    }

    if (!_push(stack_tracker[stack_id].min_stack, min_value))
    {
        if (min_value != data)
            free(min_value);
        pop(stack);
        return false;
    }

    if (min_value != data)
        free(min_value);

    void *max_value = data;
    if (!is_empty(stack_tracker[stack_id].max_stack))
    {
        void *temp = malloc(stack->data_size);
        if (!temp)
        {
            pop(stack);
            pop(stack_tracker[stack_id].min_stack);
            return false;
        }

        top(stack_tracker[stack_id].max_stack, temp);
        if (stack->compare(data, temp) < 0)
        {
            max_value = temp;
        }
        else
        {
            free(temp);
        }
    }

    if (!_push(stack_tracker[stack_id].max_stack, max_value))
    {
        if (max_value != data)
            free(max_value);
        pop(stack);
        pop(stack_tracker[stack_id].min_stack);
        return false;
    }

    if (max_value != data)
        free(max_value);

    return true;
}

static bool _pop(stack_t *stack)
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

bool pop(stack_t *stack)
{
    if (!stack)
    {
        return false;
    }

    if (stack->stack_id < 0)
    {
        return _pop(stack);
    }

    int stack_id = stack->stack_id;

    if (!_pop(stack))
    {
        return false;
    }

    _pop(stack_tracker[stack_id].min_stack);
    _pop(stack_tracker[stack_id].max_stack);

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
    if (!stack || !data)
    {
        return false;
    }

    if (stack->stack_id >= 0)
    {
        int stack_id = stack->stack_id;
        return top(stack_tracker[stack_id].max_stack, data);
    }

    if (!stack->top || !stack->compare)
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
    if (!stack || !data)
    {
        return false;
    }

    if (stack->stack_id >= 0)
    {
        int stack_id = stack->stack_id;
        return top(stack_tracker[stack_id].min_stack, data);
    }

    if (!stack->top || !stack->compare)
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

static bool _delete(stack_t *stack)
{
    if (!stack)
    {
        return false;
    }

    while (stack->top)
    {
        _pop(stack);
    }

    free(stack);
    return true;
}

bool delete(stack_t *stack)
{
    if (!stack)
    {
        return false;
    }

    if (stack->stack_id < 0)
    {
        return _delete(stack);
    }

    int stack_id = stack->stack_id;

    _delete(stack_tracker[stack_id].min_stack);
    _delete(stack_tracker[stack_id].max_stack);

    stack_tracker[stack_id].in_use = false;

    while (stack->top)
    {
        _pop(stack);
    }

    free(stack);
    return true;
}