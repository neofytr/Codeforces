#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: powerProducts
// URL: https://codeforces.com/contest/1225/problem/D
// Difficulty: hard
// Tags: 
// Strategy: 

#define MAX (100000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // smallest prime factor sieve
    vector<int> spf(MAX + 1, -1);
    for (int i = 2; i <= MAX; i++) {
        if (spf[i] == -1) {
            for (int j = i; j <= MAX; j += i) {
                if (spf[j] == -1) spf[j] = i;
            }
        }
    }

    vector<int> arr(n);
    for (int &val : arr) cin >> val;

    map<vector<pair<int, int>>, int> freq;
    long long res = 0;

    for (int val : arr) {
        map<int, int> mp;
        int x = val;
        while (x != 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                cnt++;
                x /= p;
            }
            mp[p] = cnt % k;
        }

        vector<pair<int, int>> sig;
        for (auto &s : mp) {
            if (s.second) sig.push_back(s);
        }

        vector<pair<int, int>> req;
        for (auto &s : sig) {
            int p = s.first;
            int r = (k - s.second) % k;
            if (r) req.push_back({p, r});
        }

        if (freq.count(req)) res += freq[req];
        freq[sig]++;
    }

    cout << res << "\n";
    return 0;
}