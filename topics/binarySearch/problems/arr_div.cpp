// https://cses.fi/problemset/task/1085

#include <bits/stdc++.h>
using namespace std;

bool canMake(long long target, int k, const vector<long long> &arr)
{
    int count = 1;
    long long curr = 0;
    for (int i = 0; i < (int)arr.size(); ++i)
    {
        if (arr[i] > target)
            return false; // cannot split if one element is too big

        if (curr + arr[i] > target)
        {
            count++;
            curr = arr[i];
        }
        else
        {
            curr += arr[i];
        }
    }
    return count <= k;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<long long> arr(n);
    for (auto &x : arr)
        cin >> x;

    long long left = 0, right = 1e18; // large enough upper bound

    while (left < right)
    {
        long long mid = left + (right - left) / 2;
        if (canMake(mid, k, arr))
            right = mid;
        else
            left = mid + 1;
    }

    cout << left << '\n';
    return 0;
}
