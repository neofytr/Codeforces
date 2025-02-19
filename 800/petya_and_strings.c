#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_LEN 1024
#define MAX_STR_LEN 256

int main()
{
    char str_one[MAX_STR_LEN];
    char str_two[MAX_STR_LEN];
    char file[MAX_FILE_LEN];

    if (fread(file, sizeof(char), MAX_FILE_LEN, stdin) == -1)
    {
        perror("fread");
        return EXIT_FAILURE;
    }

    size_t curr = 0;
    while (file[curr] != '\n' && curr < MAX_STR_LEN - 1)
    {
        str_one[curr++] = file[curr++];
    }

    str_one[curr] = 0;

    curr++;
    size_t index = 0;
    while (file[curr] != '\n' && index < MAX_STR_LEN - 1)
    {
        str_one[index++] = file[curr++];
    }

    str_one[index] = 0;

    fprintf(stdout, "%s %s\n", str_one, str_two);
}