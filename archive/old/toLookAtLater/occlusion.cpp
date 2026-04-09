// https://atcoder.jp/contests/abc395/tasks/abc395_f

#include <bits/stdc++.h>
using namespace std;

bool fit(long long budget, long long x, vector<long long> &upper, vector<long long> &lower)
{
    int n = upper.size();
    // try all possible H = U[i] + D[i] after grinding (H ≤ U[i] + D[i])
    long long min_possible_H = LLONG_MAX;

    for (int i = 0; i < n; i++)
    {
        min_possible_H = min(min_possible_H, upper[i] + lower[i]);
    }

    for (long long H = min_possible_H; H >= 0; H--)
    {
        // dp[i]: min/max possible value of U[i] after enforcing continuity constraint
        vector<long long> lo(n), hi(n);

        lo[0] = max(0LL, H - lower[0]);
        hi[0] = min(upper[0], H);

        for (int i = 1; i < n; i++)
        {
            lo[i] = max(lo[i - 1] - x, max(0LL, H - lower[i]));
            hi[i] = min(hi[i - 1] + x, min(upper[i], H));
            if (lo[i] > hi[i])
                goto next_H; // no valid range
        }

        // backtrack to assign final U[i] values within lo[i]...hi[i]
        vector<long long> final_upper(n);
        final_upper[n - 1] = lo[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            final_upper[i] = min(hi[i], final_upper[i + 1] + x);
            final_upper[i] = max(final_upper[i], lo[i]);
        }

        // total cost = sum of grindings on U[i] and D[i]
        long long cost = 0;
        for (int i = 0; i < n; i++)
        {
            long long new_upper = final_upper[i];
            long long new_lower = H - new_upper;
            if (new_upper > upper[i] || new_lower > lower[i])
            {
                cost = budget + 1; // invalid
                break;
            }
            cost += (upper[i] - new_upper) + (lower[i] - new_lower);
            if (cost > budget)
                break;
        }

        if (cost <= budget)
            return true;

    next_H:;
    }

    return false;
}

int main()
{
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> upper(n), lower(n);
    long long max_len = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> upper[i] >> lower[i];
        max_len = max({max_len, upper[i], lower[i]});
    }

    long long left = -1, right = 2 * max_len * n;
    while (right - left > 1)
    {
        long long mid = left + (right - left) / 2;
        if (fit(mid, x, upper, lower))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << right << '\n';
    return EXIT_SUCCESS;
}
