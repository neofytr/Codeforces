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

queue_t *create(compare_t comparator)
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
    queue->compare = comparator;

    if (!queue->left || !queue->left_max || !queue->left_min ||
        !queue->right || !queue->right_max || !queue->right_min)
    {
        free(queue);
        return NULL;
    }

    return queue;
}

bool pop(queue_t *queue)
{
    if (!queue || !queue->left || !queue->left_max || !queue->left_min ||
        !queue->right || !queue->right_max || !queue->right_min)
    {
        return false;
    }

    if (is_empty_stack(queue->left))
    {
#define MAX_RETRIES 3
        TYPE temp_data[MAX_ELEMENTS];
        int count = 0;
        int retries = 0;
        bool success = true;

        while (!is_empty_stack(queue->right) && success)
        {
            TYPE data;
            top_stack(queue->right, &data);
            temp_data[count++] = data;

            pop_stack(queue->right);
            pop_stack(queue->right_max);
            pop_stack(queue->right_min);

        retry_push:
            if (!push_stack(queue->left, &data))
            {
                if (++retries < MAX_RETRIES)
                    goto retry_push;

                success = false;
                break;
            }
            retries = 0;

            if (is_empty_stack(queue->left_min))
            {
            retry_min:
                if (!push_stack(queue->left_min, &data))
                {
                    if (++retries < MAX_RETRIES)
                        goto retry_min;

                    success = false;
                    break;
                }
                retries = 0;
            }
            else
            {
                TYPE top;
                top_stack(queue->left_min, &top);
                TYPE min = (queue->compare(&top, &data) < 0) ? top : data;

            retry_min2:
                if (!push_stack(queue->left_min, &min))
                {
                    if (++retries < MAX_RETRIES)
                        goto retry_min2;

                    success = false;
                    break;
                }
                retries = 0;
            }

            if (is_empty_stack(queue->left_max))
            {
            retry_max:
                if (!push_stack(queue->left_max, &data))
                {
                    if (++retries < MAX_RETRIES)
                        goto retry_max;

                    success = false;
                    break;
                }
                retries = 0;
            }
            else
            {
                TYPE top;
                top_stack(queue->left_max, &top);
                TYPE max = (queue->compare(&top, &data) > 0) ? top : data;

            retry_max2:
                if (!push_stack(queue->left_max, &max))
                {
                    if (++retries < MAX_RETRIES)
                        goto retry_max2;

                    success = false;
                    break;
                }
                retries = 0;
            }
        }

        if (!success)
        {
            for (int i = count - 1; i >= 0; i--)
            {
                push_stack(queue->right, &temp_data[i]);

                if (is_empty_stack(queue->right_min))
                {
                    push_stack(queue->right_min, &temp_data[i]);
                }
                else
                {
                    TYPE top;
                    top_stack(queue->right_min, &top);
                    TYPE min = (queue->compare(&top, &temp_data[i]) < 0) ? top : temp_data[i];
                    push_stack(queue->right_min, &min);
                }

                if (is_empty_stack(queue->right_max))
                {
                    push_stack(queue->right_max, &temp_data[i]);
                }
                else
                {
                    TYPE top;
                    top_stack(queue->right_max, &top);
                    TYPE max = (queue->compare(&top, &temp_data[i]) > 0) ? top : temp_data[i];
                    push_stack(queue->right_max, &max);
                }
            }

            while (!is_empty_stack(queue->left))
            {
                TYPE data;
                top_stack(queue->left, &data);
                pop_stack(queue->left);
                pop_stack(queue->left_max);
                pop_stack(queue->left_min);
            }

            return false;
        }
    }

    pop_stack(queue->left);
    pop_stack(queue->left_max);
    pop_stack(queue->left_min);

    return true;
}

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

        max = (queue->compare(&max, data) > 0) ? max : *data;
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

        min = (queue->compare(&min, data) < 0) ? min : *data;
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

    *data = (queue->compare(&left_min, &right_min) < 0) ? left_min : right_min;
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

    *data = (queue->compare(&left_max, &right_max) > 0) ? left_max : right_max;
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