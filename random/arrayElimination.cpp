#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    vector<int> bit(31, 0);
    for (int r = 1; r <= n; r++) {
        cin >> arr[r];
        for (int b = 0; b <= 30; b++)
            if (arr[r] & (1LL << b))
                bit[b]++;
    }

    int g = 0;
    for (int b = 0; b <= 30; b++)
        g = gcd(g, bit[b]);

    for (int k = 1; k <= n; k++)
        if (!(g % k))
            cout << k << " ";

    cout << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}