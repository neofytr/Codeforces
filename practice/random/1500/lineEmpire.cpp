#include <bits/stdc++.h>
using namespace std;

#define int long long
void solve() {
	int n, a, b; cin >> n >> a >> b;
	vector<int> x(n + 1, 0), p(n + 1, 0);
	for (int r = 1; r <= n; r++) cin >> x[r], p[r] += p[r - 1] + x[r];

	int mini = LLONG_MAX;
	for (int r = 1; r <= n; r++)
		mini = min(mini, a * x[n - 1] - b * (p[n - 1] - p[r - 1]));
	cout << mini + b * p[n] << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}