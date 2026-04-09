#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: connectingTwoBarns
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: hard
// Tags: 
// Strategy: 

void solve() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    while(m--)
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<vector<int>> component;
    vector<bool> vis(n + 1, false);
    queue<int> que;

    for (int r = 1; r <= n; r++)
        if (!vis[r]) {
            vector<int> comp;
            vis[r] = true;
            que.push(r);

            while(!que.empty()) {
                int x = que.front();
                que.pop();
                comp.push_back(x);

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }
            sort(comp.begin(), comp.end()); // sort each component
            component.push_back(move(comp));
        }

    int srcComponent = -1, dstComponent = -1;
    for (int r = 0; r < component.size(); r++) {
        if (binary_search(component[r].begin(), component[r].end(), 1)) srcComponent = r;
        if (binary_search(component[r].begin(), component[r].end(), n)) dstComponent = r;
    }

    // already connected
    if (srcComponent == dstComponent) {
        cout << 0 << endl;
        return;
    }

    vector<pair<int,int>> mergedComponents; // (node value, component id)
    for (int r = 0; r < component.size(); r++)
        for (int x : component[r])
            mergedComponents.push_back({x, r});

    sort(mergedComponents.begin(), mergedComponents.end());

    vector<long long> srcMin(component.size(), LLONG_MAX);
    vector<long long> dstMin(component.size(), LLONG_MAX);

    int nearestSrc = -1;
    for (auto &[v, c] : mergedComponents) {
        if (c == srcComponent) nearestSrc = v;
        else if (nearestSrc != -1) srcMin[c] = min(srcMin[c], (v - nearestSrc) * (v - nearestSrc));
    }

    int nearestDst = -1;
    for (int r = (int)mergedComponents.size() - 1; r >= 0; r--) {
        int v = mergedComponents[r].first;
        int c = mergedComponents[r].second;
        if (c == dstComponent) nearestDst = v;
        else if (nearestDst != -1) dstMin[c] = min(dstMin[c], (v - nearestDst) * (v - nearestDst));
    }

    long long minCost = srcMin[dstComponent]; // direct connection
    for (int r = 0; r < component.size(); r++)
        if (r != srcComponent && r != dstComponent)
            if (srcMin[r] != LLONG_MAX && dstMin[r] != LLONG_MAX)
                minCost = min(minCost, srcMin[r] + dstMin[r]);

    cout << minCost << endl;
}


int32_t main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}