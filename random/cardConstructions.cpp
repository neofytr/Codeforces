#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    int k = n;
    int cnt = 0;
    while (k > 1) {
        int left = 0;
        int right = k;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if ((mid * (3 * mid + 1)) / 2 <= k)
                left = mid;
            else
                right = mid;
        }
        cnt++;
        k -= (left * (3 * left + 1)) / 2;
    }
    cout << cnt << endl;
    return;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}