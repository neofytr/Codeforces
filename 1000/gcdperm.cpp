#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}

void solve()
{
    int n;
    cin >> n;

    set<int> available;
    for (int i = 1; i <= n; i++)
    {
        available.insert(i);
    }

    vector<int> perm(n);

    if (n == 2)
    {
        cout << "1 2" << endl;
        return;
    }

    perm[0] = 1;
    perm[1] = 2;
    perm[2] = 3;

    available.erase(1);
    available.erase(2);
    available.erase(3);

    for (int i = 3; i < n; i++)
    {
        int candidate = 0;

        if (i % 2 == 1)
        {
            candidate = 2 * perm[i - 1];
        }
        else
        {
            if (i - 2 >= 0)
            {
                candidate = 2 * perm[i - 2];
            }
        }

        if (candidate > 0 && candidate <= n && available.find(candidate) != available.end())
        {
            perm[i] = candidate;
        }
        else
        {
            perm[i] = *available.begin();
        }

        available.erase(perm[i]);
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