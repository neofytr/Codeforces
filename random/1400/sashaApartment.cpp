#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
	int cnt = 0;
	bool lastright = false;
	if (!(n & 1)) {
		for (int r = 1; r <= n / 2; r++) {
			int before = r - 1;
			int right = r + 1 + before;
			int toremove = n - right;
			if (toremove <= k) {
				cnt += (arr[r + 1] - arr[r]);
				if (!lastright) cnt++;
				lastright = true;
			} else lastright = false;
		}

		for (int r = n / 2 + 1; r <= n - 1; r++) {
			int after = n - r - 1;
			int left = r - after;
			if (left - 1 <= k) {
				cnt += (arr[r + 1] - arr[r]);
				if (!lastright) cnt++;
				lastright = true;
			} else lastright = false;
		}

		if (!lastright && n - 1 <= k)
			cnt++;
	}
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}