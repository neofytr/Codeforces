#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    size_t t, n;
    scanf("%zu", &t);

    for (size_t counter = 0; counter < t; counter++)
    {
        scanf("%zu", &n);
        vector<size_t> init_state;
        for (size_t index = 0; index < n; index++)
        {
            scanf("%zu", &init_state[index]);
        }
    }
    return EXIT_SUCCESS;
}