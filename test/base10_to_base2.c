#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "wrong format\n!");
        return EXIT_FAILURE;
    }

    uint32_t a = strtoul(argv[1], NULL, 10);
    for (int32_t counter = 31; counter >= 0; counter--)
    {
        if ((1U << counter) & a)
        {
            fprintf(stdout, "1");
        }
        else
        {
            fprintf(stdout, "0");
        }
    }

    fprintf(stdout, "\n");
}