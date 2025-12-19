#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int cnt = 0;
	if (n & 1) {
		for (int r = 1; r <= n; r++)
			if (!(r & 1)) {
				int t = arr[r - 1] + arr[r + 1];
				if (arr[r] >= t)
					continue;

				int d = t - arr[r];
				arr[r + 1] = max(0ll, arr[r + 1] - d);
				cnt += d;
			}
	} else {
		for (int r = 1; r <= n; r++)
			if (r == n && arr[r] < arr[r - 1])
				cnt += (arr[r - 1] - arr[r]);
			else if (r != n && !(r & 1)) {
				int t = arr[r - 1] + arr[r + 1];
				if (arr[r] >= t)
					continue;

				int d = t - arr[r];
				arr[r + 1] = max(0ll, arr[r + 1] - d);
				cnt += d;
			}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}