#include <bits/stdc++.h>
using namespace std;

long long solve(int index, vector<long long> &arr, vector<long long> &dp, long long *sum)
{
    if (index >= arr.size())
    {
        return 0;
    }

    if (dp[index] != -1)
    {
        return dp[index];
    }

    long long more = solve(index + 1, arr, dp, sum);
    *sum = max(*sum, dp[index] = max(more + arr[index], arr[index]));

    return dp[index];
}

int main()
{
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    vector<long long> dp(n, -1);
    // dp[r] is the maximum subarray sum for a subarray starting at r; 0 <= r < n
    long long max_sum = LLONG_MIN;
    solve(0, arr, dp, &max_sum);

    cout << max_sum << endl;
    return EXIT_SUCCESS;
}