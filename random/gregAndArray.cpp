#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    vector<tuple<int, int, int>> operations(m + 1);
    for (int i = 1; i <= m; i++) {
        int l, r, d;
        cin >> l >> r >> d;
        operations[i] = {l, r, d};
    }

    vector<int> op_count(m + 2, 0);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        op_count[x]++;
        op_count[y + 1]--;
    }

    for (int i = 1; i <= m; i++)
        op_count[i] += op_count[i - 1];

    vector<int> diff(n + 2, 0);
    for (int i = 1; i <= m; i++) {
        auto [l, r, d] = operations[i];
        int cnt = op_count[i];
        diff[l] += cnt * d;
        diff[r + 1] -= cnt * d;
    }

    for (int i = 1; i <= n; i++) {
        diff[i] += diff[i - 1];
        cout << arr[i] + diff[i] << " ";
    }
    cout << endl;
}
