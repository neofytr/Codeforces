#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];
	
	set<int> div;
	for (int r = 1; r * r <= b[n]; r++)
		if (!(b[n] % r))
			div.insert(r), div.insert(b[n] / r);

	set<pair<int, int>> res;
	for (int r : div)
		if (!(b[n - 1] % r))
			res.insert({r, b[n - 1] / r});
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}