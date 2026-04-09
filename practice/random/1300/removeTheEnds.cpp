#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    int j = n, i = n, psum = 0, nsum = 0;
    int res = 0;

    while (i >= 1) {
        while (i >= 1 && arr[i] > 0) {
            psum += arr[i];
            i--;
        }

        if (i >= 1) {
            int cost = -arr[i];
            int current_balance = psum - nsum;

            if (cost > current_balance) {
                res += cost + nsum;

                psum = 0;
                nsum = 0;

                j = i - 1;
                i = j;
            } else {
                nsum += cost;
                i--;
            }
        }
    }

    for (int r = 1; r <= j; r++)
        if (arr[r] > 0)
            res += arr[r];

    cout << res << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}