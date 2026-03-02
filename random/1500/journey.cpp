#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

double dfs(int node, int parent, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1) return 0.0;

	double res = 0;
	double cnt = 0;
	for (int v : tree[node])
		if (v != parent)
			cnt++, res += dfs(v, node, tree);

	return res / cnt + 1.0;
}

int32_t main() {
	int n; cin >> n;
	if (n == 1) {
		cout << 0.0 << endl;
		return 0;
	}
	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	cout << setprecision(24) << dfs(1, -1, tree) << endl;
	return 0;
}