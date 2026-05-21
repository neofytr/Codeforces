#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, d, h; cin >> n >> d >> h;
	vector<int> y(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> y[i];
	for (int i = 1; i <= n; i++) p[i] = p[i - 1] + y[i];

	double area = 0;
	for (int i = 1; i <= n; i++) {
		area += 0.5 * d * h;

		int low = y[i] + 1, high = y[i] + h - 1;
		int l = lower_bound(y.begin() + 1, y.end(), low) - y.begin();
		int r = lower_bound(y.begin() + 1, y.end(), high + 1) - y.begin();
		if (r - 1 < l) continue;

		r--;
		int num = r - l + 1;
		int overlap = (0.5 * d * (y[i] + h) * num - 0.5 * d * (p[r] - p[l - 1])); 
		cout << l << " " << r << endl;
		cout << i << " " << overlap << endl;
		area -= overlap; 
	}

	cout << area << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}