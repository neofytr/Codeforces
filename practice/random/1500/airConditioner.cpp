#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	int prev = 0;
	int left = m, right = m;
	bool done = false;
	for (int i = 1; i <= n; i++) {
		int t, l, r; cin >> t >> l >> r;

		int have = t - prev;
		if (l > right + have || r < left - have)
			done = true;

		left = max(left - have, l);
		right = min(right + have, r);
		prev = t;
	}

	if (done) {
		cout << "NO" << endl;
		return;
	}

	if (left <= right)
		cout << "YES" << endl;
}

int32_t main() {
	int q; cin >> q;
	while (q--) solve();
	return 0;
}