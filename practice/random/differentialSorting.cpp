#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    if (arr[n - 1] > arr[n]) {
        cout << -1 << endl;
        return;
    }

    int s = arr[n - 1] - arr[n];
    if (arr[n] >= 0) {
        cout << n - 2 << endl;
        for (int r = 1; r <= n - 2; r++)
            cout << r << " " << n - 1 << " " << n << endl;
        return;
    } else {
        for (int r = 1; r <= n - 1; r++)
            if (arr[r] > arr[r + 1]) {
                cout << -1 << endl;
                return;
            }
        cout << 0 << endl;
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}