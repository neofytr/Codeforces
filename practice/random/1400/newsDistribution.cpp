#include <bits/stdc++.h>
using namespace std;

#define int long long 

class DSU {
	public:

	vector<int> parent, size;

	DSU(int n) {
		parent.resize(n + 1), size.resize(n + 1);
		for (int r = 1; r <= n; r++)
			parent[r] = r, size[r] = 1;
	}

	int root(int x) {
		int y = x;
		while (x != parent[x]) x = parent[x];

		int tmp;
		while (y != parent[y]) {
			tmp = parent[y];
			parent[y] = x;
			y = tmp;
		}
		return x;
	}

	void join(int x, int y) {
		int rootX = root(x), rootY = root(y);
		if (rootX == rootY) return;
		if (size[rootX] < size[rootY]) swap(rootX, rootY), swap(x, y);

		parent[rootY] = rootX;
		size[rootX] += size[rootY];
	}

	bool conn(int x, int y) {
		return root(x) == root(y);
	}
};

int32_t main() {
	int n, m;
	cin >> n >> m;

	DSU dsu(n);

	while (m--) {
		int k;
		cin >> k;

		if (!k) continue;

		k--;
		int f, v;
		cin >> f;

		while (k--)
			cin >> v, dsu.join(f, v);
	}

	for (int r = 1; r <= n; r++)
		cout << dsu.size[dsu.root(r)] << " ";
	cout << endl;

	return 0;
}