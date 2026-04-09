#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

char **read_lines(int *num_lines)
{
    char buffer[MAX_LINE];

    if (!fgets(buffer, MAX_LINE, stdin))
        return NULL;
    *num_lines = atoi(buffer);

    if (*num_lines <= 0)
        return NULL;

    char **lines = malloc(*num_lines * sizeof(char *));
    if (!lines)
        return NULL;

    for (int i = 0; i < *num_lines; i++)
    {
        if (!fgets(buffer, MAX_LINE, stdin))
        {
            for (int j = 0; j < i; j++)
                free(lines[j]);
            free(lines);
            return NULL;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        lines[i] = strdup(buffer);
        if (!lines[i])
        {
            for (int j = 0; j < i; j++)
                free(lines[j]);
            free(lines);
            return NULL;
        }
    }

    return lines;
}

void free_lines(char **lines, int num_lines)
{
    if (!lines)
        return;
    for (int i = 0; i < num_lines; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

int main()
{
    int num_of_lines;
    char **lines;
    if (!(lines = read_lines(&num_of_lines)))
    {
        free_lines(lines, num_of_lines);
        return EXIT_FAILURE;
    }

    for (size_t counter = 0; counter < num_of_lines; counter++)
    {
        fprintf(stdout, "%s\n", lines[counter]);
    }

    return EXIT_SUCCESS;
}