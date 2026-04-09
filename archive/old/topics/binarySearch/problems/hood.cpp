// https://codeforces.com/contest/2014/problem/C

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    if (n < 3)
    {
        cout << -1 << endl;
        return;
    }

    sort(arr.begin(), arr.end());

    int r = n / 2;

    long long x = max(0LL, 2 * arr[r] * n - accumulate(arr.begin(), arr.end(), 0LL) + 1);
    cout << x << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
}