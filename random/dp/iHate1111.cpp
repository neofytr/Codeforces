#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int x;
    cin >> x;

    // Any combination of 11, 111, ... can be expressed as 11 * a + 111 * b for some non-negative integers a, b
    // Also, since gcd(111, 11) = 1, any number > 111 * 11 - 111 - 11 can be expressed as 11 * a + 111 * b for some non-negative integers a, b

    // Thus, any number > 1099 can be expressed as a combination of 11, 111,
    if (x > 1099) {
        cout << "YES\n";
        return;
    }

    for (int a = 0; a <= 100; a++) {
        if (x - 11 * a >= 0) {
            int t = x - 11 * a;
            if (!(t % 111)) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}