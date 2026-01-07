#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define VMAX (int)(1e4)

int h[MAX + 1];
int dp[MAX + 1];
int f[MAX + 1];

int clst(int x, set<int> &s) {}

int32_t main() {
    int n, k;
    cin >> n >> k;

    for (int r = 1; r <= n; r++)
        cin >> h[r];
    for (int r = 1; r <= VMAX; r++)
        f[r] = 0;

    // dp[r] is the minimum cost incurred before the frog reaches the stone r
    dp[1] = 0;
    set<int> s;
    int cnt = 0;

    s.insert(h[1]), cnt++, f[h[1]]++;
    for (int r = 2; r <= n; r++) {
    }
    return 0;
}