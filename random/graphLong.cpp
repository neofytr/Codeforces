#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m;
	cin >> n >> m;

	int u, v;
	vector<vector<int>> graph(n + 1);
	vector<pair<int, int>> edges;
	while(m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u), edges.push_back({u, v});

	vector<int> p(n + 1, -1);
	queue<pair<int, int>> que;

	int src = 1;
	p[src] = 0;
	que.push({src, -1});
	while (!que.empty()) {
		auto [node, parent] = que.front();
		que.pop();

		for (int v : graph[node])
			if (p[v] == -1) {
				p[v] = !p[node];
				que.push({v, node});
			} else if (p[v] == p[node]) {
				cout << "NO" << endl;
				return 0;
			}
	}

	cout << "YES" << endl;
	for (auto &[u, v] : edges)
		cout << p[u];
	cout << endl;
	return 0;
}