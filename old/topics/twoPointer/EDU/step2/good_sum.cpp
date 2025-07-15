#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long s;
    cin >> n >> s;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    // a segment of the array (l, r), where 0 <= l <= r < n, is good if the
    // sum of the elements in this segment is <= s

    // we need to find the longest good segment, i.e, we need to find
    // max (r - l + 1, where 0 <= l <= r < n such that  summation (l <= k <= r) of arr[k] <= s)
    // if there are no such segments, print 0

    // a good segment can start either at index 0, or at 1, ..., or at n - 1
    // these cases are mutually exclusive and exhaustive

    int left = 0;
    int right = 0;
    int max_len = 0;
    long long sum = 0;

    while (left < n)
    {
        while (right < n && sum + arr[right] <= s)
        {
            sum += arr[right++];
        }

        max_len = max(max_len, right - left);
        sum -= arr[left++];
    }

    cout << max_len << endl;

    // another method
    left = right = sum = max_len = 0;

    while (right < n)
    {
        // include element at right pointer
        sum += arr[right++];

        // remove elements from the left until sum <= s
        while (sum > s)
        {
            sum -= arr[left++];
        }

        max_len = max(max_len, right - left);
    }

    cout << max_len << endl;

    return EXIT_SUCCESS;
}