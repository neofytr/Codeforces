#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	cout << 2 * n - 3 << endl;
	int r = 2;
	for (int i = 2; i <= n; i++)
		cout << i << " " << 1 << " " << r++ << endl;

	int i = 1;
	for (int l = 2; l <= n - 1; l++)
		cout << i++ << " " << l << " " << n << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}