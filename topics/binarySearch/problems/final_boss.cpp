#include <bits/stdc++.h>
using namespace std;

void solve()
{
    long long h, n;
    cin >> h >> n;

    vector<long long> attack(n);
    vector<long long> cooldown(n);

    for (long long &val : attack)
    {
        cin >> val;
    }

    for (long long &val : cooldown)
    {
        cin >> val;
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
}