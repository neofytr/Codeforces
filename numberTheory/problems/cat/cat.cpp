#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cat
// URL: https://codeforces.com/problemset/problem/1487/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        if (!(n & 1))
            cout << (k - 1) % n + 1 << endl;
        else {
            const int r = (n - 1) / 2;
            const int s = (k - 1) / r;
            cout << (k - 1 + s) % n + 1 << endl;
        }
    }

    return 0;
}