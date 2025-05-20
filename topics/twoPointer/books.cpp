// https://codeforces.com/contest/279/problem/B

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, t;
    cin >> n >> t;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    // we find the max of the max segment starting at index 0, 1,  ..., n - 1

    long long left = 0;
    long long right = 0;
    long long max_val = 0;
    long long rem_time = t;

    while (left < n)
    {
        while (right < n && rem_time >= arr[right])
        {
            rem_time -= arr[right++];
        }

        max_val = max(max_val, right - left);

        rem_time += arr[left++];
    }

    cout << max_val << endl;
    return EXIT_SUCCESS;
}