#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cherryAndBits
// URL: https://www.codechef.com/CENS2020/problems/CENS20A
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m));
    for (int row = 0; row < n; row++) {
        string str;
        cin >> str;
        for (int col = 0; col < m; col++) {
            arr[row][col] = str[col] - '0';
        }
    }

    int q;
    cin >> q;
    int x1, y1, x2, y2;

    vector<vector<int>> diff(n + 1, vector<int>(m + 1, 0));
    while (q--) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        diff[y1][x1] += 1;
        diff[y1][x2 + 1] -= 1;
        diff[y2 + 1][x1] -= 1;
        diff[y2 + 1][x2 + 1] += 1;
    }

    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
    for (int row = 1; row <= n; row++)
        for (int col = 1; col <= m; col++)
            prefix[row][col] = prefix[row - 1][col] + prefix[row][col - 1] - prefix[row - 1][col - 1] + diff[row - 1][col - 1];

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++)
            if (prefix[row + 1][col + 1] & 1)
                cout << !arr[row][col];
            else
                cout << arr[row][col];
        cout << endl;
    }

    return 0;
}