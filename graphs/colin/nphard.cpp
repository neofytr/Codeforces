#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<vector<int>> graph(n + 1);
    while (m--) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    for (int node = 1; node <= n; node++) {
        if (color[node] == -1) {
            int src = node;

            queue<int> que;
            color[src] = 0;
            que.push(src);
            while (!que.empty()) {
                int x = que.front();
                que.pop();

                for (int v : graph[x]) {
                    if (color[v] == -1) {
                        color[v] = !color[x];
                        que.push(v);
                    } else if (color[v] == color[x]) {
                        cout << -1 << endl;
                        return EXIT_SUCCESS;
                    }
                }
            }
        }
    }

    int firstCount = 0;
    int secondCount = 0;
    for (int node = 1; node <= n; node++) {
        if (color[node])
            secondCount++;
        else
            firstCount++;
    }

    cout << firstCount << endl;
    for (int node = 1; node <= n; node++) {
        if (!color[node])
            cout << node << " ";
    }
    cout << endl;
    cout << secondCount << endl;
    for (int node = 1; node <= n; node++) {
        if (color[node])
            cout << node << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}