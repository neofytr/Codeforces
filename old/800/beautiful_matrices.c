#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int row = 0, col = 0;
    char c;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            scanf(" %c", &c);
            if (c == '1')
            {
                row = i;
                col = j;
            }
        }
    }

    printf("%d\n", abs(row - 2) + abs(col - 2));

    return EXIT_SUCCESS;
}