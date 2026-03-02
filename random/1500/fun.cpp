#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, x; cin >> n >> x;

	int cnt = 0;
	for (int a = 1; a <= x; a++)
		for (int b = 1; b <= n / a; b++) {
			int r = min(x - (a + b), (n - a * b) / (a + b));
			if (r >= 1) cnt += r;
		}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}