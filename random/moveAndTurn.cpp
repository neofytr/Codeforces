#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n % 2 == 0) {
        // n is even, n = 2k. k = n / 2.
        // The sets of reachable points overlap completely.
        // Total = (k + 1) * (k + 1)
        int k = n / 2;
        cout << (k + 1) * (k + 1) << "\n";
    } else {
        // n is odd, n = 2k + 1. k = n / 2 (integer division).
        // The sets are disjoint.
        // Total = 2 * (k + 1) * (k + 2)
        int k = n / 2;
        cout << 2 * (k + 1) * (k + 2) << "\n";
    }

    return 0;
}