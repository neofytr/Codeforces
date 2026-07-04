#include <bits/stdc++.h>
using namespace std;

#define int long long

int dfs(int node, vector<int> &sz, vector<vector<int>> &tree) {
	sz[node] = 1;
	for (int v : tree[node])
		sz[node] += dfs(v, sz, tree);
	return sz[node];
}

int32_t main() {
	string s; cin >> s;

	int n = s.length();
	vector<int> p(n + 1, 0); p[0] = -1;
	int j = p[1];
	for (int i = 2; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != s[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	vector<vector<int>> tree(n + 1);
	for (int i = 1; i <= n; i++)
		tree[p[i]].push_back(i);

	vector<int> sz(n + 1, 0);
	dfs(0, sz, tree);
	j = p[n];
	vector<pair<int, int>> res;
	while (j > 0)
		res.push_back({j, sz[j]}), j = p[j];

	reverse(res.begin(), res.end());
	cout << res.size() + 1 << endl;
	for (auto &[l, c] : res)
		cout << l << " " << c << endl;
	cout << n << " " << 1 << endl;
	return 0;
}