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

    int left = 0;
    int right = 0;
    long long sum = 0;
    int min_len = INT_MAX;

    while (left < n)
    {
        while (right < n && sum < s)
        {
            sum += arr[right++];
        }

        if (sum >= s)
        {
            min_len = min(min_len, right - left);
            sum -= arr[left++];
        }
        else
        {
            break;
        }
    }

    if (min_len == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << min_len << endl;
    }

    // method 2

    left = right = sum = 0;
    min_len = INT_MAX;

    while (right < n)
    {
        // include the element at the right ptr
        sum += arr[right++];

        while (sum - arr[left] >= s)
        {
            sum -= arr[left++];
        }

        if (sum >= s)
        {
            min_len = min(min_len, right - left);
        }
    }

    if (min_len == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << min_len << endl;
    }

    return EXIT_SUCCESS;
}