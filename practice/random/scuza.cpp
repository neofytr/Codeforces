#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> steps(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> steps[r];

    vector<int> p(n + 1, 0);
    for (int r = 1; r <= n; r++)
        p[r] = max(p[r - 1], steps[r]);

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] = prefix[r - 1] + steps[r];

    int k;
    while (q--) {
        cin >> k;

        int left = 0;
        int right = n + 1;
        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (p[mid] <= k)
                left = mid;
            else
                right = mid;
        }

        cout << prefix[left] << " ";
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