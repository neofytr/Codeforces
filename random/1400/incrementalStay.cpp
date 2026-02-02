#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;

	vector<int> a(2 * n + 1, 0);
	for (int r = 1; r <= 2 * n; r++) cin >> a[r];

	vector<int> even(2 * n + 1, 0), odd(2 * n + 1, 0), p(2 * n + 1, 0);
	for (int r = 1; r <= 2 * n; r++)
		p[r] += p[r - 1] + a[r];

	odd[1] = a[1];
	for (int r = 3; r <= 2 * n; r += 2)
		odd[r] = odd[r - 2] + a[r];
	even[2] = a[2];
	for (int r = 4; r <= 2 * n; r += 2)
		even[r] = even[r - 2] + a[r];

	for (int k = 1; k <= n; k++) {
		int c = 0;
		c -= (p[k] - p[0]);
		c += (p[2 * n] - p[2 * n - k]);

		if (k + 1 <= 2 * n - k - 1) {
			if ((k + 1) & 1)
				c += (odd[2 * n - k - 1] - odd[k - 1]);
			else 
				c += (even[2 * n - k - 1] - even[k - 1]);
		}

		if (k + 2 <= 2 * n - k) {
			if ((k + 2) & 1)
				c -= odd[2 * n - k] - odd[k];
			else
				c -= even[2 * n - k] - even[k];
		}

		cout << c << " ";
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}