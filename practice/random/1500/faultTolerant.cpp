#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n; 
    cin >> n;
    vector<int> a(n), b(n);
    
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    auto get_best = [&](int val, const vector<int>& arr) {
        int best = 2e9; 
        for (int x : arr) {
            best = min(best, llabs(val - x));
        }
        return best;
    };

    int best_a1 = get_best(a[0], b);
    int best_an = get_best(a[n - 1], b);
    int best_b1 = get_best(b[0], a);
    int best_bn = get_best(b[n - 1], a);

    int ans = best_a1 + best_an + best_b1 + best_bn;

    ans = min(ans, llabs(a[0] - b[0]) + llabs(a[n - 1] - b[n - 1])); 
    ans = min(ans, llabs(a[0] - b[n - 1]) + llabs(a[n - 1] - b[0]));

    ans = min(ans, llabs(a[0] - b[0]) + best_an + best_bn);
    ans = min(ans, llabs(a[n - 1] - b[n - 1]) + best_a1 + best_b1);
    ans = min(ans, llabs(a[0] - b[n - 1]) + best_an + best_b1);
    ans = min(ans, llabs(a[n - 1] - b[0]) + best_a1 + best_bn);

    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; 
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}