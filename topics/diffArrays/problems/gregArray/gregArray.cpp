#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<pair<pair<int, int>, int>> queries(m);
    for (auto &[p, x] : queries) {
        cin >> p.first >> p.second >> x;
        p.first--, p.second--; // convert to 0-based
    }

    // count how many times each operation is applied
    vector<int> ops(m + 1, 0);
    while (k--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        ops[l] += 1;
        ops[r + 1] -= 1;
    }

    for (int i = 1; i < m; i++) // prefix sum on ops (size m)
        ops[i] += ops[i - 1];
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < m; i++) {
        auto [p, x] = queries[i];
        int l = p.first, r = p.second;
        prefix[l] += ops[i] * x;
        prefix[r + 1] -= ops[i] * x;
    }
    for (int i = 1; i < n; i++)
        prefix[i] += prefix[i - 1];
    for (int i = 0; i < n; i++)
        arr[i] += prefix[i];
    for (int val : arr)
        cout << val << " ";
    cout << "\n";
    return 0;
}
