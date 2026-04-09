#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mpow
// URL: https://www.spoj.com/problems/MPOW/
// Difficulty: medium
// Tags:
// Strategy:

#define Mat vector<vector<int>>
#define MOD (1000000000 + 7)
#define REP(var, mx) for (int var = 0; var < mx; var++)

Mat mul(const Mat &m1, const Mat &m2) {
    const int sz = m1.size();
    Mat res(sz, vector<int>(sz));

    REP(row, m)
    REP(col, m) {
        int elt = 0;
        for (int itr = 0; itr < sz; itr++)
            elt = (elt + ((m1[row][itr] % MOD) * (m2[itr][col] % MOD)) % MOD) % MOD;
        res[row][col] = elt;
    }
    return res;
}

Mat exp(Mat base, int pow) {
    const int sz = base.size();
    Mat res(sz, vector<int>(sz, 0));
    for (int r = 0; r < sz; r++)
        res[r][r] = 1; // identity matrix

    if (pow < 0)
        return Mat{};
    if (!pow)
        return res;
    while (pow) {
        if (pow & 1)
            res = mul(res, base);
        base = mul(base, base);
        pow >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> m >> n;

        Mat mat(m, vector<int>(m));
        REP(row, m) REP(col, m) cin >> mat[row][col];

        // this exponentiation is done in O(m^3 * log(n)) time
        const Mat res = exp(move(mat), n);
        REP(row, m) {
            REP(col, m) cout << res[row][col] << " ";
            cout << endl;
        }
    }

    return 0;
}