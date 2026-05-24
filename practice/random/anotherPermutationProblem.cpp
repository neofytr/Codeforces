#include <bits/stdc++.h>
using namespace std;

#define int long long

struct DSU {
	vector<int> parent;

	DSU(int n) {
		parent.resize(n + 1);
		for (int i = 0; i <= n; i++) parent[i] = i;
	}

	// find the largest number <= x still available; 0 if nothing is available
	int find(int x) {
		int y = x;
		while (parent[x] != x)
			x = parent[x];

		// path compression
		int tmp;
		while (parent[y] != y)
			tmp = parent[y], parent[y] = x, y = tmp;
		return x;
	}

	// remove x
	void erase(int x) {
		parent[x] = find(x - 1);
	}
};

void solve() {
	int n; cin >> n;
	int maxi = -1;
	int start = (!(n & 1) ? (n * n - 1) / 4 : (n * n) / 4);
	for (int m = start; m <= n * n; m++) {
		DSU dsu(n);
		int sum = -m;
		for (int i = n; i >= 1; i--) {
			int j = m / i;
			j = min(j, n);
			if (!j) break;
			int x = dsu.find(j); // find(x) returns the largest number still available <= x; returns 0 if not available
			if (!x)
				break;
			sum += i * x;
			dsu.erase(x);
		}
		maxi = max(maxi, sum);
	}
	cout << maxi << '\n';
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t; cin >> t;

	while (t--)
		solve();

	return 0;
}