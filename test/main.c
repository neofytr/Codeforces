#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int32_t a = -16;
    int32_t b = a >> 1;
    fprintf(stdout, "%d\n", b);
    return EXIT_SUCCESS;
}