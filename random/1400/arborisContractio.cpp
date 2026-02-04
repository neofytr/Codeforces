#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int dfs(int node, int parent, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1)
		return 1;

	int cnt = 0;
	for (int v : tree[node])
		if (v != parent)
			cnt += dfs(v, node, tree);
	return cnt;
}

void solve() {
	int n; cin >> n;

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	if (n == 2) {
		cout << 0 << endl;
		return;
	}

	int leaves;
	for (int r = 1; r <= n; r++)
		if (tree[r].size() > 1) {
			leaves = dfs(r, -1, tree);
			break;
		}

	int mini = LLONG_MAX;
	for (int r = 1; r <= n; r++)
		if (tree[r].size() == 1)
			mini = min(mini, leaves - 1);
		else {
			int cnt = 0;
			for (int v : tree[r])
				if (tree[v].size() == 1) cnt++;
			mini = min(mini, leaves - cnt);
		} 

	cout << mini << endl;
}


int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}