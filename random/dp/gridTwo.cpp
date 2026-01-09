#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NMAX (int)(3 * 1e3)
#define FMAX (int)(2 * 1e5)
#define MOD (int)(1e9 + 7)

int fact[FMAX + 1];
int invFact[FMAX + 1];
int dp[NMAX + 1];

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

int32_t main() {
    fact[0] = 1;
    for (int r = 1; r <= FMAX; r++)
        fact[r] = (r * fact[r - 1]) % MOD;

    invFact[FMAX] = pw(fact[FMAX], MOD - 2);
    for (int r = FMAX - 1; r >= 0; r--)
        invFact[r] = ((r + 1) * invFact[r + 1]) % MOD;

    int h, w, n;
    cin >> h >> w >> n;
}