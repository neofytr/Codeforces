#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve() {
    int c;
    cin >> c;

    int msb = 63 - __builtin_clzll(c);
    int x = (1LL << msb);

    int a = x;
    for (int bit = 0; bit <= msb; bit++)
        if (!(c & (1ll << bit)))
            a |= (1ll << bit);
    cout << a * (x - 1) << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}