#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) p[i] = p[i - 1] + a[i];

	unordered_map<int, vector<int>> f;
	f[0].push_back(0);
	for (int i = 1; i <= n; i++) f[p[i]].push_back(i);
	
	int cnt = 0, i = 1, mini = LLONG_MAX;
	while (i <= n) {
		int target = p[i - 1];
		if (!f[target].empty()) {
			auto itr = lower_bound(f[target].begin(), f[target].end(), i);
			if (itr != f[target].end())
				mini = min(mini, *itr);
		}

		if (i == mini - 1) {
			mini = LLONG_MAX;
			cnt++;
		}
		i++;
	}

	cout << cnt << endl;
	return 0;
}