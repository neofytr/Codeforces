#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: badUgly
// URL: https://codeforces.com/problemset/problem/1326/A
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1)
            cout << -1 << endl;
        else {
            cout << 2;
            for (int r = 1; r <= n - 1; r++)
                cout << 3;
            cout << endl;
        }
    }

    return 0;
}