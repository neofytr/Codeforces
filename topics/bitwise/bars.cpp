#include <bits/stdc++.h>
using namespace std;

#define MAX 1000

void solve()
{
    int target;
    cin >> target;

    int n;
    cin >> n;

    bitset<MAX + 1> reachable;
    reachable[0] = true;
    int val;

    for (int index = 0; index < n; index++)
    {
        cin >> val;

        // update all reachable values by val
        reachable[val] = true;
        reachable |= reachable << val;
    }

    if (reachable[target])
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
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

    return EXIT_SUCCESS;
}