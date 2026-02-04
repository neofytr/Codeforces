#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int dp[MAX + 1];
int p[MAX + 1];
int dfs(int node, int parent, vector<vector<int>> &tree) {
	p[node] = parent;
	if (tree[node].size() == 1 && parent != -1) 
		return dp[node] = 1;
	
	for (int v : tree[node])
		if (v != parent)
			dp[node] += dfs(v, node, tree);
	return dp[node];
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++) dp[r] = p[r] = 0;

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	dfs(1, -1, tree);
	int cnt = dp[1], mini = LLONG_MAX;

	for (int r = 1; r <= n; r++) {
		int c = 0;
		for (int v : tree[r])
			if (tree[v].size() == 1 && v != p[r]) c++;
		mini = min(mini, cnt - c);
	}

	cout << mini << endl;
}
	return 0;
}