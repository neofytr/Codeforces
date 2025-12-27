#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector mat(n + 1, vector<int>(n + 1));
    if (n & 1) {
        int mx = (n + 1) / 2, my = (n + 1) / 2;
        mat[mx][my] = 0;

        int k = 1;
        for (int d = 1; d <= n / 2; d++) {
            // row = mx - d, column = my - d to my + d;
            for (int c = my - d; c <= my + d; c++)
                mat[mx - d][c] = k++;

            // row = mx + d, column = my - d to my + d
            for (int c = my - d; c <= my + d; c++)
                mat[mx + d][c] = k++;

            // column = my - d, row = mx - d + 1 to mx + d - 1
            for (int r = mx - d + 1; r <= mx + d - 1; r++)
                mat[r][my - d] = k++;

            for (int r = mx - d + 1; r <= mx + d - 1; r++)
                mat[r][my + d] = k++;
        }
    } else {
        int mx = n / 2, my = n / 2;
        int k = 0;
        for (int d = 0; d <= n / 2 - 1; d++) {
            // row = mx - d, col = my - d to my + d + 1
            for (int c = my - d; c <= my + d + 1; c++)
                mat[mx - d][c] = k++;

            for (int c = my - d; c <= my + d + 1; c++)
                mat[mx + d + 1][c] = k++;

            for (int r = mx - d + 1; r <= mx + d; r++)
                mat[r][my - d] = k++;

            for (int r = mx - d + 1; r <= mx + d; r++)
                mat[r][my + d + 1] = k++;
        }
    }

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++)
            cout << mat[r][c] << " ";
        cout << endl;
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