#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	string s; cin >> s;
	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++) str[r] = s[r - 1] - '0';

	vector<int> pzero(n + 1, 0), pone(n + 1, 0);
	for (int r = 1; r <= n; r++) {
		pzero[r] = pzero[r - 1] ^ (!str[r] ? arr[r] : 0);
		pone[r] = pone[r - 1] ^ (str[r] ? arr[r] : 0);
	}

	int one = pone[n], zero = pzero[n];
	int q; cin >> q;
	while (q--) {
		int t; cin >> t;

		if (t == 1) {
			int l, r; cin >> l >> r;
			zero ^= (pzero[r] ^ pzero[l - 1]) ^ (pone[r] ^ pone[l - 1]);
			one ^= (pzero[r] ^ pzero[l - 1]) ^ (pone[r] ^ pone[l - 1]);
		} else {
			int g; cin >> g;
			if (!g) cout << zero << " ";
			else cout << one << " ";
		}
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}