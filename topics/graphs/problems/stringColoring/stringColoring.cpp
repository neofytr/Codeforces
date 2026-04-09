#include <bits/stdc++.h>
using namespace std;

#define int long long

bool dfs(int x, vector<int> &color, vector<vector<int>> &graph) {
    for (int v : graph[x])
        if (color[v] == -1) {
            color[v] = !color[x];
            if (!dfs(v, color, graph))
                return false;
        } else if (color[v] == color[x])
            return false;
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string str;
    cin >> str;

    vector<vector<int>> graph(n);
    multimap<char, int> s;

    for (int r = 0; r < n; r++) {
        int c = str[r];
        for (auto itr = s.upper_bound(c); itr != s.end(); ++itr) // all greater characters seen so far
                graph[r].push_back(itr->second), graph[itr->second].push_back(r);
        s.insert({c, r});
    }

    vector<int> color(n, -1);
    for (int r = 0; r < n; r++) 
        if (color[r] == -1) {
            color[r] = 0;
            if (!dfs(r, color, graph)) {
                cout << "NO\n";
                return 0;
            }
        }

    cout << "YES\n";
    for (int v : color) cout << v;
    cout << "\n";
}
