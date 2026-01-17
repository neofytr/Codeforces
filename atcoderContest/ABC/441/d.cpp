#include <bits/stdc++.h>
using namespace std;

#define int long long 

set<int> vert;
int n, m, l, s, t;
vector<vector<pair<int, int>>> graph;

void dfs(int curr, int left, int cost) {
	if (!left) {
		if (cost >= s && cost <= t)
			vert.insert(curr);
		return;
	}

	for (auto &[v, c] : graph[curr])
		dfs(v, left - 1, cost + c);
}

int32_t main() {
	cin >> n >> m >> l >> s >> t;
	graph.resize(n + 1);

	int u, v, c;
	while (m--)
		cin >> u >> v >> c, graph[u].push_back({v, c});

	dfs(1, l, 0);
	for (int e : vert)
		cout << e << " ";
	cout << endl;
}