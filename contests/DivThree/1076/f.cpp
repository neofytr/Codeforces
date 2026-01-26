#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, Ax, Ay, Bx, By;
	cin >> n >> Ax >> Ay >> Bx >> By;

	map<int, set<int>> f;
	vector<int> x(n + 1), y(n + 1);
	for (int r = 1; r <= n; r++) cin >> x[r];
	for (int r = 1; r <= n; r++) cin >> y[r];

	for (int r = 1; r <= n; r++)
		f[x[r]].insert(y[r]);
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}