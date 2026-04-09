#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e3)

int grid[MAX + 1][MAX + 1];
int topLeft[MAX + 1][MAX + 1];
int topRight[MAX + 1][MAX + 1];
int bottomLeft[MAX + 1][MAX + 1];
int bottomRight[MAX + 1][MAX + 1];

int32_t main() {
    int n, m;
    cin >> n >> m;

    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            cin >> grid[r][c];

    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++) {
            if (r >= 2)
                topLeft[r][c] = topLeft[r - 1][c];
            if (c >= 2)
                topLeft[r][c] = max(topLeft[r][c - 1], topLeft[r][c]);
            topLeft[r][c] += grid[r][c];
        }

    for (int r = 1; r <= n; r++)
        for (int c = m; c >= 1; c--) {
            if (r >= 2)
                topRight[r][c] = topRight[r - 1][c];
            if (c <= m - 1)
                topRight[r][c] = max(topRight[r][c], topRight[r][c + 1]);
            topRight[r][c] += grid[r][c];
        }

    for (int r = n; r >= 1; r--)
        for (int c = 1; c <= m; c++) {
            if (c >= 2)
                bottomLeft[r][c] = bottomLeft[r][c - 1];
            if (r <= n - 1)
                bottomLeft[r][c] = max(bottomLeft[r + 1][c], bottomLeft[r][c]);
            bottomLeft[r][c] += grid[r][c];
        }

    for (int r = n; r >= 1; r--)
        for (int c = m; c >= 1; c--) {
            if (c <= m - 1)
                bottomRight[r][c] = bottomRight[r][c + 1];
            if (r <= n - 1)
                bottomRight[r][c] = max(bottomRight[r][c], bottomRight[r + 1][c]);
            bottomRight[r][c] += grid[r][c];
        }

    int maxi = LLONG_MIN;
    for (int r = 2; r <= n - 1; r++) {
        for (int c = 2; c <= m - 1; c++) {
            int v1 = topLeft[r][c - 1] + bottomRight[r][c + 1] + bottomLeft[r + 1][c] + topRight[r - 1][c];
            int v2 = topLeft[r - 1][c] + bottomRight[r + 1][c] + bottomLeft[r][c - 1] + topRight[r][c + 1];
            maxi = max({maxi, v1, v2});
        }
    }

    cout << maxi << endl;
    return 0;
}