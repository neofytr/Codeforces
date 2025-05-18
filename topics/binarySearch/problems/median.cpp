#include <bits/stdc++.h>
using namespace std;

bool canMake(long long target, vector<long long> &arr, long long k)
{
    long long n = arr.size();
    long long cost = 0;

    for (int i = n / 2; i < n; i++)
    {
        if (arr[i] < target)
        {
            cost += target - arr[i];
            if (cost > k)
                return false;
        }
    }

    return true;
}

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    sort(arr.begin(), arr.end());

    long long left = arr[n / 2];
    long long right = arr[n - 1] + k + 1;

    while (right - left > 1)
    {
        long long mid = left + (right - left) / 2;
        if (canMake(mid, arr, k))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    cout << left << endl;
    return 0;
}
