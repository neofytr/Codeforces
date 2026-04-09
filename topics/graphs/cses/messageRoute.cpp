#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    int a, b;
    while (m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int src = 1;
    int dst = n;

    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1);
    queue<int> que;

    for (int node = 1; node <= n; node++)
        parent[node] = node;
    dist[src] = 0;
    que.push(src);
    while (!que.empty()) {
        int x = que.front();
        que.pop();

        for (int v : graph[x]) {
            if (dist[x] + 1 < dist[v]) {
                dist[v] = dist[x] + 1;
                parent[v] = x;
                que.push(v);
            }
        }
    }

    if (dist[dst] == INT_MAX) {
        cout << "IMPOSSIBLE\n";
        return EXIT_SUCCESS;
    }

    cout << dist[dst] + 1 << endl;

    stack<int> st;
    int x = dst;
    while (x != parent[x]) {
        st.push(x);
        x = parent[x];
    }
    st.push(x);

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return EXIT_SUCCESS;
}