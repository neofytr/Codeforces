#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

using ll = long long;

ll target;
bool found = false;

void find(ll curr)
{
    if (curr == target)
    {
        found = true;
        return;
    }

    if (curr > target)
        return;

    find(curr * 10);
    find(curr * 20);
}

void solve()
{
    cin >> target;
    found = false;

    find(1);

    if (found)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    FAST_IO;
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
