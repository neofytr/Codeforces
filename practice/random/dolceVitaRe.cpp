#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, x; cin >> n >> x;

	int p = 0, ans = 0, a;
	for (int i = 1; i <= n; i++) {
		cin >> a; p += a;
		int alp = (x - p) / i + 1;
		if (alp >= 1) ans += alp;
	}

	cout << ans << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}