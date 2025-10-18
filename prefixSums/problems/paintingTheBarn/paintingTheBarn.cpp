#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1001)

// Problem: paintingTheBarn
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=919
// Difficulty: hard
// Tags: 
// Strategy: 

int grid[MAX + 1][MAX + 1];
int prefix[MAX + 1][MAX + 1];
int32_t main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int x1, y1, x2, y2;
    while(n--) {
        // (y2, x2) isn't included
        cin >> x1 >> y1 >> x2 >> y2;
        grid[y1][x1] += 1;
        grid[y2][x1] -= 1;
        grid[y1][x2] -= 1;
        grid[y2][x2] += 1;
    }

    int cnt = 0;
    for (int row = 1; row < MAX; row++)
        for (int col = 1; col < MAX; col++) {
            prefix[row][col] += prefix[row - 1][col] + prefix[row][col - 1] + grid[row - 1][col - 1] - prefix[row - 1][col - 1];
            if (prefix[row][col] == k)
                cnt++;
        }

    cout << cnt << endl;
    return 0;
}