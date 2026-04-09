#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int arr[MAX + 1][MAX + 1];
int prefix[MAX + 1][MAX + 1];
int mat[MAX + 1][MAX + 1];

int32_t main() {
    int m, n, k;
    cin >> m >> n >> k;

    for (int row = 1; row <= MAX; row++)
        for (int col = 1; col <= MAX; col++)
            cin >> arr[row][col];

    for (int row = 1; row <= MAX; row++)
        for (int col = 1; col <= MAX; col++)
            prefix[row][col] += prefix[row - 1][col] + prefix[row][col - 1] - prefix[row - 1][col - 1] + arr[row][col];

    for (int row = 1; row <= MAX; row++)
        for (int col = 1; col <= MAX; col++) {
            int x1 = max(row - k, 1LL);
            int y1 = max(col - k, 1LL);
            int x2 = min(m, row + k);
            int y2 = min(n, col + k);

            mat[row][col] = prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][x2 - 1];
        }

    return 0;
}