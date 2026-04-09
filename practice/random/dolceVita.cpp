#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, x;
    cin >> n >> x;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    sort(arr.begin() + 1, arr.end());

    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + arr[i];

    int res = 0;
    for (int r = 1; r <= n - 1; r++) {
        int below = 0;
        if (x >= prefix[r + 1])
            below = (x - prefix[r + 1]) / (r + 1) + 1;

        int above = -1;
        if (x >= prefix[r])
            above = (x - prefix[r]) / r;
        if (above >= below)
            res += (above - below + 1) * r;
    }

    if (x >= prefix[n]) {
        int above = (x - prefix[n]) / n;
        res += (above + 1) * n;
    }

    cout << res << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
