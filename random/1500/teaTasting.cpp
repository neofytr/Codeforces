#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	vector<int> mult(n + 1, 0), p(n + 1, 0), left(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + b[r];

	for (int r = 1; r <= n; r++)
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}