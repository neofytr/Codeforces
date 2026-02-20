#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	int cnt = 0;
	for (int b = 1; b <= m; b++) {
		int left = (b + b * b) / (b * b);
		int right = (n + b) / (b * b);
		if (right >= left) cnt += (right - left + 1);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}