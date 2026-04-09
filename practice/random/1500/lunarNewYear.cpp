#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;

	int u, v;
	map<pair<int, int>, bool> seen;
	vector<vector<int>> graph(n + 1);
	while (m--) {
		cin >> u >> v;
		if (u == v) continue;
		if (!seen[{u, v}] && !seen[{v, u}])
			seen[{u, v}] = true, graph[u].push_back(v), graph[v].push_back(u);
	}

	int src = 1;
	set<int> nxt;
	nxt.insert(src);
	vector<bool> vis(n + 1, false); vis[src] = true;

	vector<int> ord;
	while (!nxt.empty()) {
		int x = *nxt.begin(); nxt.erase(nxt.begin());
		ord.push_back(x);

		for (int v : graph[x])
			if (!vis[v])
				vis[v] = true, nxt.insert(v);
	}

	for (int node : ord)
		cout << node << " ";
	cout << endl;
	return 0;
}