#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;

	set<pair<int, pair<int, int>>> que;
	vector<int> dist(n + 1, LLONG_MIN);
	int v, u;
	for (int r = 1; r <= k; r++) 
		cin >> v, dist[v] = 0, que.insert({0, {v, -1}});

	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	vector<vector<int>> modi(n + 1);
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}