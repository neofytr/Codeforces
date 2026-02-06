#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	int cnt = 0;
	vector<pair<int, int>> ops;
	for (int r = 1; r <= n; r++)
		if (a[r] == b[r]) cnt++;

	if (!(n & 1) && cnt) {
		cout << -1 << endl;
		return;
	}

	if ((n & 1) && cnt >= 2) {
		cout << -1 << endl;
		return;
	}

	for (int r = 1; r <= n; r++)
		if (a[r] == b[r]) {
			if ((n & 1) && r == n / 2 + 1)
				continue;
			swap(a[r], a[n / 2 + 1]);
			swap(b[r], b[n / 2 + 1]);
			ops.push_back({r, n / 2 + 1});
			break;
		}

	vector<int> idx(n + 1);
	for (int r = 1; r <= n; r++)
		idx[b[r]] = r;
	for (int r = 1; r <= n; r++)
		if (a[r] != b[n - r + 1]) {
			int i = idx[a[r]];
			swap(a[i], a[n - r + 1]);

			idx[b[i]] = n - r + 1;
			idx[b[n - r + 1]] = i;
			swap(b[i], b[n - r + 1]);
			ops.push_back({i, n - r + 1});
		}
	
	for (int r = 1; r<= n; r++)
		if (a[r] != b[n - r + 1]) {
			cout << -1 << "\n";
			return;
		}

	cout << ops.size() << endl;
	for (auto [i, j] : ops)
		cout << i << " " << j << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}