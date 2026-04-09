#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    // number of (i, j), 1 <= i < j <= n,  such that
    // 1. arr[i] < i
    // 2. arr[j] < j
    // 3. i < arr[j]

    int cnt = 0;
    vector<int> idx(1, 0); // all r seen till now having arr[r] < r
    for (int j = 1; j <= n; j++) {
        if (arr[j] < j && arr[j]) {
            // f(x) = idx[x] < arr[j]
            int left = 0;           // since arr[j] >= 1, f(left) is true
            int right = idx.size(); // f(right) is false
            while (right != left + 1) {
                int mid = (left + (right - left) / 2);
                if (idx[mid] < arr[j])
                    left = mid;
                else
                    right = mid;
            }
            cnt += left;
        };
        if (arr[j] < j)
            idx.push_back(j);
    }
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