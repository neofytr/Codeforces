#include <bits/stdc++.h>
using namespace std;

#define int long long

int diam = LLONG_MIN;

int dfs(int node, int parent, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1)
		return 1;

	int maxi1 = 0, maxi2 = 0;
	for (int v : tree[node]) 
		if (v != parent) {
			int l = dfs(v, node, tree);
			if (l > maxi1) maxi2 = maxi1, maxi1 = l;
			else if (l > maxi2) maxi2 = l;
		}

	diam = max(diam, maxi1 + maxi2 + 1); // update diameter using this node (whatever path has its turning point as this node)
	return maxi1 + 1;
} // returns the longest path starting from node in the subtree rooted at node

int32_t main() {
	int n; cin >> n;
	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	int root = 1;
	dfs(root, -1, tree);
	cout << diam << endl;
	return 0;
}