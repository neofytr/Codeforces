#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, d, k; cin >> n >> d >> k;

	vector<pair<int, int>> jobs(k);
	for (int r = 0; r < k; r++) 
		cin >> jobs[r].first >> jobs[r].second;

	vector<int> left(n + 1, 0), right(n + 1);
	for (auto &[l, r] : jobs) left[l]++, right[r]++;

	int cnt = 0;
	for (auto &[l, r] : jobs)
		if (l <= d) cnt++;	

	int m = cnt, idx = 1;
	cout << d << " " << cnt << endl;
	for (int r = d + 1; r <= n; r++) {
		cnt += left[r];
		cnt -= right[r - d];
		cout << r << " " << cnt << endl;
		if (cnt > m)
			m = cnt, idx = r;
	}
	
	cout << idx << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}