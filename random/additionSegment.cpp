#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];

	sort(b.begin() + 1, b.end());
	vector<int> p(n + 1);
	for (int r = 1; r <= n; r++)
		p[r] += p[r - 1] + b[r];

	int s = 0;
	for (int r = 1; r <= n; r++) {
		if (!b[r]) continue;
		if (s + (p[n] - p[r - 1]) - (n - r + 1) >= n - 1) {
			cout << n - r + 1 << endl;
			return;
		}

		s += b[r];
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}