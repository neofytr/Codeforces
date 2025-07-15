#include <bits/stdc++.h>
using namespace std;

bool canBeat(long long x, long long h, const vector<long long> &attack, const vector<long long> &cooldown)
{
    for (size_t i = 0; i < attack.size(); i++)
    {
        long long hits = (x + cooldown[i] - 1) / cooldown[i];
        h -= hits * attack[i];
        if (h <= 0)
            return true;
    }
    return false;
}

void solve()
{
    long long h, n;
    cin >> h >> n;

    vector<long long> attack(n);
    vector<long long> cooldown(n);

    for (long long i = 0; i < n; i++)
        cin >> attack[i];
    for (long long i = 0; i < n; i++)
        cin >> cooldown[i];

    long long left = 0, right = 1e12;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canBeat(mid, h, attack, cooldown))
            right = mid;
        else
            left = mid;
    }

    cout << right << '\n';
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
