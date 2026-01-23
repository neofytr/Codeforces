#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	int v;
	vector<int> w(n + 1);
	for (int r = 1; r <= m; r++)
		cin >> v, w[v]++;

	int left = 0;
	int right = 1e9 + 1;

	auto can = [&](int x) {
		int cnt = 0;
		for (int v = 1; v <= n; v++)
			if (w[v] >= x) cnt += x;
			else cnt += (w[v] + (x - w[v]) / 2);

		return cnt >= m;
	};

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			right = mid;
		else 
			left = mid;
	}

	cout << right << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}