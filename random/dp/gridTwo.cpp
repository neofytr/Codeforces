#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N_MAX (int)(3 * 1e3)
#define FMAX (int)(2 * 1e5)
#define MOD (int)(1e9 + 7)
#define C(n, r) ((r < 0 || r > n) ? 0 : (fact[(n)] * invFact[(r)] % MOD * invFact[(n) - (r)] % MOD))

int fact[FMAX + 1];
int invFact[FMAX + 1];
int dp[N_MAX + 1];
pair<int, int> vec[N_MAX + 2];

int pw(int base, int exp) {
    int res = 1;
    base = base % MOD;

    while (exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int cnt(pair<int, int> start, pair<int, int> end) {
    int r1 = start.first, c1 = start.second;
    int r2 = end.first, c2 = end.second;

    if (r1 > r2 || c1 > c2)
        return 0;
    return C(r2 - r1 + c2 - c1, r2 - r1);
}

int32_t main() {
    fact[0] = 1;
    for (int r = 1; r <= FMAX; r++)
        fact[r] = (r * fact[r - 1]) % MOD;

    invFact[FMAX] = pw(fact[FMAX], MOD - 2);
    for (int r = FMAX - 1; r >= 0; r--)
        invFact[r] = ((r + 1) * invFact[r + 1]) % MOD;

    int h, w, n;
    cin >> h >> w >> n;

    int row, col;
    for (int r = 1; r <= n; r++)
        cin >> row >> col, vec[r] = {row, col};
    vec[n + 1] = {h, w};

    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
        // return true if a < b, false otherwise (to sort in increasing order)
        if (a.first < b.first)
            return true;
        if (a.first == b.first && a.second < b.second)
            return true;
        return false;
    };

    sort(vec + 1, vec + n + 2, cmp);

    // dp[1] = cnt({1, 1}, vec[1])
    // dp[r] = number of paths from {1, 1} to point r such that the path does not pass through any
    // of the points k < r
    for (int r = 1; r <= n + 1; r++) {
        dp[r] = cnt({1, 1}, vec[r]);
        for (int k = 1; k < r; k++) {
            dp[r] = (dp[r] - dp[k] * cnt(vec[k], vec[r]) + MOD) % MOD;
        }
    }

    cout << (dp[n + 1] + MOD) % MOD << endl;
    return 0;
}