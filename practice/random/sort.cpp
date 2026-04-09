#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        string a, b;
        cin >> a >> b;

        vector<vector<int>> prefixA(n + 1, vector<int>(26, 0));
        for (int r = 1; r <= n; r++) {
            for (int c = 0; c < 26; c++) {
                prefixA[r][c] = prefixA[r - 1][c] + ((a[r - 1] - 'a' == c) ? 1 : 0);
            }
        }

        vector<vector<int>> prefixB(n + 1, vector<int>(26, 0));
        for (int r = 1; r <= n; r++) {
            for (int c = 0; c < 26; c++) {
                prefixB[r][c] = prefixB[r - 1][c] + ((b[r - 1] - 'a' == c) ? 1 : 0);
            }
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            int ops = 0;
            for (int c = 0; c < 26; c++) {
                int cntA = prefixA[r + 1][c] - prefixA[l][c];
                int cntB = prefixB[r + 1][c] - prefixB[l][c];
                if (cntA > cntB)
                    ops += (cntA - cntB);
            }

            cout << ops << endl;
        }
    }

    return EXIT_SUCCESS;
}