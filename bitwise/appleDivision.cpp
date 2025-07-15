// https://cses.fi/problemset/task/1623

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
        cin >> val;

    long long total = accumulate(arr.begin(), arr.end(), 0LL);
    long long minimum = LONG_LONG_MAX;
    for (int subset = 0; subset < (1 << n); subset++)
    {
        long long curr = 0;
        for (int bit = 0; bit < n; bit++)
        {
            if (subset & (1 << bit))
                curr += arr[bit];
        }

        if (minimum > abs(2 * curr - total))
            minimum = abs(2 * curr - total);
    }

    cout << minimum << endl;
    return EXIT_SUCCESS;
}