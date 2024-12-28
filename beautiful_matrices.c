#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    char buf[5][5];
    if (fread(buf, sizeof(char), 5 * 5, stdin) < 5 * 5)
    {
        return EXIT_FAILURE;
    }

    
}