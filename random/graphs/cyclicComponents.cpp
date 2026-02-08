#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int n, m; 
vector<int> graph[MAX + 1];
int deg[MAX + 1];
bool vis[MAX + 1];

int dfs(int node) {
	bool res = 1;
	if (deg[node] != 2) res = 0;

	for (int v : graph[node])
		if (!vis[v]) {
			vis[v] = true;
			res = res & dfs(v);
		}
	return res;
}

int32_t main() {
	cin >> n >> m;

	int u, v;
	while (m--) {
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);
		deg[u]++, deg[v]++;
	}

	int cnt = 0;
	for (int r = 1; r <= n; r++)
		if (!vis[r]) {
			vis[r] = true;
			cnt += dfs(r);
		}

	cout << cnt << endl;
	return 0;
}