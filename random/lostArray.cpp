#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1, INT_MAX);
	vector<vector<int>> bitarr(32, vector<int>(n + 2, 0));
	vector<pair<int, pair<int, int>>> b;

	while(m--) {
		int l, r, orval;
		cin >> l >> r >> orval;
		for (int bit = 0; bit <= 31; bit++)
			if (orval & (1LL << bit))
				b.push_back({bit, {l, r}});
			else
				bitarr[bit][l] += 1, bitarr[bit][r + 1] -= 1;
	}


	for (int bit = 0; bit <= 31; bit++) {
		for (int r = 1; r <= n; r++) {
			bitarr[bit][r] += bitarr[bit][r - 1];
			if (bitarr[bit][r])
				arr[r] &= ~(1LL << bit);
		}
	}

	for (int bit = 0; bit <= 31; bit++)
		for (int r = 0; r <= n + 1; r++)
			bitarr[bit][r] = 0;

	for (int r = 1; r <= n; r++)
		for (int bit = 0; bit <= 31; bit++)
			bitarr[bit][r] += bitarr[bit][r - 1] + ((arr[r] & (1LL << bit)) ? 1 : 0);

	for (auto [bit, idx] : b) {
		int l = idx.first, r = idx.second;
		int x = bitarr[bit][r] - bitarr[bit][l - 1];
		if (!x) {
			cout << -1 << endl;
			return;
		}		
	}

	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}