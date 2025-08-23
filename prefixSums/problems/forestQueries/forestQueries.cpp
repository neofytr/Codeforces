#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: forestQueries
// URL: https://cses.fi/problemset/task/1652
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<vector<char>> arr(n, vector<char>(n, 0));
    char val;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            if (cin >> val; val == '*')
                arr[row][col] = 1;

    // for a,b >= 1, prefix[a][b] = sum of the elements in the rectangle bounded between (0,0) and (a-1,b-1)
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
    for (int row = 1; row <= n; row++)
        for (int col = 1; col <= n; col++)
            prefix[row][col] = prefix[row - 1][col] + prefix[row][col - 1] - prefix[row - 1][col - 1] + arr[row - 1][col - 1];

    int y1, x1, y2, x2;
    while (q--) {
        cin >> y1 >> x1 >> y2 >> x2;
        y1--, x1--, y2--, x2--;
        cout << prefix[y2 + 1][x2 + 1] - prefix[y1][x2 + 1] - prefix[y2 + 1][x1] + prefix[y1][x1] << endl;
    }
    return 0;
}