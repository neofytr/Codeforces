#include <bits/stdc++.h>
using namespace std;

#define int long long 
int f[16];
vector<pair<int, int>> sums;

void solve() {
	int n;
	cin >> n;

	int mini = LLONG_MAX;
	for (auto &[sum, cnt] : sums) 
		if (sum <= n) 
			mini = min(mini, cnt + __builtin_popcountll(n - sum));
		
	cout << mini << endl;
}

int32_t main() {
	int t;
	cin >> t;

	f[0] = 1;
	for (int r = 1; r <= 15; r++)
		f[r] = r * f[r - 1];

	for (int subset = 0; subset < (1ll << 15); subset++) {
		int sum = 0, cnt = 0;
		for (int bit = 0; bit < 15; bit++)
			if (subset & (1ll << bit))
				sum += f[bit + 1], cnt++;
		sums.push_back({sum, cnt});
	}

	while(t--) {
		solve();
	}
	return 0;
}