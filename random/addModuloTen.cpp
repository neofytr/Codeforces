#include <bits/stdc++.h>
using namespace std;

#define int long long

int normalize(int x) {
    if (x % 10 == 0) return x;
    if (x % 10 == 5) return x + 5;

    while (x % 10 != 2) x += x % 10;
    return x % 20;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    for (int &x : a)
        x = normalize(x);

    bool ok = true;
    for (int i = 1; i < n; i++)
        if (a[i] != a[0])
            ok = false;

    cout << (ok ? "YES\n" : "NO\n");
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) solve();
}
