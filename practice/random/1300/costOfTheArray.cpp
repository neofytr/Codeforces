#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    if (n - k + 2 >= 3) {
        for (int r = 2; r <= n - k + 2; r++)
            if (arr[r] > 1) {
                cout << 1 << endl;
                return;
            }

        cout << 2 << endl;
        return;
    }

    vector<int> e(1, 0);
    for (int r = 2; r <= n; r += 2)
        e.push_back(arr[r]);
    e.push_back(0);

    for (int r = 1; r <= e.size(); r++)
        if (e[r] != r) {
            cout << r << endl;
            return;
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