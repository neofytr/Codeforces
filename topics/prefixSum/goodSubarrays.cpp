#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    vector<long long> prefix(n + 1);
    for (int index = 1; index <= n; index++)
    {
        prefix[index] = prefix[index - 1] + arr[index - 1];
    }
}

int main()
{
    int t;
    while (t--)
    {
        solve();
    }
}