#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> cost(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> cost[r];

    vector<int> pcost(n + 1, 0);
    for (int r = 1; r <= n; r++)
        pcost[r] += pcost[r - 1] + cost[r];

    sort(cost.begin() + 1, cost.end());
    vector<int> psorted(n + 1, 0);
    for (int r = 1; r <= n; r++)
        psorted[r] += psorted[r - 1] + cost[r];

    int m;
    cin >> m;

    int t, l, r;
    while (m--) {
        cin >> t >> l >> r;
        if (t == 1)
            cout << pcost[r] - pcost[l - 1] << endl;
        else
            cout << psorted[r] - psorted[l - 1] << endl;
    }
    return 0;
}