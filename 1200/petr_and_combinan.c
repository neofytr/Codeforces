#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n;
    scanf("%d", &n);

    int rotations[15] = {0};

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &rotations[i]);
    }

    for (size_t counter = 0; counter < n; counter++)
    {
        fprintf("%d\n", rotations[counter]);
    }

    return 0;
}