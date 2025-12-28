#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 5000

int arr[MAX + 1];
int dp[MAX + 1][MAX + 1];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= n; r++) cin >> arr[r];

    vector<vector<int>> left(n + 1), right(n + 1);
    for (int l = 2; l <= n; l++) {
        left[l] = left[l - 1];
        left[l].push_back(arr[l - 1]);
        sort(left[l].begin(), left[l].end());
    }

    for (int r = n - 1; r >= 1; r--) {
        right[r] = right[r + 1];
        right[r].push_back(arr[r + 1]);
        sort(right[r].begin(), right[r].end());
    }

    vector<vector<int>> leftm(n + 1);
    for (int l = 2; l <= n; l++) {
        vector<int> &v = left[l];
        vector<int> &p = leftm[l];
        const int sz = (int)v.size();

        p.resize(sz + 1, 0);
        for (int i = 1; i <= sz; i++)
            p[i] += p[i - 1] + v[i - 1];
    }

    vector<vector<int>> rightm(n + 1);
    for (int r = n - 1; r >= 1; r--) {
        vector<int> &v = right[r];
        vector<int> &p = rightm[r];
        const int sz = (int)v.size();

        p.resize(sz + 1, 0);
        for (int i = 1; i <= sz; i++)
            p[i] += p[i - 1] + v[i - 1];
    }

    int maxi = LLONG_MIN;
    for (int i = 2; i <= n - 1; i++) {
        // We select i as the last element
        for (int l = 1; l <= k - 1; l++) {
            const int r = k - l;
            maxi = max(leftm[i][l] + rightm[i][r] + arr[i], maxi);
        }
    }

    maxi = max(leftm[1][k] + arr[1], arr[n] + rightm[n][k]);
    cout << maxi << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}