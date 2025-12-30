#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> f(n + 1, 0);
    for (int r = 1; r <= n; r++)
        f[r] += f[r - 1] + (arr[r] < r ? 1 : 0);

    int cnt = 0;
    for (int j = 1; j <= n; j++)
        if (arr[j] < j && arr[j] >= 2)
            cnt += f[arr[j] - 1];

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