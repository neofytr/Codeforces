#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++) cin >> arr[r];

    // ai < aj < ak
    // ai + aj + ak > an <-> ai > an - aj - ak
    // ak < ai + aj <-> ai > ak - aj

    int cnt = 0;
    for (int k = 1; k <= n; k++)
        for (int j = 1; j < k; j++) {
            const auto itr = upper_bound(arr.begin() + 1, arr.end(), max(arr[n] - arr[j] - arr[k], arr[k] - arr[j]));

            if (itr == arr.end())
                continue;
            if (const int idx = itr - arr.begin(); idx < j) cnt += (j - idx);
        }

    cout << cnt << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}