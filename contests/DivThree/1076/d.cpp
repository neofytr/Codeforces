#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	int left = 0; // possible
	int right = n + 1; // impossible

	// maximize x * {number of levels cleared}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}