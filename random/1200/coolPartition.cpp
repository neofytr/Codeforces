#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	unordered_map<int, vector<int>> f;
	for (int r = 1; r <= n; r++) cin >> arr[r], f[arr[r]].push_back(r);

	int cnt = 0, last = n;
	while (last >= 1) {
		int mini = LLONG_MAX;
		for (auto &[e, v] : f)
			if (!v.empty()) {
				auto itr = upper_bound(v.begin(), v.end(), last);
				if (itr != v.begin()) 
					--itr, mini = min(mini, *itr);
			}
		last = mini - 1;
		cnt++;
	}

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