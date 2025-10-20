#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int pw(int base, int exp) {
    int res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    cout << pw(n, k) << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
