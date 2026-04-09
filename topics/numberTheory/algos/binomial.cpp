#include <bits/stdc++.h>
using namespace std;

#define int long long
#define p (1000000000 + 7)
#define MAX (1000000)

// We assume base is given % mod
// Returns (base ^ pow) % mod
int pw(int base, int pow, const int mod) {
    int res = 1;
    while (pow) {
        if (pow & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        pow >>= 1;
    }
    return res;
}

int32_t main() {
    int t;
    cin >> t;

    vector<int> h(MAX + 1);
    h[0] = 1;
    for (int r = 1; r <= MAX; r++)
        h[r] = (h[r - 1] * r) % p;

    vector<int> w(MAX + 1);
    w[MAX] = pw(MAX % p, p - 2, p);
    for (int r = MAX - 1; r >= 0; r--)
        w[r] = ((r + 1) * w[r + 1]) % p;

    while (t--) {
        int n, r;
        cin >> n >> r;
        if (r > n) {
            cout << 0 << endl;
            continue;
        }
        cout << h[n] * w[r] % p * w[n - r] % p << endl;
    }
    return 0;
}