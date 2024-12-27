#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
int main()
{
    char buff[MAX_LEN];
    size_t num_of_lines = 0;
    scanf("%zu\n", &num_of_lines);

    while (scanf("%s\n", buff) > 0)
    {
        size_t len = strlen(buff);
        if (len > 10)
        {
            fprintf(stdout, "%c%zu%c\n", buff[0], len - 2, buff[len - 1]);
        }
        else
        {
            fprintf(stdout, "%s\n", buff);
        }
    }
}