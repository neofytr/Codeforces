// https://atcoder.jp/contests/abc179/tasks/abc179_d

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> selections(n + 1);

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

    for (int val : selections)
    {
        cout << val << " ";
    }

    cout << endl;
}

int main()
{

    solve();

    return 0;
}