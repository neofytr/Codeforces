#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x;
    cin >> x;

    int dig;
    int sm = 10;
    while (x > 0) {
        dig = x % 10;
        sm = min(sm, dig);
        x /= 10;
    }

    cout << sm << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}