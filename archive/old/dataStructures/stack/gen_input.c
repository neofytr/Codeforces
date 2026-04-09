#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_OPS 1000000
#define MAX_VAL 1000000

int main()
{
    FILE *f = fopen("test_input.txt", "w");
    if (!f)
    {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));

    // Number of operations
    fprintf(f, "%d\n", MAX_OPS);

    int stack_size = 0;

    for (int i = 0; i < MAX_OPS; ++i)
    {
        int op;
        if (!stack_size)
        {
            op = 1;
        }
        else
        {
            op = rand() % 2;
        }

        if (op == 1)
        {
            int x = rand() % MAX_VAL;
            fprintf(f, "1 %d\n", x);
            stack_size++;
        }
        else
        {
            fprintf(f, "0 0\n");
            stack_size--;
        }
    }

    fclose(f);
    return 0;
}
