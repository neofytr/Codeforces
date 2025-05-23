// https://codeforces.com/contest/1882/problem/B

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> sets(n, vector<int>());
    int k, temp;
    for (int index = 0; index < n; index++)
    {
        cin >> k;
        while (k--)
        {
            cin >> temp;
            sets[index].push_back(temp);
        }
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