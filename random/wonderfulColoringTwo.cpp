#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];

    unordered_map<int, vector<int>> pos;
    for (int i = 1; i <= n; i++)
        pos[arr[i]].push_back(i);

    vector<int> freq;
    for (auto &p : pos)
        freq.push_back(p.second.size());

    sort(freq.rbegin(), freq.rend());

    auto can = [&](int x) {
        if (x == 0) return true;
        if (k * x > n) return false;

        int total = 0;
        for (int f : freq)
            total += min((int)k, f);
        return total >= k * x;
    };

    int left = 0, right = n/k + 1;
    while (right != left + 1) {
        int mid = (left + right) / 2;
        if (can(mid)) left = mid;
        else right = mid;
    }

    int x = left;

    vector<int> ans(n + 1, 0);

    vector<int> collected;
    for (auto &p : pos) {
        auto &vec = p.second;
        for (int i = 0; i < min((int)vec.size(), k); i++)
            collected.push_back(vec[i]);
    }

    collected.resize(k * x);

    int color = 1;
    for (int idx : collected) {
        ans[idx] = color;
        color++;
        if (color > k) color = 1;
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
