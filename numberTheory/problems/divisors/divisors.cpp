#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: divisors
// URL: https://open.kattis.com/problems/divisors
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 0 <= k <= n <= 431

    // pf[r] contains the prime factor map of r! for 2 <= r <= 431
    vector<unordered_map<int, int>> pf(432);
    pf[2][2] = 1;

    for (int r = 3; r <= 431; r++){ 
        int x = r;
        for (int d = 2; d * d <= x; d++)
            while(!(x % d))
                pf[r][d]++, x /= d;
        if (x > 1) pf[r][x]++;

        for (auto [p, cnt] : pf[r - 1])
            pf[r][p] += cnt;
    }
    
    int n, k;
    while(cin >> n >> k) {
        int res = 1;
        for (auto &[p, cnt] : pf[n]) {
            int left = cnt - pf[k][p] - pf[n - k][p];
            res *= (left + 1);
        }
        cout << res << endl;
    }    
    return 0;
}
