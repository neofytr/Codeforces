#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// Problem: permutationRounds
// URL: https://cses.fi/problemset/task/3398
// Difficulty: hard
// Tags: 
// Strategy: factorize cycle lengths and take LCM via prime powers

// Modular exponentiation
int pw(int base, int exp) {
    base = base % MOD;
    int res = 1;
    while(exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<int> arr(n+1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<bool> vis(n+1, false);

    unordered_map<int,int> mp;

    for (int r = 1; r <= n; r++) {
        if (vis[r]) continue; 

        int cnt = 0;
        int i = r;
        do {
            vis[i] = true;
            i = arr[i];
            cnt++;
        } while (i != r);

        int x = cnt;
        for (int p = 2; p*p <= x; p++) {
            int power = 0;
            while (!(x % p)) {
                x /= p;
                power++;
            }
            mp[p] = max(mp[p], power);
        }
        if (x > 1) mp[x] = max(mp[x], 1LL); // remaining prime
    }

    int res = 1;
    for (auto &[p, power] : mp)
        res = res * pw(p, power) % MOD;
    
    cout << res << "\n";
    return 0;
}
