#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n, l, r, x;
    scanf("%d %d %d %d", &n, &l, &r, &x);

    int difficulties[15];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &difficulties[i]);
    }

    // - n: the number of problems
    // - l: minimum total difficulty
    // - r: maximum total difficulty
    // - x: minimum difference between hardest and easiest
    // - difficulties[]: array containing all problem difficulties

    for (int set = 0; set < (1 << n); set++)
    {
        if (set == 1 || !(set & (set - 1)))
        {
            continue;
        }
        int difficulty = 0;
        int exceeded = false;
        int min = difficulties[0];
        int max = difficulties[0];
        for (int test = 0; test < n; test++)
        {
            difficulty += ((1 << test) & set) ? difficulties[test] : 0;
            if (difficulties[test] < min)
            {
                min = difficulties[test];
            }
            if (difficulties[test] > max)
            {
                max = difficulties[test];
            }
            if (difficulty > r)
            {
                exceeded = true;
                break;
            }
        }

        if (!exceeded && difficulty &&)
        {
        }
    }

    return 0;
}