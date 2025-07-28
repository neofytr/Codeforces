#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<bool> visited(n + 1, false);

    int a, b;
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int node = 1; node <= n; node++) {
        if (!visited[node]) {
            queue<int> q;
            q.push(node);
            visited[node] = true;

            long long componentSize = 0;
            long long edge_count = 0;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                componentSize++;
                edge_count += graph[u].size(); // each edge counted twice

                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            if (edge_count != componentSize * (componentSize - 1)) { // since each edge counted twice
                cout << "NO\n";
                return 0;
            }
        }
    }

    cout << "YES\n";
    return 0;
}
