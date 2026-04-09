#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: maxMinPath
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D
// Difficulty: hard
// Tags:
// Strategy:

bool pathExists(int maxWt, int maxEdges, vector<vector<pair<int, int>>> &graph) {
    // we are to find if there is a path from 1 to n such that all the edge weights are atmost maxWt
    // we will build the shortest such path, so, if its within d edges, we are done
    int n = graph.size(); // n + 1 since 1-based
    vector<int> parent(n);
    vector<int> dist(n, 1e9); // number of edges to reach each node
    queue<int> que;

    int src = 1;
    dist[src] = 0;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (auto &[v, w] : graph[u]) {
            if (w <= maxWt && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }

    return dist[n - 1] <= maxEdges;
}

pair<vector<int>, int> buildPath(int maxWt, int maxEdges, const vector<vector<pair<int, int>>> &graph) {
    int n = graph.size();
    vector<int> dist(n, 1e9);
    vector<int> parent(n, -1);
    queue<int> que;

    int src = 1;
    dist[src] = 0;
    parent[src] = src;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (auto &[v, w] : graph[u]) {
            if (w <= maxWt && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                que.push(v);
            }
        }
    }

    vector<int> path;
    int dst = n - 1;
    if (parent[dst] == -1 || dist[dst] > maxEdges)
        return {{}, -1};

    while (dst != parent[dst]) {
        path.push_back(dst);
        dst = parent[dst];
    }
    path.push_back(dst);
    reverse(path.begin(), path.end());

    return {path, (int)path.size() - 1}; // edges = nodes - 1
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, d;
    cin >> n >> m >> d;

    vector<vector<pair<int, int>>> graph(n + 1);
    int a, b, c;
    int maxwt = -1;
    while (m--) {
        cin >> a >> b >> c;
        maxwt = max(maxwt, c);
        graph[a].push_back({b, c}); // directed edges since we can only travel along the road one way
    }

    // there are n nodes labelled 1 to n and m directed edges between them
    // each edge is directed from a lower number node to a higher number node
    // this means, that is graph is acylic (a DAG basically)

    // Let x is a path from 1 to n with atmost d edges
    // We define m(x) to be the maximum edge weight in the path x
    // We are to determine min(m(x) for all paths x from 1 to n with atmost d edges)

    // We define a predicate f as follows
    // f(r) = 1 if there is a path from 1 to n with atmost d edges that has all the edge weights atmost r
    //      = 0 otherwise

    // if there is a path from 1 to n with atmost d edges that has all the edge weights atmost r, then
    // such a path with edge weights atmost r + 1 will exist

    // thus, f is monotonic

    int left = -1;     // since all edge weights are non-negative, this isnt' possible
    int right = maxwt; // since edge weights range from 0 to 1e9, this is possible

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (pathExists(mid, d, graph))
            right = mid;
        else
            left = mid;
    }

    if (!pathExists(right, d, graph)) {
        cout << -1 << endl;
        return 0;
    }

    auto [path, numEdges] = buildPath(right, d, graph);
    cout << numEdges << '\n';
    for (int v : path)
        cout << v << ' ';
    cout << '\n';

    return 0;
}