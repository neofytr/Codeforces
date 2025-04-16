// https://www.codechef.com/BYTR20B/problems/AGCY

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, q;
    cin >> n >> q;

    // prefixOne is used to apply a linear difference array update
    vector<int> prefixOne(n + 1, 0);

    // prefixTwo stores the actual values after applying range updates as a progressive sum
    vector<int> prefixTwo(n + 1, 0);

    int l, r;
    while (q--)
    {
        cin >> l >> r;
        l--, r--; // convert to zero-based indexing

        // apply difference array update:
        // mark start of addition at index l
        prefixOne[l] += 1;

        // mark end of addition at index r+1 to cancel the effect after r
        prefixOne[r + 1] -= 1;

        // subtract total added values beyond r to cancel accumulated values in prefixTwo
        prefixTwo[r + 1] -= (r - l + 1);
    }

    // propagate the updates to compute final values
    for (int index = 0; index <= n; index++)
    {
        if (index > 0)
        {
            // accumulate prefixOne so that each index has the number of additions applied
            prefixOne[index] += prefixOne[index - 1];
        }

        // add the current prefixOne value to prefixTwo (since each index is incremented that many times)
        prefixTwo[index] += prefixOne[index];

        if (index > 0)
        {
            // accumulate prefixTwo to get the final values at each position
            prefixTwo[index] += prefixTwo[index - 1];
        }
    }

    // print the final result for each of the first n positions
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
