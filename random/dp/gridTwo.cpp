#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MAX (int)(1e3)
#define NMAX (int)(1e5)
#define MOD (int)(1e9 + 7)

#define invFact(x) (pw((x), MOD - 2))
#define fact(x) (f[(x)])
#define C(n, r) (fact((n)) * invFact((r)) % MOD * invFact((n) - (r)) % MOD)

int dp[MAX + 2];
int f[NMAX + 1];

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

int cnt(const pair<int, int> &start, const pair<int, int> &end) {
    const int r1 = start.first, c1 = start.second;
    const int r2 = end.first, c2 = end.second;

    if (r1 < r2 || c1 < c2)
        return 0;

    return C(r2 - r1 + c2 - c1, r2 - r1);
}

int32_t main() {
    f[0] = 1;
    for (int r = 1; r <= NMAX; r++)
        f[r] = (r * f[r - 1]) % MOD;

    int h, w, n;
    cin >> h >> w >> n;

    vector<pair<int, int>> vec(n + 2);
    for (int r = 1; r <= n; r++)
        cin >> vec[r].first >> vec[r].second;
    vec[n].first = h, vec[n].second = w;

    auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
        // return true if a comes before b in the ordering (i.e, if a < b)
        // return false if a doesn't come before b in the ordering (i.e, if a >= b)

        if (a.first < b.first)
            return true;
        if (a.first == b.first && a.second < b.second)
            return true;
        return false;
    };

    sort(vec.begin() + 1, vec.end(), cmp);

    // dp[r] is the number of valid paths from (1, 1) to point vec[r] so that the paths do not pass
    // through any points [1, r - 1] for r >= 2
    // dp[1] is the number of paths from (1, 1) to vec[1]
    dp[1] = cnt({1, 1}, vec[1]);
    for (int r = 2; r <= n + 1; r++) {
        dp[r] = cnt({1, 1}, vec[r]); // total paths from (1, 1) to vec[r]
        for (int k = 1; k < r; k++)
    }
    return 0;
}