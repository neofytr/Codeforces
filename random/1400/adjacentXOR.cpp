#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	for (int r = 1; r <= n - 1; r++)
		if (a[r] != b[r])
			a[r + 1] = b[r] ^ a[r], a[r] = b[r];

	for (int r = 1; r <= n; r++)
		if (a[r] != b[r]) {
			cout << "NO" << endl;
			return;
		}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}