#include <bits/stdc++.h>
using namespace std;

#define int int32_t

void solve() {
	int n; cin >> n;

	vector<int> p(n + 1, 0), arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r], p[r] += p[r - 1] + arr[r];

	vector<bool> there(p[n] + 1, false);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			there[p[j] - p[i - 1]] = true;

	int cnt = 0;
	for (int r = 1; r <= n; r++) 
		if (there[arr[r]]) cnt++;
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}