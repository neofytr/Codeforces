#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

using namespace std;

int main()
{
    int64_t t;
    scanf("%ld", &t);

    for (int64_t counter = 0; counter < t; counter++)
    {
        int64_t n;
        scanf("%ld", &n);
        vector<int64_t> init_state(n);
        for (int64_t &value : init_state)
        {
            scanf("%ld", &value);
        }

        bool possible = true;

        for (size_t index = 0; index < n; index++)
        {
            if (init_state[index] <= 2 * max(index, n - 1 - index))
            {
                possible = false;
                break;
            }
        }

        printf("%s\n", possible ? "YES" : "NO");
    }
    return EXIT_SUCCESS;
}