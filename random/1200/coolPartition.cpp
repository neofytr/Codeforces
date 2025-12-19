#include <bits/stdc++.h>
using namespace std;

#define int long long 

int segments(int l, int r, vector<int> &arr) {
	if (l == r)
		return 1;


}

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	vector<vector<int>> f(n + 1, vector<int>(n + 1));
	for (int r = 1; r <= n; r++) cin >> arr[r], f[arr[r]].push_back(r);

	int cnt = 0, currend = LLONG_MAX;
	for (int r = 1; r <= n; r++) {
		vector<int> &v = f[arr[r]];
		int sz = v.size();

		if (sz == 1) {
			cout << cnt << endl;
			return;
		}

		currend = min(currend, v[sz - 1] - 1);
		if (currend <= r)
			currend = LLONG_MAX, cnt++;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}