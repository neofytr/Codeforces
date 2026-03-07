#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, h; cin >> n >> h;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	auto can = [&](int x) {
		// can the humanois absorb atleast x astronauts?
	};

	
	int left = 0;
	int right = n + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) left = mid;
		else right = mid;
	}

	cout << left << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}