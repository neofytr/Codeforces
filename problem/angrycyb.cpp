// https://www.codechef.com/BYTR20B/problems/AGCY?tab=statement

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<long long> pref_one(n, 0); // init to zero
    vector<long long> pref_two(n, 0); // init to zero

    int l, r;
    while (q--)
    {
        cin >> l >> r;

        // change to zero based indexing
        l--, r--;

        pref_one[l] += 1;
        if (r + 1 < n)
        {
            pref_one[r + 1] += -1;
            pref_two[r + 1] -= (r - l + 1);
        }
    }

    // propogate pref_one
    for (int index = 1; index < n; index++)
    {
        pref_one[index] += pref_one[index - 1];
    }

    // copy into pref_two
    for (int index = 0; index < n; index++)
    {
        pref_two[index] += pref_one[index];
    }

    // propagate pref_two
    for (int index = 1; index < n; index++)
    {
        pref_two[index] += pref_two[index - 1];
    }

    for (int val : pref_two)
    {
        cout << val << " ";
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