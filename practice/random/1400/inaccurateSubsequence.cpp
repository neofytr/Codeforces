#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m, k; cin >> n >> m >> k;
	vector<int> arr(n + 1);
	unordered_map<int, int> bcnt;
	int v;
	for (int r = 1; r <= n; r++) cin >> arr[r];
	for (int r = 1; r <= m; r++) cin >> v, bcnt[v]++;

	int c = 0;
	unordered_map<int, int> scnt; 
	int cnt = 0;
	int l = 1;
	for (int r = 1; r <= n; r++) {
		scnt[arr[r]]++;
		if (scnt[arr[r]] <= bcnt[arr[r]]) c++;

		while (l <= r && c >= k) {
			if (scnt[arr[l]] <= bcnt[arr[l]]) c--;
			scnt[arr[l]]--;
			l++;
		}

		// [l - 1, r] is the smallest segment ending at r satisfying the
		// property
		if (l >= 2 && r >= m && (r - l + 2) <= m) {
			cnt++;
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}