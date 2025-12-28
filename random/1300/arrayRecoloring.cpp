#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    vector<vector<int>> rightDP(n + 2, vector<int>(k + 1, 0));
    rightDP[n + 1][0] = 0;
    for (int r = n; r >= 1; r--)
        for (int s = 1; s <= min(n - k + 1, k); s++) {
            rightDP[r][s] = arr[r] + rightDP[r + 1][s - 1];
            if (n - r >= s)
                rightDP[r][s] = max(rightDP[r][s], rightDP[r + 1][s]);
        }

    vector<int> leftDP(k + 1, 0);
    int maxi = LLONG_MIN;
    for (int i = 2; i <= n - 1; i++) {
        vector<int> newLeft(k + 1, 0);
        for (int s = 1; s <= min(i - 1, k); s++) {
            newLeft[s] = arr[i - 1] + leftDP[s - 1];
            if (i - 2 >= s)
                newLeft[s] = max(newLeft[s], leftDP[s]);
        }
        leftDP = newLeft;

        for (int l = 1; l <= min(k - 1, i - 1); l++) {
            const int r = k - l;
            if (r > (n - i))
                continue;
            maxi = max(maxi, arr[i] + leftDP[l] + rightDP[i + 1][r]);
        }
    }

    vector<int> newLeft(k + 1);
    for (int s = 1; s <= min(n - 1, k); s++) {
        newLeft[s] = arr[n - 1] + leftDP[s - 1];
        if (n - 2 >= s)
            newLeft[s] = max(newLeft[s], leftDP[s]);
    }
    leftDP = newLeft;

    maxi = max(maxi, max(arr[1] + rightDP[2][k], arr[n] + leftDP[k]));
    cout << maxi << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}
