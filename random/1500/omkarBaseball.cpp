#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	int cnt = 0;
	vector<int> v(1);
	for (int r = 1; r <= n; r++)
		if (a[r] == r) cnt++, v.push_back(r);

	if (cnt == n) {
		cout << 0 << endl;
		return;
	}

	int sz = v.size() - 1;
	if (!sz) {
		cout << 1 << endl;
		return;
	}

	if (sz == 1) {
		if (v[1] == 1 || v[1] == n) {
			cout << 1 << endl;
			return;
		}

		cout << 2 << endl;
		return;
	}

	int c = 0;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}