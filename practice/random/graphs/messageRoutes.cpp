#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	int u, v; 
	vector<vector<int>> graph(n + 1);
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	int src = 1;
	vector<int> dist(n + 1, LLONG_MAX);
	vector<int> p(n + 1, -1);
	queue<int> que;

	p[src] = -1, dist[src] = 0, que.push(src);
	while (!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : graph[x])
			if (dist[v] > dist[x] + 1) {
				p[v] = x, dist[v] = dist[x] + 1;
				que.push(v);
			}
	}

	if (dist[n] == LLONG_MAX) {
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}

	stack<int> path;
	int x = n;
	path.push(x);
	while (p[x] != -1)
		path.push(p[x]), x = p[x];

	cout << path.size() << endl;
	while (!path.empty())
		cout << path.top() << " ", path.pop();
	cout << endl;
	return 0;
}