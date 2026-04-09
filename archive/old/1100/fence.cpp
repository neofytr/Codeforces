#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> heights(n);
    vector<int> prefix(n + 1);
    prefix[0] = 0;

    for (int &val : heights)
    {
        cin >> val;
    }

    // compute prefix
    for (int index = 1; index < n + 1; index++)
    {
        prefix[index] = heights[index - 1] + prefix[index - 1];
    }

    // we need to find the k-length subarray (of consecutive elements) with the minimum sum
    // and print the first index of that subarray

    int min = 0;
    int min_sum = prefix[k] - prefix[0];
    int sum;
    for (int index = 0; index < n - k + 1; index++)
    {
        // compute the sum of elements from index to index + k - 1
        sum = prefix[index + k] - prefix[index];
        if (sum < min_sum)
        {
            min_sum = sum;
            min = index;
        }
    }

    cout << min + 1 << endl;
}

int main()
{
    solve();
    return 0;
}