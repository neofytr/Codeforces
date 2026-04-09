#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: revegetation
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=920
// Difficulty: hard
// Tags: 
// Strategy: 

class disjointSetUnion {
private:
    vector<int> size;

public:
    vector<int> parent;
    disjointSetUnion(int n) {
        parent.resize(n);
        size.resize(n);

        for (int r = 0; r < n; r++)
            parent[r] = r, size[r] = 1;
    }

    int root(int x) {
        int y = x;
        while(x != parent[x])
            x = parent[x];

        int tmp;
        while(y != parent[y])
            tmp = parent[y], parent[y] = x, y = tmp;
        return x;
    }

    void unite(int x, int y) {
        int rootX = root(x);
        int rootY = root(y);

        if (rootX == rootY)
            return;

        if (size[rootY] > size[rootX])
            swap(rootY, rootX);

        // sizeX >= sizeY
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    }

    bool connected(int x, int y) {
        return root(x) == root(y);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    disjointSetUnion dsu(n);
    vector<vector<int>> graph(n);
    vector<pair<int, int>> edges;

    char ch;
    int u, v;
    while(m--) {
        cin >> ch >> u >> v;
        u--, v--;
        if (ch == 'S')
            dsu.unite(u, v);
        else 
            edges.push_back({u, v});
    }

    for (auto &[u, v] : edges)
        graph[dsu.root(u)].push_back(dsu.root(v)), graph[dsu.root(v)].push_back(dsu.root(u));

    queue<int> que;
    vector<int> color(n, -1);

    int ways = 0;
    bool canBeDone = true;

    for (int r = 0; r < n && canBeDone; r++)
        if (color[r] == -1 && dsu.parent[r] == r) {
            color[r] = 0;
            que.push(r);
            while(!que.empty() && canBeDone) {
                int x = que.front();
                que.pop();

                for (int v : graph[x]) {
                    if (color[v] == -1)
                        color[v] = !color[x], que.push(v);
                    else if (color[v] != !color[x] || dsu.connected(v, x)) {
                        canBeDone = false;
                        break;
                    }
                }
            }

            ways++;
        }

    if (!canBeDone)
        cout << 0 << endl;
    else {
        cout << 1;
        while(ways--)
            cout << 0;
        cout << endl;
    }
    return 0;
}