#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    vector<pair<int,int>> f(2 * n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[a[i]] = {0, i};
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        f[b[i]] = {1, i};
    }

    vector<pair<int,int>> ops;
    int alast = n, blast = n;

    for (int val = 2 * n; val >= 1; val--) {
        auto [arr, idx] = f[val];

        if (arr == 0) {
            if (idx > alast) continue;   

            for (int j = idx; j < alast; j++) {
                ops.push_back({1, j});
                swap(a[j], a[j + 1]);
                f[a[j]] = {0, j};
                f[a[j + 1]] = {0, j + 1};
            }

            if (alast == blast && a[alast] > b[alast]) {
                ops.push_back({3, alast});
                swap(a[alast], b[alast]);
                f[a[alast]] = {0, alast};
                f[b[blast]] = {1, blast};
                blast--;
                alast++;
            }
            alast--;
        }
        else {
            if (idx > blast) continue;   

            for (int j = idx; j < blast; j++) {
                ops.push_back({2, j});
                swap(b[j], b[j + 1]);
                f[b[j]] = {1, j};
                f[b[j + 1]] = {1, j + 1};
            }
            blast--;
        }
    }

   	cout << ops.size() << endl;
   	for (auto [i, j] : ops)
   		cout << i << " " << j << endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
