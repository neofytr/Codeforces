#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)
#define REP(var, mx) for (int var = 0; var < mx; var++)
#define MAT vector<vector<int>>

// Problem: fib
// URL: https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem
// Difficulty: medium
// Tags:
// Strategy:

MAT mul(const MAT &m1, const MAT &m2) {
    const int sz = m1.size();
    MAT res(sz, vector<int>(sz));
    REP(row, sz) REP(col, sz) {
        int elt = 0;
        REP(itr, sz) elt = (elt + ((m1[row][itr] % MOD) * (m2[itr][col] % MOD)) % MOD) % MOD;
        res[row][col] = elt;
    }
    return res;
}

MAT exp(MAT base, int pw) {
    const int sz = base.size();
    MAT res(sz, vector<int>(sz));
    REP(r, sz) res[r][r] = 1;

    while (pw) {
        if (pw & 1)
            res = mul(res, base);
        base = mul(base, base);
        pw >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int a, b, n;
        cin >> a >> b >> n;
        // f(0) = a and f(1) = b
        // f(r) = f(r - 1) + f(r - 2) for r >= 2
        // f(r + 2) = f(r + 1) + f(r) for r >= 0

        // { f(0) f(1) } * T^(n - 1) = { f(n - 1) f(n) }

        if (!n) {
            cout << a % MOD << endl;
            continue;
        }
        if (n == 1) {
            cout << b % MOD << endl;
            continue;
        }

        const MAT T = {{0, 1}, {1, 1}};
        const MAT res = exp(T, n - 1);
        cout << (((a % MOD) * res[1][0]) % MOD + ((b % MOD) * res[1][1]) % MOD) % MOD << endl;
    }

    return 0;
}