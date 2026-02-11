#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	int u, v;
	vector<vector<int>> graph(n + 1);
	while (m--) 
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	queue<int> que;
	vector<int> color(n + 1, -1);
	for (int node = 1; node <= n; node++)
		if (color[node] == -1) {
			que.push(node), color[node] = 0;
			while (!que.empty()) {
				int x = que.front(); que.pop();
				for (int v : graph[x])
					if (color[v] == -1) color[v] = !color[x], que.push(v);
					else if (color[v] == color[x]) {
						cout << "IMPOSSIBLE" << endl;
						return 0;
					}
			}
		}

	for (int r = 1; r <= n; r++)
		cout << color[r] + 1 <<  " ";
	cout << endl;
	return 0;
}