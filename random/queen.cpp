#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	int p, root;
	vector<int> respect(n + 1);
	vector<vector<int>> tree(n + 1);
	for (int node = 1; node <= n; node++) {
		cin >> p >> respect[node];
		if (p != -1)
			tree[p].push_back(node);
		else 
			root = node, respect[root] = 0;
	}

	vector<int> idx;
	for (int node = 1; node <= n; node++)
		if (respect[node]) {
			int cnt = 0;
			for (int v : tree[node])
				if (respect[v])
					cnt++;
			if (cnt == tree[node].size())
				idx.push_back(node);
		}

	if (idx.empty())
		cout << -1 << endl;
	else {
		for (int v :idx)
			cout << v << " ";
		cout << endl;
	}
	return 0;
}