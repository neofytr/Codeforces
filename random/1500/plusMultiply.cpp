#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e9)

void solve() {
	int n, a, b;
	cin >> n >> a >> b;

	if (b == 1) {
		cout << "YES" << endl;
		return;
	}

	if (a == 1) {
		if (!((n - 1) % b)) cout << "YES" << endl;
		else cout << "NO" << endl;
		return;
	}

	int p = 1;
	while (p <= n) {
		if (!((n - p) % b)) {
			cout << "YES" << endl;
			return;
		}
		p = p * a;
	}

	cout << "NO" << endl;
}
int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}