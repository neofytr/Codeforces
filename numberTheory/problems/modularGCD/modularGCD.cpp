#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: modularGCD
// URL: https://www.codechef.com/problems/GCDMOD
// Difficulty: hard
// Tags:
// Strategy:

#define MOD (1000000000 + 7)

int pw(int base, int power, const int mod) {
    int res = 1;
    while (power) {
        if (power & 1)
            res = ((res % mod) * (base % mod)) % mod;
        base = ((base % mod) * (base % mod)) % mod;
        power >>= 1;
    }
    return res;
}

int gcd(const int a, const int b, const int n) {
    const int r = a - b;
    if (!r)
        return (pw(a, n, MOD) + pw(b, n, MOD)) % MOD;

    int g = 1;
    for (int i = 1; i * i <= r; i++)
        if (!(r % i)) {
            int rem = (pw(a, n, i) + pw(b, n, i)) % i;
            if (!rem)
                g = max(g, i);
            rem = (pw(a, n, r / i) + pw(b, n, r / i)) % (r / i);
            if (!rem)
                g = max(g, r / i);
        }
    return g % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, n, t;
    cin >> t;
    while (t--) {
        cin >> a >> b >> n;
        cout << gcd(a, b, n) << endl;
    }
    return 0;
}