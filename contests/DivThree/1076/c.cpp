#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, q;
	cin >> n >> q;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	a[n] = max(a[n], b[n]);
	for (int r = n - 1; r >= 1; r--)
		a[r] = max({a[r], a[r + 1], b[r]});

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++)
		p[r] += p[r - 1] + a[r];

	int l, r;
	while (q--) {
		cin >> l >> r;

		cout << p[r] - p[l - 1] << " ";
	}
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