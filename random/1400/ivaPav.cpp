#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<vector<int>> p(n + 2, vector<int>(32, 0));
	for (int r = n; r >= 1; r--) 
		for (int bit = 0; bit < 32; bit++)
			p[r][bit] += p[r + 1][bit] + (bool)((1ll << bit) & arr[r]);

	int q;
	cin >> q;

	int l, k;
	while (q--) {
		cin >> l >> k;

		int leadingOne = -1;
		for (int bit = 31; bit >= 0; bit--)
			if (k & (1ll << bit)) {
				leadingOne = bit;
				break;s
			}

		if (leadingOne == -1) {
			cout << n << endl;
			continue;
		}

		beforeZero = 0;
		for (int bit = 31; bit > leadingOne; bit--)
			beforeZero = max(beforeZero, p[l][bit]);

		int one = 0, zero = 0;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}