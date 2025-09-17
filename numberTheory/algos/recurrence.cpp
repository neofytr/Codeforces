#include <bits/stdc++.h>
using namespace std;

#define int long long
#define Mat vector<vector<int>>
#define MOD (1000000000 + 7)

// We want to calculate the nth element of a recurrence relation % MOD in log(n)
// Let the recurrence relation be
// f(n) = 2f(n - 1) + 3f(n - 2) for n >= 3
// f(1) = 0 and f(2) = 1

// So,
// f(n + 2) = 2f(n + 1) + 3f(n) for n >= 1
// f(1) = 0 and f(2) = 1

// T = 0 3
//     1 2

// { f(r) f(r+1) } * T = { f(r + 1) f(r + 2) }

static inline Mat mul(const Mat &m1, const Mat &m2) {
    const int sz = m1.size();
    Mat res(sz);
    for (int row = 0; row < sz; row++)
        for (int col = 0; col < sz; col++) {
            int elt = 0;
            for (int itr = 0; itr < sz; itr++)
                elt = (elt + (m1[row][itr] % MOD) * (m2[itr][col] % MOD) % MOD) % MOD;
            res[row][col] = elt;
        }
    return res;
}

Mat exp(Mat base, int pow) {
    const int sz = base.size();
    Mat res(sz, vector<int>(sz, 0));
    for (int r = 0; r < sz; r++)
        res[r][r] = 1;

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

int func(const int n) {
    // { f(1) f(2) } * T ^ (n - 1) = { f(n) f(n + 1) }
    const Mat r1 = {{0, 1}};
    Mat T = {{0, 3}, {1, 2}};

    const Mat res = exp(move(T), n - 1);
    const Mat r2 = mul(r1, res);
    return r2[0][0];
}

int32_t main() {
    int n;
    cin >> n;
    cout << func(n) << endl;
    return 0;
}
