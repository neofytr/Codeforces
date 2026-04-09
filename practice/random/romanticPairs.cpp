#include <bits/stdc++.h>
using namespace std;

#define int long long

struct FastHash {
    static uint64_t splitmix64(uint64_t x) {
        // https://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> peven(n + 1, 0), podd(n + 1, 0);
    for (int r = 1; r <= n; r++)
        peven[r] += peven[r - 1] + ((r & 1) ? 0 : arr[r]), podd[r] += podd[r - 1] + ((r & 1) ? arr[r] : 0);

    // there is some 1 <= l <= r <= n such that sum of even in [l, r] = sum of odd in [l, r]
    // iff peven[r] - peven[l - 1] == podd[r] - podd[l - 1]
    // iff peven[r] - podd[r] = peven[l-1] - podd[l-1]

    // for each 1 <= r <= n, there is an 1 <= l <= r <= n such that even sum == odd sum iff
    // there is some k in the set {c[1], c[2], ..., c[r - 1]} such that k = c[r]

    vector<int> c(n + 1, 0);
    for (int r = 1; r <= n; r++)
        c[r] = peven[r] - podd[r];

    unordered_map<int, int, FastHash> mp;
    mp[c[0]]++; // for the initial invariant

    for (int r = 1; r <= n; r++) {
        int target = c[r];
        if (mp[target]) {
            cout << "YES\n";
            return;
        }
        mp[target]++;
    }
    cout << "NO\n";
    return;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}