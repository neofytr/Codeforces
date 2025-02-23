#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t k, s;
    scanf("%zu %zu", &k, &s);
    size_t count = 0;
    for (size_t x = 0; x <= k; x++)
    {
        for (size_t y = 0; y <= k; y++)
        {
            if (x + y > s)
            {
                break;
            }
            else if (s - (x + y) <= k)
            {
                count++;
            }
        }
    }

    fprintf(stdout, "%zu\n", count);
    return EXIT_SUCCESS;
}