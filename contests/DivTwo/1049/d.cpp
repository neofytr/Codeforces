#include <bits/stdc++.h>
using namespace std;

void solve() {
    int q;
    cin >> q;
    vector<long long> a(q), b(q);
    long long base = 0;
    for (int i = 0; i < q; ++i) {
        cin >> a[i] >> b[i];
        base += b[i] - a[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long extra = 0;
    for (int i = 0; i < q / 2; ++i) {
        long long len = b[q - 1 - i] - a[i];
        if (len > 0) {
            extra += len;
        }
    }

    cout << base + extra << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int cases;
    cin >> cases;
    while (cases--) {
        solve();
    }
    return 0;
}
