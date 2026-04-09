#include <bits/stdc++.h>
#include <cstdlib>
#include <ostream>
#include <vector>
using namespace std;

// Problem: mocha
// URL: https://codeforces.com/problemset/problem/1559/C
// Difficulty: easy
// Tags:
// Strategy:

/*

We want to insert n+1 somewhere in the path 1 → 2 → 3 → ... → n such that all edges (including those involving n+1) are valid.

There are 3 valid cases:

If a[0] == 1: There’s a road from n+1 to 1. So, we can start from n+1, then go to 1 → 2 → ... → n.

If a[n-1] == 0: There’s a road from n to n+1. So, we can go 1 → 2 → ... → n → n+1.

If a[i] == 0 and a[i+1] == 1 for some i: There's a road from i+1 to n+1, and from n+1 to i+2, so we can insert n+1 between them.

*/

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    if (a[0] == 1) {
        cout << n + 1 << " ";
        for (int i = 1; i <= n; ++i)
            cout << i << " ";
        cout << "\n";
        return;
    }

    if (a[n - 1] == 0) {
        for (int i = 1; i <= n; ++i)
            cout << i << " ";
        cout << n + 1 << "\n";
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        if (a[i] == 0 && a[i + 1] == 1) {
            for (int j = 1; j <= i + 1; ++j)
                cout << j << " ";
            cout << n + 1 << " ";
            for (int j = i + 2; j <= n; ++j)
                cout << j << " ";
            cout << "\n";
            return;
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
