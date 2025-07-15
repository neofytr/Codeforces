#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<long long> prefix(n + 1, 0);   // One-based indexing
    vector<long long> sequence(n + 1, 0); // One-based indexing

    for (int index = n - k + 1; index <= n; index++)
    {
        cin >> prefix[index];
    }

    if (k == 1)
    {
        cout << "yes\n";
        return;
    }

    for (int index = n - k + 2; index <= n; index++)
    {
        sequence[index] = prefix[index] - prefix[index - 1];
    }

    for (int index = n - k + 3; index <= n; index++)
    {
        if (sequence[index] < sequence[index - 1])
        {
            cout << "no\n";
            return;
        }
    }

    if (prefix[n - k + 1] <= sequence[n - k + 2] * (n - k + 1))
    {
        cout << "yes\n";
    }
    else
    {
        cout << "no\n";
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
    return 0;
}
