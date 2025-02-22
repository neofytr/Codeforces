#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define N (1000)
const size_t W = (100000); // configurable value of W; in the range 0 to 10^6 (both inclusive)

int main()
{
    std::bitset<W + 1> reachable_sums; // each place i represents if the sum i is reachable by some subset for any i from 0 to W

    uint32_t *weight_arr = (uint32_t *)malloc(sizeof(uint32_t) * (size_t)N);
    if (!weight_arr)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    // initialize weight_arr here

    reachable_sums[0] = 1; // we always reach zero with the empty subset
    for (size_t counter = 0; counter < N; counter++)
    {
        reachable_sums |= reachable_sums << weight_arr[counter];
    }

    fprintf(stdout, reachable_sums[W] ? "can reach %zu\n" : "cannot reach %zu\n", W);

    free(weight_arr);
    return EXIT_SUCCESS;
}