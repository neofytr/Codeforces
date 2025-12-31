#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define MOD (998244353)

int fact[MAX + 1];

void solve() {
    string str;
    cin >> str;

    int n = (int)str.length();
    vector<int> s(n + 1);
    for (int r = 1; r <= n; r++)
        s[r] = str[r - 1] - '0';

    int l = 1, r = 1;
    int ops = 0, cnt = 1;
    int f = 0;
    while (l <= n) {
        r = l;
        while (r <= n && s[r] == s[l])
            r++;

        int len = r - l;
        ops += len - 1;
        cnt = (cnt * len) % MOD, f += (len - 1);
        l = r;
    }

    cout << ops << " " << (cnt * fact[f]) % MOD << endl;
}

int32_t main() {
    int t;
    cin >> t;

    fact[0] = 1;
    for (int r = 1; r <= MAX; r++)
        fact[r] = r * fact[r - 1] % MOD;

    while (t--) {
        solve();
    }
    return 0;
}