#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e5)
#define INF (int)(1e10)
#define MAXC (int)(26)

int dp[MAX + 1][MAXC + 1];
int v[MAX + 1];
int prv[MAX + 1];

int32_t main() {
    int n, k;
    cin >> n >> k;

    string str;
    cin >> str;
    for (int r = 1; r <= n; r++)
        v[r] = str[r - 1] - 'A' + 1;

    // dp[r][c] is the minimum number of re-paintings required in [1, r] if v[r] = c such that
    // no two neighboring cells in [1, r] are of the same color

    for (int r = 1; r <= n; r++)
        for (int s = 1; s <= k; s++)
            dp[r][s] = INF;

    for (int c = 1; c <= k; c++)
        dp[1][c] = (v[1] == c ? 0 : 1), prv[1][c] = -1;

    for (int r = 2; r <= n; r++)
        for (int c = 1; c <= k; c++) {
            int m = LLONG_MAX, l = -1;
            for (int p = 1; p <= k; p++)
                if (p != c)
                    if (dp[r - 1][p] < m)
                        m = dp[r - 1][p], l = p;
            dp[r][c] = min(m + (v[r] == c ? 0 : 1), dp[r][c]);
        }

    int mini = LLONG_MAX, minic = -1;
    for (int c = 1; c <= k; c++)
        if (dp[n][c] < mini)
            mini = dp[n][c], minic = c;

    cout << (char)(minic + 'A') << endl;
    string s;
    cout << mini << endl;
    s.push_back(minic + 'A');
    for (int r = n; r >= 2; r--) {
        minic = prv[r][minic];
        s.push_back(minic + 'A');
    }
    reverse(s.begin(), s.end());
    cout << s << endl;
    return 0;
}