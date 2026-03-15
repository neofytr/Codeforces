#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	vector<vector<int>> graph(n + 1);

	int u, v;
	for (int i = 1; i <= m; i++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	vector<bool> vis(n + 1, false);
	queue<int> que;
	for (int i = 1; i <= n; i++) 
		if (!vis[i]) {
			int src = i, nodes = 0, edges = 0;
			vis[src] = true;
			que.push(src);
			while (!que.empty()) {
				int x = que.front(); que.pop();
				nodes++;
				for (int v : graph[x]) {
					if (!vis[v])
						vis[v] = true, que.push(v);
					edges++;
				}
			}

			edges >>= 1;
			if ()
		}
	return 0;
}