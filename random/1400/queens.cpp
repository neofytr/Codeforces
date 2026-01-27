#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n;
	cin >> n;

	int x, root;
	vector<int> c(n + 1);
	vector<vector<int>> tree(n + 1);
	for (int node = 1; node <= n; node++) {
		cin >> x >> c[node];
		if (x == -1) root = node;
		else tree[node].push_back(x), tree[x].push_back(node);
	}

	set<int> f;
	queue<pair<int, int>> q;

	q.push({root, -1});
	while (!q.empty()) {
		auto [node, parent] = q.front();
		q.pop();

		bool can = (c[node] ? true : false);
		for (int v : tree[node])
			if (v != parent) {
				if (!c[v]) can = false;

				q.push({v, node});
			}

		if (can) f.insert(node);
	}

	if (f.empty()) {
		cout << -1 << endl;
		return 0;
	}

	for (int e : f)
		cout << e << " ";
	cout << endl;
	return 0;
}