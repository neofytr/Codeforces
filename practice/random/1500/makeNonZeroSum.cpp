#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	int S = 0;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) 
		cin >> a[i], S += a[i];

	if (!S) {
		cout << n << endl;
		for (int i = 1; i <= n; i++)
			cout << i << " " << i << endl;
		return; 
	}

	vector<pair<int, int>> segs;
	vector<int> sign(n + 1, 0); // 0 means plus, 1 means minus
	if (S > 0) {
		// 1 to -1
		if (S & 1) {
			cout << -1 << endl;
			return;
		}

		int cnt = 0;
		int i = 1;
		bool done = false;
		while (i <= n && !done) {
			if (a[i] != 1 || i == 1) {
				i++; continue;
			}

			int j = i;
			while (a[j] == 1) j++;
			for (int k = i; k < j; k += 2) {
				sign[k] = 1, cnt++;
				if (cnt == S / 2) {
					done = true;
					break;
				}
			}

			i = j;
			// [i, j - 1] are all ones
		}

		if (cnt < S / 2) {
			cout << -1 << endl;
			return;
		}

		i = 1;
		while (i <= n) {
			int j = i;
			while (j + 1 <= n && sign[j + 1] != sign[j]) j++;
			segs.push_back({i, j});
			i = j + 1;
		}
	} else {
		S *= -1;
		if (S & 1) {
			cout << -1 << endl;
			return;
		}

		int cnt = 0;
		int i = 1;
		bool done = false;
		while (i <= n && !done) {
			if (a[i] != -1 || i == 1) {
				i++; continue;
			}

			int j = i;
			while (a[j] == -1) j++;
			for (int k = i; k < j; k += 2) {
				sign[k] = 1, cnt++;
				if (cnt == S / 2) {
					done = true;
					break;
				}
			}

			i = j;
			// [i, j - 1] are all ones
		}

		if (cnt < S / 2) {
			cout << -1 << endl;
			return;
		}

		i = 1;
		while (i <= n) {
			int j = i;
			while (j + 1 <= n && sign[j + 1] != sign[j]) j++;
			segs.push_back({i, j});
			i = j + 1;
		}
	}

	cout << segs.size() << endl;
	for (auto [l, r] : segs)
		cout << l << " " << r << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}