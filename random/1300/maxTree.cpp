#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int u, v, x, y;
	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n - 1; r++) {
		cin >> u >> v >> x >> y;
		if (v > u)
			p[u] += x, p[v] += y;
		else 
			p[v] += x, p[u] += y;
	}

	vector<pair<int, int>> vec;
	for (int r = 1; r <= n; r++)
		vec.push_back({p[r], r});

	sort(vec.begin(), vec.end());
	for (auto &[val, r] : vec)
		cout << r << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}