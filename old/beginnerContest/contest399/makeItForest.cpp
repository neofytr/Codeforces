#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN);

pair<int, int> dfs(int node)
{
    visited[node] = true;
    int nodes = 1;
    int edges = graph[node].size();

    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            auto [sub_nodes, sub_edges] = dfs(neighbor);
            nodes += sub_nodes;
            edges += sub_edges;
        }
    }
    return {nodes, edges};
}

int main()
{
    int n, m;
    cin >> n >> m;

    int u, v;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int edges_to_delete = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            auto [nodes, edges] = dfs(i);
            edges /= 2;
            edges_to_delete += edges - (nodes - 1);
        }
    }

    cout << edges_to_delete << '\n';
    return 0;
}
