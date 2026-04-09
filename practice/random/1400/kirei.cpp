#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int d[MAX + 1];
int maxi[MAX + 1];
int mini[MAX + 1];

void dfs(int node, int parent, vector<vector<int>> &tree) {
	if (parent != -1) {
		maxi[node] = max(d[node], d[node] - mini[parent]);
		mini[node] = min(d[node], d[node] - maxi[parent]);
	}

	for (int v : tree[node])
		if (v != parent)
			dfs(v, node, tree);
}

void solve() {
	int n; cin >> n;
	for (int r = 1; r <= n; r++)
		d[r] = maxi[r] = mini[r] = 0;

	for (int r = 1; r <= n; r++) cin >> d[r];

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	maxi[1] = mini[1] = d[1];
	dfs(1, -1, tree);

	for (int r = 1; r <= n; r++)
		cout << maxi[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}