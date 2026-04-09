#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1), p(n + 1, 0);
	for (int r = 1; r <= n; r++) cin >> arr[r], p[r] = p[r - 1] ^ arr[r];

	if (!p[n]) {
		cout << "YES" << endl;
		return;
	}

	for (int i = 1; i <= n - 2; i++) {
		int x = p[i];
		if (!(p[n] ^ p[i]))
			for (int j = i + 1; j <= n; j++)
				if (!p[j]) {
					cout << "YES" << endl;
					return;
				}
	}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}