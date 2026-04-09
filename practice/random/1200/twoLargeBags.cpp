#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	int val;
	vector<int> f(n + 2, 0);
	for (int r = 1; r <= n; r++)
		cin >> val, f[val]++;

	for (int r = 1; r <= n; r++)
		if (f[r] == 1) {
			cout << "NO\n";
			return;
		} else if (f[r] >= 2) 
			f[r] -= 2, f[r + 1] += f[r];

	cout << "YES\n";
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}