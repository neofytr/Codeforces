#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: simple
// URL: https://codeforces.com/problemset/problem/2093/C
// Difficulty: easy
// Tags:
// Strategy:

bool is_prime(const int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int x, k;
        cin >> x >> k;
        if (k > 1 && x > 1) {
            cout << "NO";
        } else if (k == 1) {
            cout << (is_prime(x) ? "YES" : "NO");
        } else {
            cout << ((k == 2) ? "YES" : "NO");
        }
    }
    return 0;
}
