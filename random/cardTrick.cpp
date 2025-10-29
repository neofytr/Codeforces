#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    int m, j, sum = 1;
    cin >> m;
    while (m--)
        cin >> j, sum += j;

    int r = sum % n;
    if (!r)
        cout << arr[n];
    else
        cout << arr[r];
    cout << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}