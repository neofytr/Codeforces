#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)
#define MAX (1000)

void metOne() {
    int q; // 1 <= q <= 10^6
    cin >> q;

    // 0 <= n <= 1000, 0 <= k <= n
    // C[n][r] = C(n, r)
    vector C(MAX + 1, vector<int>(MAX + 1, 0));

    // O(MAX * MAX) precalculation
    // C[n][r] = C[n - 1][r] + C[n - 1][r - 1] for 1000 >= n >= 2, 1 <= r <= n
    // C[k][0] = 1 for all 1000 >= k >= 2
    // C[1][0] = 1, C[1][1] = 1
    // C[0][0] = 1
    for (int k = 0; k <= 1000; k++)
        C[k][0] = 1;
    C[1][1] = 1;
    for (int n = 2; n <= 1000; n++)
        for (int r = 1; r <= n; r++)
            C[n][r] = (C[n - 1][r] + C[n - 1][r - 1]) % MOD;

    int n, k;
    while (q--) {
        cin >> n >> k;
        cout << C[n][k] << endl;
    }
}

#define MAXIMUM (1000000)
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
void metTwo() {
    int q;
    cin >> q; // 1 <= q <= 10^6

    vector<int> fact(MAXIMUM + 1), invFact(MAXIMUM + 1);
    fact[0] = 1;
    for (int r = 1; r <= MAXIMUM; r++)
        fact[r] = r * fact[r - 1] % MOD;
    invFact[MAXIMUM] = pw(fact[MAXIMUM], MOD - 2);
    for (int r = MAXIMUM - 1; r >= 0; r--)
        invFact[r] = invFact[r + 1] * (r + 1) % MOD;

    int n, r; // 1 <= n <= 10^6, 0 <= r <= n
    while (q--) {
        cin >> n >> r;
        cout << fact[n] * invFact[n - r] % MOD * invFact[r] % MOD << endl;
    }
}