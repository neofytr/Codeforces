#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int res = 0;
	for (int a = 0; a <= 62; a++) {
		int b = (1ll << a);
		if (n - b >= 0) {
			int g = ((n - b) / b + 1);
			g -= g / 2;
			res += a * g;
		}
	}

	cout << res + n << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}