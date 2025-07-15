#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main()
{
    stack_t *stack = create_stack(sizeof(int), NULL);

    if (!stack)
    {
        fprintf(stderr, "Failed to create stack\n");
        return EXIT_FAILURE;
    }

    int n;
    scanf("%d", &n);

    while (n--)
    {
        int op, x;
        scanf("%d %d", &op, &x);

        if (op == 1)
        {
            if (!push(stack, &x))
            {
                fprintf(stderr, "Push operation failed\n");
                delete(stack);
                return EXIT_FAILURE;
            }
        }
        else if (op == 0)
        {
            if (!is_empty(stack))
                pop(stack);
        }
        else
        {
            fprintf(stderr, "INVALID OPERATION CODE %d\n", op);
            delete(stack);
            return EXIT_FAILURE;
        }

        if (!is_empty(stack))
        {
            int max_val, min_val;
            if (max(stack, &max_val) && min(stack, &min_val))
            {
                // printf("MIN: %d, MAX: %d\n", min_val, max_val);
            }
        }
    }

    delete(stack);
    return EXIT_SUCCESS;
}