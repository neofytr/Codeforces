#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> w(n + 1), gains;
	vector<vector<int>> tree(n + 1);

	int g = 0;
	for (int r = 1; r <= n; r++) cin >> w[r], g += w[r];

	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	for (int r = 1; r <= n; r++) {
		int sz = tree[r].size() - 1;
		while (sz--) gains.push_back(w[r]);
	}

	sort(gains.rbegin(), gains.rend());

	cout << g << " ";
	for (int i = 2; i <= n - 1; i++) {
		g += gains[i - 2];
		cout << g << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}