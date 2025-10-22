#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int k = 1; k <= n; k++) {
        // f(x) = arr[k - x + 1] >= x
        int left = 1; // f(l) = true
        int right = k + 1; // f(r) = false

        // we have to find the last true
        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[k - mid + 1] >= mid)
                left = mid;
            else
                right = mid;
        }

        // [left, k] is the required subsequence
        cout << left << " ";
    }
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