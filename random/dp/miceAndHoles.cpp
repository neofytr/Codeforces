#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 5000
#define INF (int)1e12

int x[MAX + 1];
pair<int, int> h[MAX + 1];

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= m; i++)
        cin >> h[i].first >> h[i].second;

    sort(x + 1, x + n + 1);
    sort(h + 1, h + m + 1);

    // merge holes with same position
    int nm = 0;
    for (int i = 1; i <= m; i++) {
        if (nm == 0 || h[nm].first != h[i].first)
            h[++nm] = h[i];
        else
            h[nm].second += h[i].second;
    }
    m = nm;

    vector<int> prev(n + 1, INF), cur(n + 1, INF);
    vector<int> cost(n + 1, 0);

    prev[0] = 0;

    for (int j = 1; j <= m; j++) {
        // build cost prefix for hole j
        cost[0] = 0;
        for (int i = 1; i <= n; i++)
            cost[i] = cost[i - 1] + llabs(h[j].first - x[i]);

        deque<int> dq;
        cur[0] = 0;

        for (int i = 1; i <= n; i++) {
            // option 1: don't use this hole
            cur[i] = prev[i];

            int left = i - min(i, h[j].second);
            int right = i - 1;

            while (!dq.empty() && dq.front() < left)
                dq.pop_front();

            int val = prev[right] - cost[right];
            while (!dq.empty() &&
                   prev[dq.back()] - cost[dq.back()] >= val)
                dq.pop_back();
            dq.push_back(right);

            cur[i] = min(cur[i],
                         prev[dq.front()] - cost[dq.front()] + cost[i]);
        }

        swap(prev, cur);
        fill(cur.begin(), cur.end(), INF);
    }

    if (prev[n] >= INF) cout << -1 << '\n';
    else cout << prev[n] << '\n';

    return 0;
}