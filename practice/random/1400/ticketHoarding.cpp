#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m, k; cin >> n >> m >> k;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int cnt = 0;
	int left = k;
	int last;
	sort(arr.begin() + 1, arr.end());
	for (int r = 1; r <= n; r++) {
		if (left >= m) left -= m, cnt += (arr[r] - m) * (arr[r] - m);
		else cnt += (arr[r] - left) * (arr[r] - left), left = 0;

		if (!left) {
			last = r;
			break;
		}
	}
	
	int sum = 0;
	for (int r = 1; r <= last; r++)
		sum += arr[r] * arr[r];

	cout << (k * k + sum - cnt) / 2 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}