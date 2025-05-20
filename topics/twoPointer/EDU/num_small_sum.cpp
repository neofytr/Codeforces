#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, s;
    cin >> n >> s;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = 0;
    long long sum = 0;
    long long count = 0;

    // the subarrays can either start at index 0, 1, .., n - 1
    // all these cases are mutually exclusive and exhaustive

    while (left < n)
    {
        // count the number of subarrays starting at left
        while (sum + arr[right] <= s && right < n)
        {
            sum += arr[right++];
        }

        count += right - left;

        sum -= arr[left++];
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}