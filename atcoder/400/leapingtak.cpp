// https://atcoder.jp/contests/abc179/tasks/abc179_d

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> selections(n + 1, 0);

    // for computing the union
    // for each segment, we put 1 in the corresponding segment in the selection
    // to put the one, we use propagation
    // since the segments are given to be non-intersecting, the indexes in the final union will
    // all have exactly 1 as their value; in general, they are positive

    int l, r;
    for (int index = 0; index < k; index++)
    {
        cin >> l >> r;

        // convert to zero based index
        l--, r--;

        selections[l] += 1;
        selections[r + 1] -= 1;
    }

    // propagate
    for (int index = 1; index < n; index++)
    {
        selections[index] += selections[index - 1];
    }

    for (int index = 0; index < n; index++)
    {
        cout << selections[index] << " ";
    }

    cout << endl;
}

int main()
{

    solve();

    return 0;
}