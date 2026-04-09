#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int arr[2 + 1][MAX + 1];
int up[MAX + 1];
int down[MAX + 1];

void solve() {
    int m;
    cin >> m;

    for (int r = 1; r <= 2; r++)
        for (int c = 1; c <= m; c++)
            cin >> arr[r][c];

    up[0] = 0, down[0] = 0;
    for (int c = 1; c <= m; c++)
        up[c] = up[c - 1] + arr[1][c], down[c] = down[c - 1] + arr[2][c];

    //     c
    // 1 2 3 4 5 .... m
    // 1 2 3 4 5 .... m

    // (up[r] + down[m] - down[r - 1]) - up[min(r, c)] - (down[m] - down[max(r, c) - 1]) if bob gets down at r
    // up[r] - up[min(r, c)] + down[max(r, c) - 1] - down[r - 1] for 1 <= r <= m

    int mini = LLONG_MAX;
    for (int c = 1; c <= m; c++) {
        int b = max(down[c - 1], up[m] - up[c]);
        mini = min(b, mini);
    }

    cout << mini << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}