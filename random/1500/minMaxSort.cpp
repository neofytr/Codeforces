#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> p(n + 1), q(n + 1);
	for (int i = 1; i <= n; i++) cin >> p[i], q[p[i]] = i;

	auto can = [&](int x) {
		for (int i = x; i <= n - x; i++)
			if (q[i + 1] < q[i]) return false;
		return true;
	};

	if (can(1)) {
		cout << 0 << endl;
		return;
	}
	
	int left = 1;
	int right = n + 1;
	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) right = mid;
		else left = mid;
	}

	cout << right - 1 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}