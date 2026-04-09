#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k, q; cin >> n >> k >> q;

	vector<int> a(k + 1), b(k + 1);
	for (int r = 1; r <= k; r++) cin >> a[r];
	for (int r = 1; r <= k; r++) cin >> b[r];

	int d;
	while (q--) {
		cin >> d;
		if (!d) {
			cout << 0 << " ";
			continue;
		}

		if (d == n) {
			cout << b[k] << " ";
			continue;
		}

		int i = upper_bound(a.begin() + 1, a.end(), d) - a.begin();
		i--;
		int t = b[i] + ((d - a[i]) * (b[i + 1] - b[i])) / (a[i + 1] - a[i]);
		cout << (int)t << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}