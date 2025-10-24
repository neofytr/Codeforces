#include <bits/stdc++.h>
using namespace std;

#define int long long

bool can(int x, vector<pair<int, int>> &cave) {
    int n = (int)cave.size();
    n--;
    int sum = x;
    for (int r = 1; r <= n; r++)
        if (cave[r].first >= sum)
            return false;
        else
            sum += cave[r].second;
    return true;
}

void solve() {
    int n;
    cin >> n;

    int k, val;
    vector<pair<int, int>> cave(n + 1);
    for (int r = 1; r <= n; r++) {
        cin >> k;
        int maxi = LLONG_MIN;
        for (int i = 1; i <= k; i++)
            cin >> val, maxi = max(maxi, val - i + 1);
        cave[r] = {maxi, k};
    }

    sort(cave.begin(), cave.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first == b.first)
            return a.second > b.second; // decreasing order for second
        return a.first < b.first;       // increasing order for first
    });

    int left = 0;
    int right = 1e18;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid, cave))
            right = mid;
        else
            left = mid;
    }
    cout << right << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}