#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main()
{
    uint64_t num_of_lines;
    char line[MAX_LINE_LEN];

    if (scanf("%lu\n", &num_of_lines) < 1)
    {
        return EXIT_FAILURE;
    }

    size_t total = 0;

    while (fgets(line, MAX_LINE_LEN, stdin))
    {
        line[strcspn(line, "\n")] = '\0';
        char curr_yes = 0;
        for (size_t counter = 0; counter < strlen(line); counter++)
        {
            if (isspace(line[counter]))
            {
                continue;
            }
            else
            {
                char dig = line[counter] - '0';
                if (dig)
                {
                    curr_yes++;
                }
            }
        }

        if (curr_yes >= 2)
        {
            total++;
        }
    }

    fprintf(stdout, "%zu\n", total);

    return EXIT_SUCCESS;
}