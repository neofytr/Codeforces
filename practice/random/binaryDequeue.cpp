#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, s; cin >> n >> s;
	vector<int> a(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	int sum = 0;
	int j = 1;
	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++) {
		sum += a[i];
		while (j <= i && sum > s)
			sum -= a[j], j++;
		if (j <= i && sum == s)
			maxi = max(maxi, i - j + 1);
	}

	cout << (maxi == LLONG_MIN ? -1 : n - maxi) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}