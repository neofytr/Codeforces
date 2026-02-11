#include <bits/stdc++.h>
using namespace std;

#define int long long

int dfs(int node, int parent, vector<int> &sub, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1)
		return sub[node] = 0;

	int cnt = 0;
	for (int v : tree[node])
		if (v != parent)
			cnt += (1 + dfs(v, node, sub, tree));
	return sub[node] = cnt;
}

int32_t main() {
	int n; cin >> n;

	int v;
	vector<int> sub(n + 1, 0);
	vector<vector<int>> tree(n + 1);
	for (int r = 2; r <= n; r++)
		cin >> v, tree[v].push_back(r), tree[r].push_back(v);

	dfs(1, -1, sub, tree);
	for (int r = 1; r <= n; r++)
		cout << sub[r] << " ";
	cout << endl;
	return 0;
}