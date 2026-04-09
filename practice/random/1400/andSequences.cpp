#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (int)(1e9 + 7)
#define MAX (int)(2 * 1e5)

int f[MAX + 1];
void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	set<int> mid;
	vector<vector<int>> bit(31);

	for (int b = 0; b <= 30; b++)
		for (int r = 1; r <= n; r++)
			if (arr[r] & (1ll << b))
				bit[b].push_back(r);

	for (int b = 0; b <= 30; b++) {
		if (bit[b].empty() || bit[b].size() == n)
			continue;

		for (auto r : bit[b])
			mid.insert(r);
	}

	if (mid.size() > n - 2) {
		cout << 0 << endl;
		return;
	}

	int sz = mid.size();
	cout << f[n - 2] * (n - sz) % MOD * (n - sz - 1) % MOD << endl;
}

int32_t main() {
	int t;
	cin >> t;

	f[0] = 1;
	for (int r = 1; r <= MAX; r++)
		f[r] = (r * f[r - 1]) % MOD;

	while (t--) {
		solve();
	}
	return 0;
}