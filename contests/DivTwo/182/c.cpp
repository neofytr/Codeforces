#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int mod = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<long long> p(n), q(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i];
    for (int i = 0; i < n; ++i)
        cin >> q[i];

    for (int i = 0; i < n; ++i)
        if (p[i] > q[i])
            swap(p[i], q[i]);

    for (int i = 0; i < n - 1; ++i)
        if (p[i] > p[i + 1] || q[i] > q[i + 1]) {
            cout << 0 << endl;
            return;
        }

    long long ans = 1, dp1 = 1, dp2 = 1;

    for (int i = 1; i < n; ++i) {
        if (p[i] > q[i - 1]) {
            ans = ans * (dp1 + dp2) % mod;
            dp1 = dp2 = 1;
        } else {
            long long prev1 = dp1;
            long long prev2 = dp2;
            dp1 = prev1;
            dp2 = prev2;
            if (p[i] >= q[i - 1]) {
                dp1 = (dp1 + prev2) % mod;
                dp2 = (dp2 + prev1) % mod;
            }
        }
    }
    ans = ans * (dp1 + dp2) % mod;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
    return 0;
}
