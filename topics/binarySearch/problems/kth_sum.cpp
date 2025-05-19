#include <bits/stdc++.h>
using namespace std;

long long count(long long target, const vector<long long> &a, const vector<long long> &b)
{
    long long cnt = 0;
    for (const auto &val : a)
    {
        auto it = upper_bound(b.begin(), b.end(), target - val);
        cnt += (it - b.begin());
    }
    return cnt;
}

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> a(n);
    vector<long long> b(n);

    for (long long &val : a)
    {
        cin >> val;
    }

    for (long long &val : b)
    {
        cin >> val;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // we need to find the kth number (0-indexed) in the final sorted array
    // count(x) returns the number of elements in the final array that are less than or equal to x
    // we need to find the minimum x such that count(x) >= k + 1; for this x, count(x) == k + 1 and there will be such an x which is also in the array,
    // since the array is guaranteed to have an element at index k

    long long left = a[0] + b[0];
    long long right = a[n - 1] + b[n - 1];
    long long ans = -1;

    while (right >= left)
    {
        long long mid = left + (right - left) / 2;
        if (count(mid, a, b) >= k)
        {
            right = mid - 1;
            ans = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << ans << endl;
    return EXIT_SUCCESS;
}
