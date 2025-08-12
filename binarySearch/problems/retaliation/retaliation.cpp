#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    if (!(cin >> n))
        return;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    if (n == 1) {
        // a + b = arr[1] -> choose a = arr[1], b = 0 (non-negative ints)
        cout << "Yes\n";
        return;
    }

    // solve from r = 1 and r = 2:
    // a + n*b = arr1
    // 2a + (n-1)*b = arr2
    // subtract: (2a+2n b) - (2a+(n-1)b) => (n+1)*b = 2*arr1 - arr2
    int denom = n + 1;
    long long num_b = 2 * arr[1] - arr[2];

    if (num_b % denom != 0) {
        cout << "No\n";
        return;
    }
    int b = num_b / denom;
    if (b < 0) {
        cout << "No\n";
        return;
    }
    int a = arr[1] - n * b;
    if (a < 0) {
        cout << "No\n";
        return;
    }

    // verify all r
    for (int r = 1; r <= n; ++r) {
        long long left = a * r + b * (n - r + 1);
        if (left != arr[r]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
