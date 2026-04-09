#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> x(n + 1), y(n + 1);
	for (int r = 1; r <= n; r++) cin >> x[r] >> y[r];

	sort(x.begin() + 1, x.end());
	sort(y.begin() + 1, y.end());
	if (n & 1) {
		cout << 1 << endl;
		return;
	}
	cout << (x[n / 2 + 1] - x[n / 2] + 1) * (y[n / 2 + 1] - y[n / 2] + 1) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}