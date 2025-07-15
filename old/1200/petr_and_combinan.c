#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int rotations[15] = {0};

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &rotations[i]);
    }

    for (int set = 0; set < (1 << n); set++)
    {
        int sum = 0;
        for (int test = 0; test < n; test++)
        {
            sum += ((1 << test) & set) ? -rotations[test] : rotations[test];
        }

        if (!(sum % 360))
        {
            fprintf(stdout, "YES");
            return EXIT_SUCCESS;
        }
    }

    fprintf(stdout, "NO");
    return EXIT_SUCCESS;
}