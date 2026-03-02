#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int cnt = 0;

	for (int c = 1; c <= n; c++) {
		int x = c * c - c;
		int sq = sqrt(1 + 4 * x);
		if (sq * sq != 1 + 4 * x)
			continue;

		if ((sq - 1) & 1) continue;

		int b = (sq - 1) >> 1;
		sq = sqrt(b + c);
		if (sq * sq != b + c) continue;

		int a = sq;

		if (a >= 1 && b >= a && c >= b) cnt++;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}