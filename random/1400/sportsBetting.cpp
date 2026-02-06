#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	unordered_map<int, int> f;

	int v;
	for (int r = 1; r <= n; r++) cin >> v, f[v]++;

	for (auto &[e, c] : f) {
		if (c >= 4) {
			cout << "YES" << endl;
			return;
		}

		if (c >= 2 && (f[e - 1] >= 2 || f[e + 1] >= 2)) {
			cout << "YES" << endl;
			return;
		}

		if (c >= 1 && f[e - 1] >= 2 && f[e + 1] >= 2) {
			cout << "YES" << endl;
			return;
		}

		if (c >= 3 && (f[e - 1] >= 1 || f[e + 1] >= 1)) {
			cout << "YES"  << endl;
			return;
		}

		if (c >= 1 && f[e - 1] >= 2 && f[e + 1] >= 1 && f[e + 2] >= 2) {
			cout << "YES" << endl;
			return;
		}
	}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}