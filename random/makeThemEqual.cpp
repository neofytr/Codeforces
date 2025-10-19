#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    char c;
    cin >> n >> c;

    string str;
    cin >> str;

    // can this be done in 0 steps?
    bool zero = true;
    for (const char ch : str)
        if (ch != c)
            zero = false;
    if (zero) {
        cout << 0 << endl;
        return;
    }

    // can this be done in one step?
    // this is psbl iff there is 1 <= x <= n such that str[r - 1] == c for all
    // multiples r of x

    for (int x = 1; x <= n; x++) {
        bool allC = true;
        for (int r = x; r <= n; r += x)
            if (str[r - 1] != c) {
                allC = false;
                break;
            }
        if (allC) {
            cout << 1 << endl;
            cout << x << endl;
            return;
        }
    }

    // its always possible in two step otherwise
    // choose the first integer as n and the other n - 1
    cout << 2 << endl;
    cout << n << " " << n - 1 << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}