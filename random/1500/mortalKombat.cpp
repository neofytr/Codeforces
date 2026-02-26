#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];

	bool allzero = true;
	for (int r = 1; r <= n; r++)
		if (a[r]) {
			allzero = false;
			break;
		}
	if (allzero) {
		cout << 0 << endl;
		return;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}