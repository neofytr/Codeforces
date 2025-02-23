#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

using namespace std;

void simulate_second(vector<int64_t> &state)
{
    for (int64_t &value : state)
    {
        value--;
    }
}

bool is_the_step_correct(vector<int64_t> &state)
{
    for (int64_t &value : state)
    {
        if (value <= 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int64_t t, n;
    scanf("%zu", &t);

    for (int64_t counter = 0; counter < t; counter++)
    {
        scanf("%zu", &n);
        vector<int64_t> init_state(n);
        for (int64_t &value : init_state)
        {
            scanf("%zu", &value);
        }
    }
    return EXIT_SUCCESS;
}