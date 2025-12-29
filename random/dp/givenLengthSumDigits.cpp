#include <bits/stdc++.h>
using namespace std;

string dp[105][905];
string gp[105][905];

int main() {
    int m, s;
    cin >> m >> s;

    if (s == 0) {
        if (m == 1)
            cout << "0 0" << endl;
        else
            cout << "-1 -1" << endl;
        return 0;
    }

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= s; j++)
            dp[i][j] = "N", gp[i][j] = "N";

    dp[0][0] = "";
    gp[0][0] = "";

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= s; j++) {
            for (int d = 9; d >= 0; d--) {
                if (i == m && d == 0 && m > 1)
                    continue;

                if (j >= d && dp[i - 1][j - d] != "N") {
                    string val = char('0' + d) + dp[i - 1][j - d];
                    if (dp[i][j] == "N" || val > dp[i][j]) {
                        dp[i][j] = val;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= s; j++) {
            for (int d = 0; d <= 9; d++) {
                if (i == m && d == 0 && m > 1)
                    continue;

                if (j >= d && gp[i - 1][j - d] != "N") {
                    string val = char('0' + d) + gp[i - 1][j - d];
                    if (gp[i][j] == "N" || val < gp[i][j]) {
                        gp[i][j] = val;
                    }
                }
            }
        }
    }

    if (dp[m][s] == "N") {
        cout << "-1 -1" << endl;
    } else {
        cout << gp[m][s] << " " << dp[m][s] << endl;
    }

    return 0;
}