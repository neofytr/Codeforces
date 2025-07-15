#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    if (k == 2 || k == 3 || k == 5)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] % k == 0)
            {
                cout << 0 << endl;
                return;
            }
        }

        int min_ops = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int ops = (k - (a[i] % k)) % k;
            min_ops = min(min_ops, ops);
        }

        cout << min_ops << endl;
        return;
    }

    if (k == 4)
    {
        for (int i = 0; i < n; i++)
        {
            if (a[i] % 4 == 0)
            {
                cout << 0 << endl;
                return;
            }
        }

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] % 2 == 0)
            {
                cnt++;
            }
        }

        int min_ops_for_one = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int ops = (4 - (a[i] % 4)) % 4;
            min_ops_for_one = min(min_ops_for_one, ops);
        }

        int min_ops_for_two = INT_MAX;
        if (n >= 2)
        {
            min_ops_for_two = max(0, 2 - cnt);
        }

        cout << min(min_ops_for_one, min_ops_for_two) << endl;
        return;
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