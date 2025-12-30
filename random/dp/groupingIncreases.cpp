#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first)
            return a.first < b.first; // min first
        return a.second > b.second;   // max second
    }
};

int arr[MAX + 1];
int dp[MAX + 1];
int p[MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    p[0] = p[1] = 0;
    for (int r = 2; r <= n; r++)
        p[r] += p[r - 1] + (arr[r] > arr[r - 1] ? 1 : 0);

    for (int r = 1; r <= n; r++)
        cout << p[r] << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}