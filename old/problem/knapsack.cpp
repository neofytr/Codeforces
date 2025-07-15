#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define N (1000)           // Maximum number of items
const size_t W = (100000); // Maximum weight sum that can be checked

int main()
{
    // `reachable_sums[i]` is 1 if a subset sum `i` can be achieved, 0 otherwise.
    std::bitset<W + 1> reachable_sums;

    // Dynamic allocation for weight array
    uint32_t *weight_arr = (uint32_t *)malloc(sizeof(uint32_t) * (size_t)N);
    if (!weight_arr)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    // Initialize weight_arr (e.g., read from input)

    // Base case: sum 0 is always achievable using an empty subset
    reachable_sums[0] = 1;

    // Iterate through each weight and update reachable sums
    for (size_t counter = 0; counter < N; counter++)
    {
        // since we can now reach each of the previous reachable sums + weight_arr[counter], we can
        // now reach the all the sums reachable_sums << weight_arr[counter] due to the addition of the new 
        // weight; since we could already reach the sums reachable_sums before, the total sums we can now 
        // reach are reachable_sums |= reachable_sums << weight_arrp[counter]
        
        // Update reachable sums by shifting left by weight_arr[counter] 
        // This ensures all previously reachable sums now extend to `i + weight_arr[counter]`
        reachable_sums |= reachable_sums << weight_arr[counter];
    }

    // Print whether the exact sum W is achievable
    fprintf(stdout, reachable_sums[W] ? "can reach %zu\n" : "cannot reach %zu\n", W);

    // Free allocated memory
    free(weight_arr);
    return EXIT_SUCCESS;
}