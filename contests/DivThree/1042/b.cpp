#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n % 2 != 0) {
        for (int i = 0; i < n; ++i) {
            cout << (i % 2 == 0 ? -1 : 3) << " ";
        }
        cout << endl;
    } else {
        for (int i = 0; i < n - 2; ++i) {
            cout << (i % 2 == 0 ? -1 : 3) << " ";
        }
        cout << -1 << " " << 2 << endl;
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}