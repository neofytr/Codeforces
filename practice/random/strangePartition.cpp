#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, x;
    cin >> n >> x;

    vector<double> arr(n);
    for (auto &val : arr)
        cin >> val;

    int maxi = 0;
    double mini = 0;

    for (double v : arr) {
        maxi += (int)ceil(v / x);
        mini += v / x;
    }

    cout << (int)ceil(mini) << " " << maxi << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
