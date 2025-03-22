#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string a, b;
    cin >> a >> b;

    int len = a.length(); // len >= 2 (given)

    vector<pair<int, int>> eq; // number, index

    for (int index = 0; index < len; index++)
    {
        if (a[index] == b[index])
        {
            if (a[index] == '0')
            {
                eq.push_back(pair(0, index));
            }
            else
            {
                eq.push_back(pair(1, index));
            }
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

    return EXIT_SUCCESS;
}