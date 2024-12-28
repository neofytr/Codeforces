#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LEN 10

int main()
{
    char buff[MAX_LINE_LEN];
    size_t num_of_lines;
    if (fscanf(stdin, "%zu\n", &num_of_lines) < 0)
    {
        return EXIT_FAILURE;
    }

    int64_t x = 0;

    while (fgets(buff, MAX_LINE_LEN, stdin))
    {
        buff[strcspn(buff, "\n")] = '\0';

        bool is_neg;
        for (size_t counter = 0; counter < strlen(buff); counter++)
        {
            if (buff[counter] == '-')
            {
                is_neg = true;
            }
            else if (buff[counter] == '+')
            {
                is_neg = false;
            }
        }

        if (is_neg)
        {
            x--;
        }
        else
        {
            x++;
        }
    }

    fprintf(stdout, "%ld\n", x);
}