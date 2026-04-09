#include <bits/stdc++.h>
using namespace std;

#define int uint64_t

int prefix(const int v, const int k) {
    if (v <= 0)
        return 0;
    if (v <= k) {
        return v * (v + 1) / 2;
    }
    if (v >= 2 * k) {
        return k * k;
    }

    int t = v - k;
    int part1 = k * (k + 1) / 2;
    int part2 = t * k - t * (t + 1) / 2;
    return (part1 + part2);
}

void solve() {
    int k, x;
    cin >> k >> x;

    // f(y) = f(y) >= x
    int left = 0;      // f(left) = false
    int right = 2 * k; // f(right) = true
    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (prefix(mid, k) >= x)
            right = mid;
        else
            left = mid;
    }

    if (right == 2 * k)
        cout << 2 * k - 1 << endl;
    else
        cout << right << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}