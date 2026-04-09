#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	int u, v;
	vector<vector<int>> graph(n + 1);
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	int src = 1;
	vector<bool> sel(n + 1, false), vis(n + 1, false);
	queue<pair<int, int>> que;

	vis[src] = true, que.push({src, 0});
	while (!que.empty()) {
		auto [x, d] = que.front(); que.pop();
		if (!(d & 1)) sel[x] = true;
		for (int v : graph[x])
			if (!vis[v]) vis[v] = true, que.push({v, d + 1}); 
	}

	int cnt = 0;
	for (int r = 1; r <= n; r++)
		if (sel[r]) cnt++;
	if (cnt <= n / 2) {
		cout << cnt << endl;
		for (int r = 1; r <= n; r++)
			if (sel[r]) cout << r << " ";
		cout << endl;
		return;
	}

	for (int r = 1; r <= n; r++) sel[r] = vis[r] = false;
	vis[src] = true, que.push({src, 0});
	while (!que.empty()) {
		auto [x, d] = que.front(); que.pop();
		if (d & 1) sel[x] = true;
		for (int v : graph[x])
			if (!vis[v]) vis[v] = true, que.push({v, d + 1});
	}

	cnt = 0;
	for (int r = 1; r <= n; r++)
		if (sel[r]) cnt++;
	cout << cnt << endl;
	for (int r = 1; r <= n; r++)
		if (sel[r]) cout << r << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}