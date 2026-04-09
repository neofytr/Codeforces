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

	int sz = vec.size() - 1;
	int mini = LLONG_MAX;
	sort(vec.begin() + 1, vec.end());
	vector<int> p(sz + 1, 0);
	for (int r = 1; r <= sz; r++) p[r] = p[r - 1] + vec[r];
	for (int c = 0; c <= maxi + 1; c++) {
		int k = 0;
		int i = lower_bound(vec.begin() + 1, vec.end(), c) - vec.begin();
		if (i <= sz) 
			k += (p[sz] - p[i - 1]) - c * (sz - i + 1);
		i--;
		k += p[i];

		mini = min(mini, k);
	}

	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}