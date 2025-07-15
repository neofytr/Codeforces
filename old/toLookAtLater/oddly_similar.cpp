// https://atcoder.jp/contests/abc348/editorial/9776

#include<bits/stdc++.h>
using namespace std;

static constexpr size_t maxN = 2000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<bitset<maxN> > bt(n);
    vector<bitset<maxN> > bs(1000);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            bs[a[j][i]].set(j);
        }
        for (int j = 0; j < n; ++j) {
            bt[j] ^= bs[a[j][i]];
        }
        for (int j = 0; j < n; ++j) {
            bs[a[j][i]].reset(j);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)ans += bt[i].count();
    if (m & 1)ans -= n;
    cout << ans / 2 << endl;
}
