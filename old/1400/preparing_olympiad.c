#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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

    int ways = 0;

    for (int set = 0; set < (1 << n); set++)
    {
        if (!(set & (set - 1)) || !set) // check if set is a power of two; since at least two problems are required
        {
            continue;
        }
        int difficulty = 0;
        int exceeded = false;
        int min = INT32_MAX;
        int max = INT32_MIN;
        for (int test = 0; test < n; test++)
        {
            difficulty += ((1 << test) & set) ? difficulties[test] : 0;
            if (((1 << test) & set) && difficulties[test] < min)
            {
                min = difficulties[test];
            }
            if (((1 << test) & set) && difficulties[test] > max)
            {
                max = difficulties[test];
            }
            if (difficulty > r)
            {
                exceeded = true;
                break;
            }
        }

        if (!exceeded && difficulty <= r && difficulty >= l && (max - min) >= x)
        {
            ways++;
        }
    }

    fprintf(stdout, "%d\n", ways);
    return 0;
}