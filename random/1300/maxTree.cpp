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
		if (x > y && p[x] <= p[y]) p[x] = p[y] + 1;
		if (y >= x && p[y] <= p[x]) p[y] = p[x] + 1;
	}

	for (int r = 1; r <= n; r++) cout << p[r] << " ";
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