#include "queue.h"
#include <string.h>

static stack_t *create_stack();
static bool push_stack(stack_t *stack, TYPE *data);
static void pop_stack(stack_t *stack);
static bool is_empty_stack(stack_t *stack);
static void top_stack(stack_t *stack, TYPE *data);

static bool is_empty_stack(stack_t *stack)
{
    return !stack->size;
}

static void top_stack(stack_t *stack, TYPE *data)
{
    memcpy(&stack->top->data, data);
}

static void pop_stack(stack_t *stack)
{
    node_t *temp = stack->top;
    stack->top = temp->next;
    free(temp);
    stack->size--;
}

static bool push_stack(stack_t *stack, TYPE *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
    {
        return false;
    }

    memcpy(&node->data, data, sizeof(TYPE));
    node->next = stack->top;
    stack->top = node;
    stack->size++;

    return true;
}

stack_t *create_stack()
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (!stack)
    {
        return NULL;
    }

    stack->top = NULL;
    stack->size = 0;
    return stack;
}

queue_t *create()
{
    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
    {
        return NULL;
    }

    queue->left = create_stack();
    queue->left_max = create_stack();
    queue->left_min = create_stack();
    queue->right = create_stack();
    queue->right_max = create_stack();
    queue->right_min = create_stack();

    if (!queue->left || !queue->left_max || !queue->left_min ||
        !queue->right || !queue->right_max || !queue->right_min)
    {
        free(queue);
        return NULL;
    }

    return queue;
}

// if pop fails, we are in serious trouble
// the queue structure is completely altered beyond repair
// let's hope it never fails
bool pop(queue_t *queue)
{
    if (!queue || !queue->left || !queue->left_max || !queue->left_min ||
        !queue->right || !queue->right_max || !queue->right_min)
    {
        return false;
    }

    // we pop from the back (left end)

    if (is_empty_stack(queue->left))
    {
        // if the left stack has become empty, convert right stack into left, and then pop
        while (!is_empty_stack(queue->right))
        {
            TYPE data;
            top_stack(queue->right, &data);

            pop_stack(queue->right);
            pop_stack(queue->right_max);
            pop_stack(queue->right_min);

            if (!push_stack(queue->left, &data))
            {
                return false;
            }

            if (is_empty_stack(queue->left_min))
            {
                if (!push_stack(queue->left_min, &data))
                {
                    return false;
                }
            }
            else
            {
                TYPE top;
                top_stack(queue->left_min, &top);

                TYPE min = (top < data) ? top : data;
                if (!push_stack(queue->left_min, &min))
                {
                    return false;
                }
            }

            if (is_empty_stack(queue->left_max))
            {
                if (!push_stack(queue->left_max, &data))
                {
                    return false;
                }
            }
            else
            {
                TYPE top;
                top_stack(queue->left_max, &top);

                TYPE max = (top > data) ? top : data;
                if (!push_stack(queue->left_max, &max))
                {
                    return false;
                }
            }
        }
    }

    pop_stack(queue->left);
    pop_stack(queue->left_max);
    pop_stack(queue->left_min);

    return true;
}

// if push fails, we can be sure that our queue isn't altered
bool push(queue_t *queue, TYPE *data)
{
    if (!queue || !queue->left || !queue->left_max || !queue->left_min ||
        !queue->right || !queue->right_max || !queue->right_min || !data)
    {
        return false;
    }

    if (!push_stack(queue->right, data))
    {
        return false;
    }

    if (is_empty_stack(queue->right_max))
    {
        if (!push_stack(queue->right_max, data))
        {
            pop_stack(queue->right);
            return false;
        }
    }
    else
    {
        TYPE max;
        top_stack(queue->right_max, &max);

        max = (max > *data) ? max : *data;
        if (!push_stack(queue->right_max, &max))
        {
            pop_stack(queue->right);
            return false;
        }
    }

    if (is_empty_stack(queue->right_min))
    {
        if (!push_stack(queue->right_min, data))
        {
            pop_stack(queue->right);
            pop_stack(queue->right_max);
            return false;
        }
    }
    else
    {
        TYPE min;
        top_stack(queue->right_min, &min);

        min = (min < *data) ? min : *data;
        if (!push_stack(queue->right_min, &min))
        {
            pop_stack(queue->right);
            pop_stack(queue->right_max);
            return false;
        }
    }

    return true;
}

bool min(queue_t *queue, TYPE *data)
{
    if (!queue || !data || !queue->left_min || !queue->right_min)
    {
        return false;
    }

    if (is_empty_stack(queue->left_min) && is_empty_stack(queue->right_min))
    {
        return false;
    }

    if (is_empty_stack(queue->left_min))
    {
        return top_stack(queue->right_min, data);
    }

    if (is_empty_stack(queue->right_min))
    {
        return top_stack(queue->left_min, data);
    }

    TYPE left_min, right_min;
    if (!top_stack(queue->left_min, &left_min) || !top_stack(queue->right_min, &right_min))
    {
        return false;
    }

    *data = (left_min < right_min) ? left_min : right_min;
    return true;
}

bool max(queue_t *queue, TYPE *data)
{
    if (!queue || !data || !queue->left_max || !queue->right_max)
    {
        return false;
    }

    if (is_empty_stack(queue->left_max) && is_empty_stack(queue->right_max))
    {
        return false;
    }

    if (is_empty_stack(queue->left_max))
    {
        return top_stack(queue->right_max, data);
    }

    if (is_empty_stack(queue->right_max))
    {
        return top_stack(queue->left_max, data);
    }

    TYPE left_max, right_max;
    if (!top_stack(queue->left_max, &left_max) || !top_stack(queue->right_max, &right_max))
    {
        return false;
    }

    *data = (left_max > right_max) ? left_max : right_max;
    return true;
}

bool is_empty(queue_t *queue)
{
    if (!queue || !queue->left || !queue->right)
    {
        return true;
    }

    return is_empty_stack(queue->left) && is_empty_stack(queue->right);
}