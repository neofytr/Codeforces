#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: children
// URL: https://codeforces.com/problemset/problem/1850/F
// Difficulty: medium
// Tags:
// Strategy:

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int val;
        unordered_map<int, int, custom_hash> mp;
        for (int r = 1; r <= n; r++)
            cin >> val, mp[val]++;

        int maxi = -1;
        for (int r = 1; r <= n; r++) {
            int cnt = 0;
            for (int d = 1; d * d <= r; d++)
                if (!(r % d)) {
                    cnt += mp[d];
                    if (d != r / d)
                        cnt += mp[r / d];
                }
            maxi = max(maxi, cnt);
        }
        cout << maxi << endl;
    }
    return 0;
}