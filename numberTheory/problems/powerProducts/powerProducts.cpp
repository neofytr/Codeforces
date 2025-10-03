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

    map<vector<pair<int,int>>, int> freq;
    long long ans = 0;

    for (int val : arr) {
        int x = val;
        map<int,int> exp;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            cnt %= k;
            if (cnt != 0) exp[p] += cnt;
        }

        vector<pair<int,int>> sig;
        for (auto &e : exp) sig.push_back(e);

        vector<pair<int,int>> comp;
        for (auto &e : exp) {
            int p = e.first, r = e.second;
            comp.push_back({p, (k - r) % k});
        }

        if (freq.count(comp)) ans += freq[comp];

        freq[sig]++;
    }

    cout << ans << "\n";
    return 0;
}