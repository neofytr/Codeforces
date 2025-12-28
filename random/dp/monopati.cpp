#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> path(2 * n + 1, vector<int>(2 + 1));
    for (int row = 1; row <= 2; row++)
        for (int col = 1; col <= 2 * n; col++)
            cin >> path[row][col];

    vector<int> upMax(2 * n + 1, LLONG_MIN), upMin(2 * n + 1, LLONG_MAX);
    vector<int> downMax(2 * n + 1, LLONG_MIN), downMin(2 * n + 1, LLONG_MAX);

    for (int col = 1; col <= 2 * n; col++) {
        upMax[col] = max(upMax[col - 1], path[1][col]);
        upMin[col] = min(upMin[col - 1], path[1][col]);
    }

    downMin[2 * n] = downMax[2 * n] = path[1][2 * n];
    for (int col = 2 * n - 1; col >= 1; col--) {
        downMin[col] = min(downMin[col + 1], path[2][col]);
        downMax[col] = max(downMax[col + 1], path[2][col]);
    }

    int cnt = 0, currL = 1, currR = 2 * n;
    for (int t = 1; t <= 2 * n; t++) {
        int l = min(upMin[t], downMin[t]);
        int r = max(upMax[t], downMax[t]);

        if (l <= currL && r >= currR)
            continue;

        if (l > currL && r < currR) {
            cnt += (l - currL + 1) * (currR - r + 1), currL = l, currR = r;
            continue;
        }

        if (r <= currR && r >= currL && l < currL) {
            cnt += (currR - r + 1) * (l);
            currR = r;
            continue;
        }

        if (l >= currL && l <= currR && r > currR) {
            cnt += (l - currL + 1) * (2 * n - r + 1);
            l = currL;
            continue;
        }

        if (r < currL) {
        }
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}