#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 2, 0);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<vector<int>> p(n + 2, vector<int>(32, 0));
	for (int r = n; r >= 1; r--) {
	for (int bit = 0; bit < 32; bit++) {
		if (arr[r] & (1LL << bit))
			p[r][bit] = 1 + p[r + 1][bit];
		else
			p[r][bit] = 0;
	}
}


	int q;
	cin >> q;

	int l, k;
	while (q--) {
		cin >> l >> k;

		int leadingOne = -1;
		for (int bit = 31; bit >= 0; bit--)
			if (k & (1ll << bit)) {
				leadingOne = bit;
				break;
			}

		if (leadingOne == -1) {
			cout << n << endl;
			continue;
		}

		int front = 0;
		int one = 0, latestZero = 0;
		for (int bit = 31; bit > leadingOne; bit--)
			front = max(front, p[l][bit]);
		one = p[l][leadingOne];

		for (int bit = leadingOne - 1; bit >= 0; bit--) {
			int j = p[l][bit];
			if (k & (1ll << bit)) 
				if (j < one) one = max(latestZero, j);
			else 
				latestZero = max(latestZero, j), latestZero = min(latestZero, one);
		}

		int final = max({front, one});
		if (!final)
			cout << -1 << " ";
		else 
			cout << l + final - 1 << " ";
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}