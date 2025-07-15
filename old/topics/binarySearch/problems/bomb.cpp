// https://codeforces.com/contest/1996/problem/F

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> a(n);
    vector<long long> b(n);

    for (long long &val : a)
        cin >> val;
    for (long long &val : b)
        cin >> val;

    // max-heap of pairs: (value, index)
    priority_queue<pair<long long, long long>> pq;

    for (long long index = 0; index < n; index++)
    {
        pq.push({a[index], index});
    }

    long long score = 0;

    for (long long op = 0; op < k && !pq.empty(); op++)
    {
        auto [val, idx] = pq.top();
        pq.pop();

        score += val;

        long long next_val = val - b[idx];
        if (next_val > 0)
            pq.push({next_val, idx});
    }

    cout << score << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
}