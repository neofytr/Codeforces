#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(100)

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];
    sort(arr.begin() + 1, arr.end());

    int res = 0;
    for (int r = 1; r <= n - 2 * k; r++)
        res += arr[r];

    for (int r = n - 2 * k + 1; r <= n - k; r++)
        res += (arr[r] / arr[r + k]);

    cout << res << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}