#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	unordered_map<int, int> f;

	int v;
	for (int r = 1; r <= n; r++) cin >> v, f[v]++;

	int maxi = LLONG_MIN;
	vector<int> vec(1);
	for (auto &[e, c] : f) maxi = max(maxi, c), vec.push_back(c);

	int sz = v.size() - 1;
	int mini = LLONG_MAX;
	sort(vec.begin() + 1, vec.end());
	for (int c = 0; c <= maxi + 1; c++) {
		int i = lower_bound(vec.begin() + 1, vec.end(), c) - vec.begin();
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}