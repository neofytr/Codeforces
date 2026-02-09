#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	int u, v;
	vector<vector<int>> graph(n + 1);
	vector<int> deg(n + 1, 0);
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u), deg[u]++, deg[v]++;

	set<pair<int, int>> pq;
	vector<bool> sel(n + 1, false);
	for (int r = 1; r <= n; r++)
		pq.insert({-deg[r], r});

	int cnt = 0;
	while (!pq.empty()) {
		auto [d, x] = *pq.begin();
		pq.erase(pq.begin());

		sel[x] = true;
		cnt++;
		for (int v : graph[x])
			pq.erase({-deg[v], v});
	}

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