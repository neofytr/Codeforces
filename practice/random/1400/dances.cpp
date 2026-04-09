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

	int i = 1, l1 = n;
	int j = 1, l2 = n;

	sort(a.begin() + 1, a.end());
	sort(b.begin() + 1, b.end());

	int cnt = 0;
	while (i <= l1 && j <= l2) {
		while (i <= l1 && j <= l2 && a[i] >= b[j]) j++, l1--, cnt++;
		if (i <= l1 && j <= l2 && a[i] < b[j]) i++, j++;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}