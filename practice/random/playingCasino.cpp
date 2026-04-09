#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> cards(m + 1, vector<int>(n + 1));
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= m; c++)
                cin >> cards[c][r];

        int sum = 0;
        for (int c = 1; c <= m; c++) {
            vector<int> &v = cards[c];
            sort(v.begin(), v.end());

            vector<int> prefix(n + 1, 0);
            for (int r = 1; r <= n; r++)
                prefix[r] += prefix[r - 1] + v[r];
            for (int r = 1; r <= n; r++)
                sum += (prefix[n] - prefix[r] - v[r] * (n - r));
        }
        cout << sum << endl;
    }

    return 0;
}