#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, d; cin >> n >> d;
	vector<pair<int, int>> f(n + 1);
	for (int i = 1; i <= n; i++) cin >> f[i].first >> f[i].second;

	sort(f.begin() + 1, f.end());
	vector<int> p(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		auto [m, s] = f[i];
		p[i] = p[i - 1] + s;
	}

	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++) {
		auto [m, s] = f[i];
		int j = lower_bound(f.begin() + 1, f.end(), make_pair(m - d + 1, 0ll)) - f.begin();
		maxi = max(maxi, p[i] - p[j - 1]);
	}

	cout << maxi << endl;
	return 0;
}