#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, d, h; cin >> n >> d >> h;
	vector<int> y(n + 1);
	for (int i = 1; i <= n; i++) cin >> y[i];

	double area = 0.5 * d * h;
	for (int i = 1; i <= n - 1; i++) 
		if (y[i + 1] >= y[i] + h) area += 0.5 * d * h;
		else area += 0.5 * (d + (((double)d) / h) * (y[i] + h - y[i + 1])) * (y[i + 1] - y[i]);

	cout << setprecision(24) << area << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}