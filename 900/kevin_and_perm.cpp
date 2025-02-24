#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> p(n);
    vector<bool> used(n + 1, false);

    for (int i = k - 1; i < n; i += k)
    {
        p[i] = i / k + 1;
        used[i / k + 1] = true;
    }

    int next_num = 1;
    for (int i = 0; i < n; i++)
    {
        if (p[i] == 0)
        {
            while (next_num <= n && used[next_num])
            {
                next_num++;
            }
            p[i] = next_num;
            used[next_num] = true;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << p[i] << " ";
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