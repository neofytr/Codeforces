#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ll = long long;
using vll = vector<ll>;

void solve()
{
    ll n, k;
    cin >> n >> k;

    vll divisors;

    for (ll d = 1; d * d <= n; d++)
    {
        if (n % d == 0)
        {
            divisors.push_back(d);
            if (d != n / d)
                divisors.push_back(n / d);
        }
    }

    sort(divisors.begin(), divisors.end());

    if (k > divisors.size())
        cout << -1 << endl;
    else
        cout << divisors[k - 1] << endl;
}

int main()
{
    FAST_IO;
    solve();
    return 0;
}
