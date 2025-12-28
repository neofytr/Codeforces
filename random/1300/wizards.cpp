#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<vector<int>> inv(n + 1, vector<int>(n + 1, 0));
    for (int l = 1; l <= n; l++)
        for (int r = l + 1; r <= n; r++)
            inv[l][r] += inv[l][r - 1] + (arr[l] > arr[r] ? 1 : 0) + (arr[r] > arr[l] ? -1 : 0);

    int lmax = -1, rmax = -1;
    int maxi = 0;
    for (int l = 1; l <= n; l++)
        for (int r = l + 1; r <= n; r++) {
            // selecting [l, r]
            if (inv[l][r] > maxi)
                maxi = inv[l][r], lmax = l, rmax = r;
        }

    if (lmax == -1 && rmax == -1)
        cout << 1 << " " << 1 << endl;
    else
        cout << lmax << " " << rmax << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}