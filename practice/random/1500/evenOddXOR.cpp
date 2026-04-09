#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);

	if (n == 3) {
		cout << 2 << " " << 1 << " " << 3 << endl;
		return;
	}

	int f = n;
	if (n & 1) {
		a[n] = 0;
		n--;
	}

	int x = 0;
	for (int bit = 24; bit >= 0; bit--)
		x |= (1ll << bit);

	if ((n / 2) & 1) {
		int i = 5, j = 6;
		int k = 1; 
		while (i + 2 <= n && j + 2 <= n) {
			a[i] = k, a[i + 2] = k + 1;
			a[j] = k, a[j + 2] = k + 1;

			for (int bit = 25; bit >= 19; bit--)
				a[j] |= (1ll << bit);
			for (int bit = 25; bit >= 19; bit--)
				a[j + 2] |= (1ll << bit);
			i += 4, j += 4, k += 2;
		}

		a[1] = (1ll << 29), a[3] = (1ll << 28);
		a[2] = (1ll << 27), a[4] = (1ll << 26);
		a[n - 1] = a[1] ^ a[3] ^ (1ll << 30);
		a[n] = a[2] ^ a[4] ^ (1ll << 30);

		for (int m = 1; m <= n; m++)
			cout << a[m] << " ";
		if (f != n)
			cout << a[f] << " ";
		cout << endl;
	} else {
		int i = 1, j = 2;
		int k = 1;
		while (i + 2 <= n && j + 2 <= n) {
			a[i] = k, a[i + 2] = k + 1;
			a[j] = k, a[j + 2] = k + 1;

			for (int bit = 25; bit >= 19; bit--)
				a[j] |= (1ll << bit);
			for (int bit = 25; bit >= 19; bit--)
				a[j + 2] |= (1ll << bit);
			i += 4, j += 4, k += 2;
		}	

		for (int m = 1; m <= n; m++)
			cout << a[m] << " ";
		if (f != n)
			cout << a[f] << " ";
		cout << endl;
	}

	int odd = 0, even = 0;
	set<int> s;
	for (int i = 1; i <= f; i++) {
		if (i & 1) odd ^= a[i];
		else even ^= a[i];
		s.insert(a[i]);
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}