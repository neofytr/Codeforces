#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

void solve()
{
    size_t n, k;
    cin >> n >> k;

    vector<size_t> num(n);

    for (size_t &val : num)
    {
        cin >> val;
    }

    vector<size_t> rem_count(k, 0); // Stores count of each remainder mod k

    for (size_t &val : num)
    {
        size_t rem = val % k;
        rem_count[rem]++;
    }

    // If any number is already divisible by k, answer is 0
    if (rem_count[0] > 0)
    {
        cout << 0 << endl;
        return;
    }

    // Handling k = 2
    if (k == 2)
    {
        cout << 1 << endl;
        return;
    }

    // Handling k = 3
    if (k == 3)
    {
        if (rem_count[2] > 0)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl; // Only 1s exist
        }
        return;
    }

    // Handling k = 4
    if (k == 4)
    {
        if (rem_count[2] >= 2)
        {
            cout << 0 << endl;
            return;
        }
        if (rem_count[3] > 0)
        {
            cout << 1 << endl;
            return;
        }
        if (rem_count[2] == 1)
        {
            cout << 1 << endl;
            return;
        }
        cout << 3 << endl;
        return;
    }

    // Handling k = 5
    if (k == 5)
    {
        if (rem_count[4] > 0)
        {
            cout << 1 << endl;
            return;
        }
        if (rem_count[3] > 0)
        {
            cout << 2 << endl;
            return;
        }
        if (rem_count[2] > 0)
        {
            cout << 3 << endl;
            return;
        }
        cout << 4 << endl;
        return;
    }
}

int main()
{
    FAST_IO;
    size_t t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
