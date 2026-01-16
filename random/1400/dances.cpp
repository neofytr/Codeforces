#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1), b(n + 1);
	a[1] = 1;

	for (int i = 2; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	int i = 1, j = 1;
	int cnt = 0;
	while (i <= n) {
		int k = j;

		while (k <= n && a[k] >= b[j]) cnt++, k++, n--;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}