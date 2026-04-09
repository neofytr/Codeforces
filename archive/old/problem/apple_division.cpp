#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

int main()
{
    size_t n;
    scanf("%zu", &n);

    vector<size_t> weights(n);
    int64_t max = INT64_MIN;
    int64_t min = INT64_MAX;

    for (size_t subset = 0; subset < 2 << n; subset++)
    {
        int64_t sum = 0;
        for (size_t test = 0; test < n; test++)
        {
            sum += ((subset & (1 << test)) ? weights[test] : 0);
        }
        if (sum < min)
        {
            min = sum;
        }
        if (sum > max)
        {
            max = sum;
        }
    }

    fprintf(stdout, "%ld\n", max - min);
}