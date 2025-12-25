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

	for (int b = 0; b <= 63; b++) {
		int more = (n - f[b]) * (1ll << (b));
		if (k >= more)
			f[b] += (n - f[b]), k -= more;
		else {
			for (int r = 1; r <= (n - f[b]); r++)  {
				int req = r * (1ll << (b));
				if (req <= k)
					continue;

				f[b] += (r - 1);
				break;
			}
			break;
		}
	}

	int cnt = 0;
	for (int b = 0; b <= 63; b++)
		cnt += f[b];
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