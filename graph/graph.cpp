#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; // n = number of nodes, m = number of edges
    cin >> n >> m;

    int a, b, w; // a and b are endpoints of an edge, w is the weight

    // in weighted graphs, we usually assume that there can only be one undirected, or two directed edges
    // between any two nodes

    // -------------------------------------
    // undirected unweighted graph
    // -------------------------------------

    // 2D vector (n+1) x (n+1), 0/1 entries or counts of edges
    vector<vector<int>> adjMatrixUndirUnw(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adjMatrixUndirUnw[a][b]++;
        adjMatrixUndirUnw[b][a]++;
    }

    // array of vectors; adjListUndirUnw[x] contains neighbors of x
    vector<vector<int>> adjListUndirUnw(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adjListUndirUnw[a].push_back(b);
        adjListUndirUnw[b].push_back(a);
    }

    // -------------------------------------
    // undirected weighted graph
    // -------------------------------------

    // 2D vector (n+1) x (n+1), stores weights of edges, 0 if no edge
    vector<vector<int>> adjMatrixUndirW(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adjMatrixUndirW[a][b] = w;
        adjMatrixUndirW[b][a] = w;
    }

    // array of vectors of pairs; each pair = (neighbor, weight)
    vector<vector<pair<int, int>>> adjListUndirW(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adjListUndirW[a].emplace_back(b, w);
        adjListUndirW[b].emplace_back(a, w);
    }

    // -------------------------------------
    // directed unweighted graph
    // -------------------------------------

    // 2D vector (n+1) x (n+1), stores 1 or count of edges from a to b
    vector<vector<int>> adjMatrixDirUnw(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adjMatrixDirUnw[a][b]++;
    }

    // array of vectors; adjListDirUnw[x] contains nodes reachable from x
    vector<vector<int>> adjListDirUnw(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        adjListDirUnw[a].push_back(b);
    }

    // -------------------------------------
    // directed weighted graph
    // -------------------------------------

    // 2D vector (n+1) x (n+1), stores weights from a to b, 0 if no edge
    vector<vector<int>> adjMatrixDirW(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adjMatrixDirW[a][b] = w;
    }

    // array of vectors of pairs; each pair = (neighbor, weight)
    vector<vector<pair<int, int>>> adjListDirW(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        adjListDirW[a].emplace_back(b, w);
    }
}
