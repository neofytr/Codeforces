#include <bits/stdc++.h>
using namespace std;

#define int long long

int fact[15 + 1];
void solve() {
	int n; cin >> n;

	int mini = LLONG_MAX;
	for (int subset = 0; subset < (1ll << 15); subset++) {
		int sum = 0;
		int cnt = 0;
		for (int bit = 0; bit < 15; bit++)
			if (subset & (1ll << bit)) sum += fact[bit + 1], cnt++;

		if (sum <= n) 
			mini = min(mini, __builtin_popcountll(n - sum) + cnt);
	}
	cout << mini << endl;
}

int32_t main() {
	fact[0] = 1;
	for (int r = 1; r <= 15; r++) fact[r] = r * fact[r - 1];
	int t; cin >> t;
	while (t--) solve();
	return 0;
}