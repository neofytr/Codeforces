#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	cin >> n >> m;

	vector<char> comm(n + 1);
	for (int r = 1; r <= n; r++) cin >> comm[r];

	vector<int> v(m + 1);
	for (int r = 1; r <= m; r++)
		cin >> v[r];

	int l = 1, r = 1;
	while (l <= r) {
		r = l;
		int k = 0;
		while (v[r] == v[l] + k)
			k++, r++;

		// [l, r - 1]
	}

	int curr = 1;
	for (int r = 1; r <= n; r++)
		if (comm[r] == 'A') black.insert(++curr);
		else {

		}

	cout << black.size() << endl;
	for (int b : black)
		cout << b << " ";
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