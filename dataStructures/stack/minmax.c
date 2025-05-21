#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main()
{
    stack_t *max_stack = create_stack(sizeof(int));
    stack_t *min_stack = create_stack(sizeof(int));
    stack_t *stack = create_stack(sizeof(int));

    if (!min_stack || !max_stack || !stack)
    {
        return EXIT_FAILURE;
    }

    int n;
    scanf("%d\n", &n);

    while (n--)
    {
        int op, x;
        scanf("%d %d\n", &op, &x);

        if (op == 1)
        {
            // push(x)
            push(stack, &x);

            if (!is_empty(max_stack))
            {
                int maxelt;
                top(max_stack, &maxelt);

                maxelt = (x > maxelt ? x : maxelt);
                push(max_stack, &maxelt);
            }
            else
            {
                push(max_stack, &x);
            }

            if (!is_empty(min_stack))
            {
                int minelt;
                top(min_stack, &minelt);

                minelt = (x < minelt ? x : minelt);
                push(min_stack, &minelt);
            }
            else
            {
                push(min_stack, &x);
            }
        }
        else if (!op)
        {
            // pop(x)
            pop(stack);
            pop(min_stack);
            pop(max_stack);
        }
        else
        {
            fprintf(stderr, "INVALID OPERATION CODE %d\n", op);
            delete(stack);
            delete(min_stack);
            delete(max_stack);
            return EXIT_FAILURE;
        }

        int max, min;
        top(min_stack, &min);
        top(max_stack, &max);

        fprintf(stdout, "MIN: %d, MAX: %d\n", min, max);
    }

    delete(stack);
    delete(min_stack);
    delete(max_stack);
    return EXIT_SUCCESS;
}