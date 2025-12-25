#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> f(64, 0);
	for (int b = 0; b <= 63; b++)
		for (int r = 1; r <= n; r++)
			if (arr[r] & (1ll << b)) f[b]++;

	int m = n - f[0];
	f[0] += min(m, k);
	k -= min(k, m);

	for (int b = 1; b <= 63; b++) {
		int more = (n - f[b]) * (1ll << (b - 1));
		if (k >= more)
			f[b] = n, k -= more;
		else {
			cout << b << endl;
			cout << k << " " << more << endl;
			break;
		}
	}

	int cnt = 0;
	for (int b = 0; b <= 63; b++)
		cout << "f[" << b << "] = " << f[b] << endl;
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}