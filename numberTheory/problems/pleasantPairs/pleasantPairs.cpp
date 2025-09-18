#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: pleasantPairs
// URL: https://codeforces.com/problemset/problem/1541/B

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> arr[i];

        int cnt = 0;
        for (int s = 1; s < n; s++)
            for (int j = (2 * s) / arr[s] + 1; j * arr[s] <= 2 * n; j++) {
                int r = j * arr[s] - s;
                if (r >= 1 && r <= n && arr[r] == j)
                    cnt++;
            }
        cout << cnt << "\n";
    }
    return 0;
}
