// https://www.codechef.com/BYTR20B/problems/AGCY

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> prefixOne(n + 1, 0);
    vector<int> prefixTwo(n + 1, 0);

    int l, r;
    while (q--)
    {
        cin >> l >> r;
        l--, r--; // convert to zero-based indexing

        // update l to r
        prefixOne[l] += 1;
        prefixOne[r + 1] -= 1;
        prefixTwo[r + 1] -= (r - l + 1);
    }

    // propagate
    for (int index = 0; index <= n; index++)
    {
        if (index > 0)
        {
            prefixOne[index] += prefixOne[index - 1];
        }
        prefixTwo[index] += prefixOne[index];
        if (index > 0)
        {
            prefixTwo[index] += prefixTwo[index - 1];
        }
    }

    for (int index = 0; index < n; index++)
    {
        cout << prefixTwo[index] << " ";
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

    return EXIT_SUCCESS;
}