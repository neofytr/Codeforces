#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

int k[MAX + 1];
int p[MAX + 1];

void solve() {
    int n, m;
    cin >> n >> m;

    for (int r = 1; r <= n; r++)
        cin >> k[r];
    for (int r = 1; r <= m; r++)
        cin >> p[r];

    int cost = 0;
    int curridx = 1;
    sort(k + 1, k + n + 1, greater<int>());

    for (int r = 1; r <= n; r++)
        if (curridx < k[r])
            cost += p[curridx++];
        else if (curridx >= k[r])
            cost += p[k[r]];

    cout << cost << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}