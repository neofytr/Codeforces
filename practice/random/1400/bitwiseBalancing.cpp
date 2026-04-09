#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int b, c, d; cin >> b >> c >> d;
	int a = 0;
	for (int bit = 0; bit <= 60; bit++) {
		int bbit = ((b & (1ll << bit)) ? 1 : 0);
		int cbit = ((c & (1ll << bit)) ? 1 : 0);
		int dbit = ((d & (1ll << bit)) ? 1 : 0);

		if (bbit) {
			if (dbit)
				a &= ~(1ll << bit);
			else if (cbit)
				a |= (1ll << bit);
			else {
				cout << -1 << endl;
				return;
			}
		} else {
			if (!dbit) 
				a &= ~(1ll << bit);
			else if (!cbit)
				a |= (1ll << bit);
			else {
				cout << -1 << endl;
				return;
			}
		}
	}
	cout << a << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}