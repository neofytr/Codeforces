#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int tc) {
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];
	sort(arr.begin() + 1, arr.end());

	int cnt = 0;
	bool lastright = false;

	for (int r = 1; r <= n - 1; r++) {
		int after = n - (r + 1);
		int left = r - after;
		int c1 = LLONG_MAX;
		if (left >= 1)
			c1 = left - 1;

		int before = r - 1;
		int right = (r + 1) + before;
		int c2 = LLONG_MAX;
		if (right <= n)
			c2 = n - right;
		if (min(c1, c2) <= k) {
			cnt += (arr[r + 1] - arr[r]);
			if (!lastright) cnt++;
			lastright = true;
		} else if ((n & 1) && r == (n + 1) / 2) cnt++, lastright = true;
		else lastright = false;
	}
	if (!lastright && n - 1 <= k) cnt++;
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int r = 1; r <= t; r++) solve(r);
	return 0;
}