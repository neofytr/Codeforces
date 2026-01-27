#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int sm = 0;
	for (int r = 1; r <= m; r++)
		sm += arr[r];

	int cnt = 0;
	int s = 0;
	int mini = LLONG_MAX;
	for (int r = 1; r <= m - 1; r++) {
		s += arr[r];
		mini = min(s, mini);
	}

	multiset<int> ms;
	for (int r = 1; r <= m; r++)
		ms.insert(arr[r]);

	for (auto itr = ms.rbegin(); itr != ms.rend(); ++itr)
		if (sm > mini) cnt++, sm += -2 * (*itr);

	cout << cnt << endl;	
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}