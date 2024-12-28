#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t M;
    size_t N;
    if (fscanf(stdin, "%zu %zu", &M, &N) < 0)
    {
        return EXIT_FAILURE;
    }

    size_t min = (M <= N) ? M : N;
    size_t max = (M >= N) ? M : N;

    size_t num_of_tiles = 0;

    if (!(min & 1UL))
    {
        num_of_tiles = (max * (min >> 1UL));
    }
    else
    {
        num_of_tiles = (max * ((min - 1) >> 1UL) + (max >> 1UL));
    }

    fprintf(stdout, "%zu\n", num_of_tiles);
    return EXIT_SUCCESS;
}
