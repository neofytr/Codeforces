#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    if (n == 2)
    {
        // For n=2, any permutation gives only 1 distinct GCD
        cout << "1 2" << endl;
        return;
    }

    // For n >= 3, we can create a permutation with exactly n distinct GCDs
    vector<int> perm;

    // Add all powers of 2 first (they will create distinct GCDs with each other)
    for (int i = 1; i <= n; i *= 2)
    {
        perm.push_back(i);
    }

    for (int i = 3; i <= n; i += 2)
    {
        if (find(perm.begin(), perm.end(), i) == perm.end())
        {
            perm.push_back(i);
        }
    }

    for (int i = 6; i <= n; i += 4)
    {
        if (find(perm.begin(), perm.end(), i) == perm.end())
        {
            perm.push_back(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (find(perm.begin(), perm.end(), i) == perm.end())
        {
            perm.push_back(i);
        }
    }

    for (int val : perm)
    {
        cout << val << " ";
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}