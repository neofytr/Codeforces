#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int t) {
	int n, l, r, k;
	cin >> n >> l >> r >> k;

	if (n & 1) {
		cout << l << endl;
		return;
	}

	if (n == 2) {
		cout << -1 << endl;
		return;
	}

	int highest = -1;
	for (int b = 63; b >= 0; b--)
		if (l & (1ll << b)) {
			highest = b;
			break;
		}

	if ((1ll << (highest + 1)) > r) {
		cout << -1 << endl;
		return;
	}

	if (k <= n - 2) {
		cout << l << endl;
	} else {
		cout << (1ll << (highest + 1)) << endl;
	}
}

int32_t main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		solve(i);
	}
	return 0;
}
