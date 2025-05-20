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
    long long min_val = LLONG_MAX;

    while (right < n)
    {
        // include the element at ptr right
        sum += arr[right];

        // remove from left uptil we can
        while (sum - arr[left] >= s)
        {
            sum -= arr[left++];
        }

        // if sum is atleast s, we have found a segment
        if (sum >= s)
        {
            min_val = min(min_val, right - left + 1);
        }
        right++;
    }

    if (min_val == LLONG_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << min_val << endl;
    }

    // a simpler version
    left = right = sum = 0;
    min_val = LLONG_MAX;

    while (right < n)
    {
        // include the element at the right ptr
        sum += arr[right++];

        while (sum >= s)
        {
            min_val = min(min_val, right - left);
            sum -= arr[left++];
        }
    }

    if (min_val == LLONG_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << min_val << endl;
    }

    return EXIT_SUCCESS;
}