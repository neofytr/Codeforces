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

	int maxi = cnt, idxmaxi = 1;
	int mini = cnt, idxmini = 1;
	for (int r = d + 1; r <= n; r++) {
		cnt += left[r];
		cnt -= right[r - d];
		if (cnt > maxi)
			maxi = cnt, idxmaxi = r - d + 1;
		if (cnt < mini)
			mini = cnt, idxmini = r - d + 1;
	}
	
	cout << idxmaxi << " " << idxmini << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}