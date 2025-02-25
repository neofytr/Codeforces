#include <stdio.h>

int main()
{
    char str[256];

    scanf("%s", str);

    char *ptr = str;

    while (*ptr)
    {
        if (*ptr == 's' && *(ptr + 1) == 's')
        {
            printf("hiss\n");
            return 0;
        }
        ptr++;
    }

    return 0;
}
