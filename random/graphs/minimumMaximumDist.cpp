#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;

	queue<pair<int, int>> que;
	vector<int> dist(n + 1, 0);
	vector<int> which(n + 1, -1);

	int v, u;
	for (int r = 1; r <= k; r++) 
		cin >> v, dist[v] = 0, que.push({v, v}), which[v] = v;

	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	while (!que.empty()) {
		auto [x, p] = que.front(); que.pop();
		for (int v : tree[x])
			if (which[v] == -1) {
				which[v] = p;
				cout << v << " " << x << " " << p << endl;
				dist[v] = dist[x] + 1;
				que.push({v, p});
			} else if (which[v] != p && dist[x] + 1 > dist[v])
				dist[v] = dist[x] + 1, which[v] = p, que.push({v, p}), cout << v << " " << p << endl;
	}

	for (int r = 1; r <= n; r++)
		cout << dist[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}