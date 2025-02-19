#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_FILE_LEN 1024
#define MAX_STR_LEN 256

int main()
{
    char str_one[MAX_STR_LEN];
    char str_two[MAX_STR_LEN];
    char file[MAX_FILE_LEN];

    size_t bytes_read = fread(file, sizeof(char), MAX_FILE_LEN, stdin);
    if (bytes_read == 0 && ferror(stdin))
    {
        perror("fread");
        return EXIT_FAILURE;
    }

    size_t curr = 0;
    size_t index = 0;

    while (file[curr] != '\n' && curr < bytes_read && index < MAX_STR_LEN - 1)
    {
        str_one[index++] = file[curr++];
    }
    str_one[index] = '\0';

    if (curr < bytes_read && file[curr] == '\n')
        curr++;

    index = 0;
    while (file[curr] != '\n' && curr < bytes_read && index < MAX_STR_LEN - 1)
    {
        str_two[index++] = file[curr++];
    }
    str_two[index] = '\0';

    size_t len_one = strlen(str_one);
    size_t len_two = strlen(str_two);

    if (len_one != len_two)
    {
        return EXIT_FAILURE;
    }

    for (size_t counter = 0; counter < len_one; counter++)
    {
        if (tolower(str_one[counter]) < tolower(str_one[counter]))
        {
            fprintf(stdout, "-1");
            break;
        }
        else if (tolower(str_one[counter]) > tolower(str_two[counter]))
        {
            fprintf(stdout, "1");
            break;
        }
        else
        {
            fprintf(stdout, "0");
            break;
        }
    }
    return EXIT_SUCCESS;
}