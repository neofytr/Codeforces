#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long k, x, a;
        cin >> k >> x >> a;

        if (k == 1) {
            cout << "NO\n";
            continue;
        }

        long long lost = 0;   // total loss so far
        long long bet = 1;    // current bet
        bool ok = true;

        for (int i = 0; i < x; i++) {
            if (bet > a - lost) {
                ok = false;
                break;
            }

            lost += bet;

            bet = lost / (k - 1) + 1;
        }

        if (ok && bet <= a - lost) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}