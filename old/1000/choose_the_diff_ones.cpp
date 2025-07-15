#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    unordered_set<int> set_a, set_b;
    vector<int> a(n), b(m);

    for (int &x : a)
    {
        cin >> x;
        set_a.insert(x);
    }

    for (int &x : b)
    {
        cin >> x;
        set_b.insert(x);
    }

    int cntA = 0, cntB = 0, cntTotal = 0;

    for (int x = 1; x <= k; x++)
    {
        bool inA = set_a.count(x);
        bool inB = set_b.count(x);
        if (inA)
            cntA++;
        if (inB)
            cntB++;
        if (inA || inB)
            cntTotal++;
    }

    if (cntA >= k / 2 && cntB >= k / 2 && cntTotal == k)
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
