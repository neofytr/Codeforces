// https://cses.fi/problemset/task/1623

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int64_t> arr(n);
    int64_t total = 0;
    for (int64_t &val : arr)
    {
        cin >> val;
        total += val;
    }

    int64_t min_diff = INT64_MAX;
    for (uint32_t choice = 0; choice < (1U << n); choice++)
    {
        int64_t first = 0;
        for (int i = 0; i < n; i++)
        {
            if (choice & (1U << i))
                first += arr[i];
        }
        int64_t second = total - first;
        min_diff = min(min_diff, abs(first - second));
    }

    cout << min_diff << endl;
}
