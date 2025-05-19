#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Returns how many picks of element i have values >= threshold
ll picks_for_threshold(ll a, ll b, ll threshold)
{
    if (a < threshold)
        return 0;
    // Solve for x: a - (x-1)*b >= threshold
    // (x-1) <= (a - threshold)/b
    // x <= (a - threshold)/b + 1
    return 1 + (a - threshold) / b;
}

// Sum of arithmetic progression for x picks from element i
// sum_i(x) = x * a - b * (x * (x-1) / 2)
ll sum_for_picks(ll a, ll b, ll x)
{
    return x * a - b * (x * (x - 1) / 2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n), b(n);
        for (auto &x : a)
            cin >> x;
        for (auto &x : b)
            cin >> x;

        // Binary search for the value threshold
        ll left = 0, right = 2e9 + 10; // large enough upper bound
        while (left < right)
        {
            ll mid = (left + right + 1) / 2;
            ll total_picks = 0;
            for (int i = 0; i < n; i++)
            {
                total_picks += picks_for_threshold(a[i], b[i], mid);
                if (total_picks > k)
                    break; // no need to count more
            }
            if (total_picks >= k)
                left = mid; // can achieve this threshold
            else
                right = mid - 1;
        }

        ll threshold = left;
        ll total_picks = 0, score = 0;

        // Calculate total score picking all values >= threshold
        for (int i = 0; i < n; i++)
        {
            ll cnt = picks_for_threshold(a[i], b[i], threshold);
            total_picks += cnt;
            score += sum_for_picks(a[i], b[i], cnt);
        }

        // If we picked more than k, remove the excess picks with value == threshold
        ll excess = total_picks - k;
        score -= excess * threshold;

        cout << score << "\n";
    }
}
