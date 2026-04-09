#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, d; cin >> n >> k >> d;

	int u, v;
	set<int> police;
	vector<set<int>> tree(n + 1);
	map<pair<int, int>, int> f;
	for (int r = 1; r <= k; r++) cin >> v, police.insert(v);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, f[{u, v}] = f[{v, u}] = r, tree[u].insert(v), tree[v].insert(u);

	queue<int> que;
	vector<int> dist(n + 1, LLONG_MAX);
	for (int p : police)
		que.push(p), dist[p] = 0;

	while (!que.empty()) {
		int x = que.front(); que.pop();
		int d = dist[x];
		for (int v : tree[x])
			if (dist[v] > d + 1)
				dist[v] = d + 1, que.push(v);
	}

	vector<int> edges;
	for (int p : police) {
		int src = p;
		queue<pair<int, int>> q;
		q.push({src, -1});
		while (!q.empty()) {
			auto [x, p] = q.front(); q.pop();
			vector<int> rem;
			for (int v : tree[x])
				if (v != p && dist[v] > dist[x])
					q.push({v, x});
				else if (v != p && dist[v] <= dist[x]) {
					rem.push_back(v);
				}
			for (int r : rem)
				tree[r].erase(x), tree[x].erase(r), edges.push_back(f[{x, r}]);
		}
	}

	cout << edges.size() << endl;
	for (int r : edges)
		cout << r << " ";
	cout << endl;
	return 0;
}