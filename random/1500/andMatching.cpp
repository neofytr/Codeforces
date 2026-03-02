#include <bits/stdc++.h>
using namespace std;

#define int long long

int inv(int i) {
	int r = 63 - __builtin_clzll(i);
	int x = 0;
	for (int bit = 0; bit <= r; bit++)
		if (i & (1ll << bit)) x &= ~(1ll << bit);
		else x |= (1ll << bit);
	return x;
}

void solve() {
	int n, k; cin >> n >> k;
	if (k == n - 1) {
		if (n <= 5) {
			cout << -1 << endl;
			return;
		}

		cout << n - 1 << " " << n - 2 << endl;
		cout << 1 << " " << 3 << endl;
		vector<bool> done(n + 1, false);	
		done[n - 1] = done[n - 2] = done[1] = done[3] = true;
		for (int r = n - 3; r >= 1; r--)
			if (!done[r]) {
				done[r] = true;
				if (done[inv(r)]) {
					cout << r << " " << 0 << endl;
					continue;
				}
				done[inv(r)] = true;
				cout << r << " " << inv(r) << endl;
			}
		return;
	}

	vector<bool> done(n + 1, false);
	cout << n - 1 << " " << k << endl;

	done[n - 1] = done[k] = true;
	for (int r = n - 1; r >= 1; r--)
		if (!done[r]) {
			done[r] = true;
			if (done[inv(r)]) {
				cout << r << " " << 0 << endl;
				continue;
			}
			done[inv(r)] = true;
			cout << r << " " << inv(r) << endl;
		}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}