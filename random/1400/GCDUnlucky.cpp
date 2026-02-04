#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> p(n + 1, 0), s(n + 2, 0);
	for (int r = 1; r <= n; r++) cin >> p[r];
	for (int r = 1; r <= n; r++) cin >> s[r];

	if (p[n] != s[1]) {
		cout << "NO" << endl;
		return;
	}

	int g = p[n];
	for (int r = 1; r <= n - 1; r++)
		if (p[r] % p[r + 1]) {
			cout << "NO" << endl;
			return;
		}

	for (int r = 1; r <= n - 1; r++)
		if (s[r + 1] % s[r]) {
			cout << "NO" << endl;
			return;
		}
	
	for (int r = 0; r <= n; r++)
		if (gcd(p[r], s[r + 1]) != g) {
			cout << "NO" << endl;
			return;
		}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}