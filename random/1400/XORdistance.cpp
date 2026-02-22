#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int a, b, r; cin >> a >> b >> r;
	if (!r) {
		cout << llabs(a - b) << endl;
		return;
	}

	if (a == b) {
		cout << 0 << endl;
		return;
	}

	if (a > b) {
		int x = 0;
		int h = -1;
		for (int bit = 63; bit >= 0; bit--)
			if (r & (1ll << bit)) {
				h = bit;
				break;
			}

		for (int bit = h; bit >= 0; bit--)
			if (!(a & (1ll << bit)) && (b & (1ll << bit)))
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}