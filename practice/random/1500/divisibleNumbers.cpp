#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int a, b, c, d; cin >> a >> b >> c >> d;

	for (int x = a + 1; x <= c; x++) {
		int g = gcd(a * b, x);
		int l = (a * b) / g;

		int r = d % l;
		int y = d - r;
		if (y > b && y <= d) {
			cout << x << " " << y << endl;
			return;
		}
	}

	cout << -1 << " " << -1 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}