#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    vector<int> sa = a;
    vector<int> sb = b;

    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    vector<pair<int, int>> original, target;

    for (int i = 0; i < n; i++) {
        original.push_back({a[i], b[i]});
        target.push_back({sa[i], sb[i]});
    }

    sort(original.begin(), original.end());
    sort(target.begin(), target.end());

    if (original != target) {
        cout << -1 << '\n';
        return;
    }

    vector<pair<int, int>> moves;

    for (int i = 0; i < n; i++) {
        int pos = i;

        while (pos < n &&
               !(a[pos] == sa[i] && b[pos] == sb[i])) {
            pos++;
        }

        while (pos > i) {
            swap(a[pos], a[pos - 1]);
            swap(b[pos], b[pos - 1]);

            moves.push_back({pos + 1, pos});

            pos--;
        }
    }

    cout << moves.size() << '\n';

    for (auto [x, y] : moves) {
        cout << x << ' ' << y << '\n';
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
