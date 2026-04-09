#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (998244353)
#define MAX (2 * 100000 + 1)

int fact[MAX + 1];

void solve() {
    string str;
    cin >> str;

    int n = (int)str.length();
    vector<int> idx;
    int i = 0, j = 0;
    while (i < n) {
        j = i;
        while (j < n - 1 && str[j] == str[j + 1])
            j++;

        if (j == i) {
            i = j + 1;
            continue;
        }
        idx.push_back(j - i);
        i = j + 1;
    }

    int res = 1;
    int s = 0;
    for (const int id : idx)
        res = res * (id + 1) % MOD, s += id;

    res = res * fact[s] % MOD;
    cout << s << " " << res << endl;
}

int32_t main() {
    int t;
    cin >> t;

    fact[0] = 1;
    for (int r = 1; r <= MAX; r++)
        fact[r] = fact[r - 1] * r % MOD;

    while (t--) {
        solve();
    }
    return 0;
}