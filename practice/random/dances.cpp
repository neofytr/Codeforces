#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	int val;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 2; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> val, b[r] = val;

	a[1] = 1;

	sort(a.begin() + 1, a.end());
	sort(b.begin() + 1, b.end());
	
	int r = 1;
	for (int l = 1; l <= n; l++) {
		while (r <= n && b[r] <= a[l])
			r++;

		if (r > n) {
			cout << n - l + 1 << endl;
			return;
		}
		
		r++;
	}

	cout << 0 << endl;
}	

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}