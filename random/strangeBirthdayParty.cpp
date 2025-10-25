#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> price(m + 1);
    for (int r = 1; r <= m; r++)
        cin >> price[r];

    int cost = 0;
    int lastFree = 1;
    sort(arr.begin() + 1, arr.end(), greater<int>());
    for (int r = 1; r <= n; r++) {
        if (lastFree <= arr[r])
            cost += price[lastFree++];
        else
            cost += price[arr[r]];
    }
    cout << cost << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}