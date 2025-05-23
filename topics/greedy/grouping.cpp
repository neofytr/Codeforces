// https://codeforces.com/problemset/problem/1919/C
#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    long long penalty = 0;
    int x = INT_MAX, y = INT_MAX; // x >= y (alway)

    int temp;
    while (n--)
    {
        cin >> temp;

        if (temp <= x)
        {
            x = temp;
        }
        else if (temp > y)
        {
            x = temp;
            swap(x, y);
            penalty++;
        }
        else
        {
            // x < temp <= y
            y = temp;
        }
    }

    cout << penalty << endl;
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