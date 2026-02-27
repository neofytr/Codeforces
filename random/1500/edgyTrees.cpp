#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k; cin >> n >> k;
	vector<vector<pair<int, int>>> tree(n + 1);

	int u, v, x;
	for (int r = 1; r <= n; r++)
		cin >> u >> v >> x, tree[u].push_back({v, x}), tree[v].push_back({u, x});

	return 0;
}