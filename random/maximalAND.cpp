#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> sset(31, 0);
    for (int r = 1; r <= n; r++) {
        for (int bit = 0; bit <= 30; bit++)
            if (arr[r] & (1LL << bit))
                sset[bit]++;
    }

    // for (int bit = 0; bit <= 30; bit++)
    //    cout << sset[bit] << " ";
    // cout << endl;

    int res = 0, x = k;
    for (int bit = 30; bit >= 0; bit--) {
        int todo = n - sset[bit];
        if (!todo)
            res |= (1LL << bit);
        else if (x - todo >= 0)
            x -= todo, res |= (1LL << bit);
    }
    cout << res << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}