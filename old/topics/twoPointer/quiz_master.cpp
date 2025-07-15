#include <bits/stdc++.h>
using namespace std;

bool possible(long long diff, int m, const vector<long long> &arr, const vector<vector<int>> &divisors)
{
    vector<int> prof(m + 1, 0);
    int covered = 0;
    int n = arr.size() - 1;

    int left = 1, right = 1;
    while (left <= n)
    {
        // find if there is a team starting at left
        // extend window as much as possible
        while (right <= n && arr[right] - arr[left] <= diff)
        {
            for (int d : divisors[right])
            {
                if (++prof[d] == 1)
                    covered++;
            }
            right++;
        }

        // check if we found a valid team
        if (covered == m)
            return true;

        // move left pointer and update proficiency
        for (int d : divisors[left])
        {
            if (!(--prof[d]))
                covered--;
        }
        left++;
    }

    return false;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<long long> arr(n + 1); // 1-based indexing
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    sort(arr.begin() + 1, arr.end());

    // precalculate which among 1 <= r <= m divide each of arr[index] for 1 <= index <= n in divisor[index]
    vector<vector<int>> divisors(n + 1);
    for (int i = 1; i <= n; i++)
    {
        long long x = arr[i];
        for (int d = 1; d * 1LL * d <= x && d <= m; d++)
        {
            if (!(x % d))
            {
                if (d <= m)
                    divisors[i].push_back(d);
                long long other = x / d;
                if (other != d && other <= m)
                    divisors[i].push_back(other);
            }
        }
    }

    long long left = -1;                   // not even possible to have this
    long long right = arr[n] - arr[1] + 1; // nice upper bound

    while (right > left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (possible(mid, m, arr, divisors))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << (right < arr[n] - arr[1] + 1 ? right : -1) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}