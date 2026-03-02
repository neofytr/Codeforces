#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int cnt = 0;

	if (n <= 3) {
		cout << 0 << endl;
		return;
	}

	int i = 3;
	while (i * i <= 2 * n - 1) {
		if (!((i * i + 1) & 1)) cnt++;
		i++;
	}
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}