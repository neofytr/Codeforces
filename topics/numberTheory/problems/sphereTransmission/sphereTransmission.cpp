#include <bits/stdc++.h>
using namespace std;

#define int long long

int phi(int n) {
    int res = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            res -= res / p;
        }
    }
    if (n > 1)
        res -= res / n;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, int> mp;
    for (int g = 1; g * g <= n; g++) {
        if (n % g == 0) {
            int d1 = n / g;
            int s1 = d1 + g * d1 * (d1 - 1) / 2;
            mp[s1] += phi(d1);

            if (g != d1) {
                int d2 = g;
                int s2 = d2 + (n / d2) * d2 * (d2 - 1) / 2;
                mp[s2] += phi(d2);
            }
        }
    }

    mp[1]++; // for k = n

    for (auto &[s, cnt] : mp)
        cout << s << " ";
    cout << "\n";

    return 0;
}
