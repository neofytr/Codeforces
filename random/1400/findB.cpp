#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, q; 
	cin >> n >> q;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> ones(n + 1, 0), p(n + 1, 0);
	for (int r = 1; r <= n; r++) {
		ones[r] = ones[r - 1] + (arr[r] == 1);
		p[r] = p[r - 1] + arr[r];
	}

	int l, r;
	while (q--) {
		cin >> l >> r;
		if (r - l == 0) {
			cout << "NO\n";
			continue;
		}

		int o = ones[r] - ones[l - 1];
		int s = (p[r] - p[l - 1]) - o;
		s -= (r - l + 1 - o);

		if (o > s) {
			cout << "NO\n";
			continue;
		}

		s += (r - l + 1 - o);
		int len = r - l + 1 - o;

		if (s == 2 * len && len < o) {
			cout << "NO" << endl;
			continue;
		}

		cout << "YES" << endl;
	}
}

int32_t main() {
	int t; 
	cin >> t;
	while (t--) solve();
	return 0;
}