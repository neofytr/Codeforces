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
	for (int bit = 30; bit >= 0; bit--)
		x |= (1ll << bit);

	if ((n / 2) & 1) {
		int i = 5, j = 6;
		int k = 1; 
		while (i + 2 <= n && j + 2 <= n) {
			a[i] = k, a[i + 2] = k + 1;
			a[j] = k, a[j + 2] = k + 1;

			int m;
			for (int bit = 30; bit >= 0; bit--)
				if (a[j] & (1ll << bit)) {
				 	m = bit;
				 	break;
				}

			for (int bit = 30; bit >= 0; bit--)
				if (a[j + 2] & (1ll << bit)) {
				 	m = max(m, bit);
				 	break;
				}


			for (int bit = 30; bit >= m + 1; bit--)
				a[j] |= (1ll << bit);
			for (int bit = 30; bit >= m + 1; bit--)
				a[j + 2] |= (1ll << bit);
			i += 4, j += 4, k += 3;
		}

		a[1] = f + 1, a[3] = f + 2;
		a[2] = f + 3, a[4] = f + 4;
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

			int m;
			for (int bit = 30; bit >= 0; bit--)
				if (a[j] & (1ll << bit)) {
				 	m = bit;
				 	break;
				}

			for (int bit = 30; bit >= 0; bit--)
				if (a[j + 2] & (1ll << bit)) {
				 	m = max(m, bit);
				 	break;
				}

			cout << m << endl;
			for (int bit = 30; bit >= m + 1; bit--)
				a[j] |= (1ll << bit);
			for (int bit = 30; bit >= m + 1; bit--)
				a[j + 2] |= (1ll << bit);
			i += 4, j += 4, k += 3;
		}	

		for (int m = 1; m <= n; m++)
			cout << a[m] << " ";
		if (f != n)
			cout << a[f] << " ";
		cout << endl;
	}

	int even = 0, odd = 0;
	for (int i = 1; i <= f; i += 2)
		odd ^= a[i];
	for (int i = 2; i <= f; i += 2)
		even ^= a[i];

	cout << (a[1] ^ a[3]) << " " << (a[2] ^ a[4]) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}