#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	if (n < 7) {
		cout << "NO" << endl;
		return;
	}

	int k = 2;
	while (k * k * k <= n * (k - 1) + 1) {
		int d = k * k * k, num = n * (k - 1) + 1;
		if (num % d) {
			k++;
			continue;
		}

		int w = num / d;
		while (w > 1 && !(w % k)) w /= k;
		if (w == 1) {
			cout << "YES" << endl;
			return;
		}

		k++;
	}

	cout << "NO" << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}