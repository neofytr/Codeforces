#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (1000)

int cntB[MAX + 1];
int cntG[MAX + 1];

int dp[MAX + 1][2];
int dpm[MAX + 1];
int32_t main() {
    int n, v;
    cin >> n;
    for (int r = 1; r <= n; r++)
        cin >> v, cntB[v]++;

    int m;
    cin >> m;
    for (int r = 1; r <= m; r++)
        cin >> v, cntG[v]++;

    for (int r = 2; r <= MAX; r++) {
        dp[r][0] = dpm[r - 1] + min(cntB[r], cntG[r]);
    }

    return 0;
}