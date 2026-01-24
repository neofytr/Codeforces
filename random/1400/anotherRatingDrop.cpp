#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int res = 0;
	for (int a = 0; a <= 62; a++) {
		int b = (1ll << a);
		res += a * ((n - b + 1) / b + 1);
	}

	cout << res << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}