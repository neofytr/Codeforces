#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int dfs(int node, int parent, vector<int> &cnt, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1) 
		return cnt[node] = 1;

	for (int v : tree[node])
		if (v != parent)
			cnt[node] += dfs(v, node, cnt, tree);
	return cnt[node];
}

void solve() {
	int n; cin >> n;

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	vector<int> cnt(n + 1, 0);
	dfs(1, -1, cnt, tree);

	int x, y;
	int q; cin >> q;
	while (q--) {
		cin >> x >> y;
		cout << cnt[x] * cnt[y] << endl;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}