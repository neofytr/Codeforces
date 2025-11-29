#include <bits/stdc++.h>
using namespace std;

#define int long long

// 1 0 1 0 1 1 0 1 0 1
// 1 0 1 0 1 0 0 0 0 0 
// 0 0 0 0 0 1 0 1 0 1

void solve() {
	int n;
	cin >> n;

	if (!n) {
		cout << "YES" << endl;
		return;
	}

	int f;
	for (int bit = 29; bit >= 0; bit--)
		if (n & (1LL << bit)) {
			f = bit;
			break;
		}

	for (int first = 62; first >= f; first--) {
		if (first & 1) {
			bool done = true;
		for (int bit = 0; bit <= first / 2; bit++) {
			int x = bit, y = first - bit;
			int i = ((n & (1ll << x)) ? 1 : 0);
			int j = ((n & (1ll << y)) ? 1 : 0);
			if (i != j) {
				done = false;
			}
		}
		if (done) {
			cout << "YES\n";
			return;
		}
	} else {
		bool done = true;
		for (int bit = 0; bit < first / 2; bit++) {
			int x = bit, y = first - bit;
			int i = ((n & (1ll << x)) ? 1 : 0);
			int j = ((n & (1ll << y)) ? 1 : 0);
			if (i != j) {
				done = false;
			}
		}

		if (n & (1ll << (first / 2))) {
			done = false;
		}
		if (done) {
			cout << "YES\n";
			return;
		}
	}
	}
	
	cout << "NO\n";
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}