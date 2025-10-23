#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> arr(n + 1);
    unordered_map<int, int> pcnt;
    int k, p;
    for (int r = 1; r <= n; r++) {
        cin >> k;
        while (k--)
            cin >> p, arr[r].push_back(p), pcnt[p]++;
    }

    bool canBeDone = false;
    for (int r = 1; r <= n; r++) {
        bool c = true;
        for (int v : arr[r])
            if (pcnt[v] <= 1) {
                c = false;
                break;
            }
        if (c) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}