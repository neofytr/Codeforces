#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> points(n);
    multiset<int> xs, ys;

    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
        xs.insert(points[i].first);
        ys.insert(points[i].second);
    }

    int minCost = LLONG_MAX;

    for (int i = 0; i < n; ++i) {
        auto [x, y] = points[i];

        // temporarily remove one monster
        xs.erase(xs.find(x));
        ys.erase(ys.find(y));

        if (!xs.empty() && !ys.empty()) {
            int minX = *xs.begin();
            int maxX = *xs.rbegin();
            int minY = *ys.begin();
            int maxY = *ys.rbegin();

            int width = maxX - minX + 1;
            int height = maxY - minY + 1;
            int area = width * height;

            int monstersLeft = n - 1;

            if (area == monstersLeft) {
                // Need to expand in one direction
                int area1 = (width + 1) * height; // expand width
                int area2 = width * (height + 1); // expand height
                area = min(area1, area2);
            }

            minCost = min(minCost, area);
        }

        // restore
        xs.insert(x);
        ys.insert(y);
    }

    if (minCost == LLONG_MAX) { // a very important edge case
        minCost = 1;
    }

    cout << minCost << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
}
