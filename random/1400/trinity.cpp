#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int cnt = 0;
	sort(arr.begin() + 1, arr.end());
	int a = arr[1], b = arr[2];
	for (int r = n; r >= 3; r--)
		if (arr[r] >= a + b) arr[r] = b, cnt++;
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}