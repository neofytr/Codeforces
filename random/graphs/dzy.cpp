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
	vector<int> vis(n + 1, false);
	int res = 1;
	for (int r = 1; r <= n; r++)
		if (!vis[r]) {
			int cnt = 0;
			vis[r] = true, que.push(r);
			while(!que.empty()) {
				int x = que.front(); que.pop();
				cnt++;
				for (int v : graph[x])
					if (!vis[v]) vis[v] = true, que.push(v);
			}

			res = res * (1ll << (cnt - 1));
		}

	cout << res << endl;
	return 0;
}