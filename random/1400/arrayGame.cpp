#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int ans = a[0];

    if (k >= 3) {
        cout << 0 << '\n';
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = llabs(a[i] - a[j]);
            ans = min(ans, d);
        }
    }

    if (k == 1) {
        cout << ans << '\n';
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = llabs(a[i] - a[j]);

            auto it = lower_bound(a.begin(), a.end(), d);
            if (it != a.end())
                ans = min(ans, llabs(*it - d));
            if (it != a.begin()) {
                --it;
                ans = min(ans, llabs(*it - d));
            }
        }
    }

    cout << ans << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
