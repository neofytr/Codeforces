// https://atcoder.jp/contests/abc179/tasks/abc179_d

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

void solve()
{
    long long n, k;
    cin >> n >> k;

    vector<pair<long long, long long>> segments(k);

    // all segments are non-long longersecting

    long long l, r;
    for (auto &seg : segments)
    {
        cin >> l >> r;
        seg.first = l;
        seg.second = r;
    }

    // dp[r] is the number of ways to get to r from the starting position (1)
    vector<long long> dp(n + 1, 0);
    vector<long long> prefix(n + 1, 0);
    dp[1] = 1; // since we are starting at 1
    prefix[1] = 1;

    for (long long index = 2; index < n + 1; index++)
    {
        for (auto seg : segments)
        {
            long long left = index - seg.second;
            long long right = index - seg.first;

            if (right >= 1)
            {
                dp[index] = (dp[index] + prefix[right] - (left > 1 ? prefix[left - 1] : 0) + MOD) % MOD;
            }
        }

        prefix[index] = (prefix[index - 1] + dp[index]) % MOD;
    }

    cout << dp[n] % MOD << endl;
}

int main()
{

    solve();

    return 0;
}