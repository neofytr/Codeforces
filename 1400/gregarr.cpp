// https://codeforces.com/contest/295/problem/A

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    size_t n, m, k;
    cin >> n >> m >> k;

    vector<size_t> arr(n);
    for (size_t &val : arr)
    {
        cin >> val;
    }

    // l and r follow one based indexing; we change them to zero based by doing l--, r--;
    vector<tuple<size_t, size_t, size_t>> operations(m); // l, r, d

    for (auto &trips : operations)
    {
        
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}