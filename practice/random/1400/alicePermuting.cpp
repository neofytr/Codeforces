#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, b, c; cin >> n >> b >> c;
	if (!b) {
		if (c >= n) {
			cout << n << endl;
			return;
		}

		if (c == n - 1 || c == n - 2) {
			cout << n - 1 << endl;
			return;
		}

		cout << -1 << endl;
		return;
	}

	int left = max((2 * b - 1 - c) / b, 1ll);
	int right = min((n + b - c - 1) / b, n);

	if (right >= left)
		cout << n - (right - left + 1) << endl;
	else 
		cout << n << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}