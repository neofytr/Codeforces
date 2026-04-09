#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#define N 100000
const size_t MAX_NUM = 10000000;  

int main()
{
    std::bitset<MAX_NUM> unique;
    
    uint32_t *arr = (uint32_t *)malloc(sizeof(uint32_t) * (size_t)N);
    if (!arr)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t counter = 0; counter < N; counter++)
    {
        if (arr[counter] < MAX_NUM) {
            unique.set(arr[counter]);
        }
    }

    fprintf(stdout, "num of unique numbers is: %zu\n", unique.count());
    
    free(arr);
    return EXIT_SUCCESS;
}