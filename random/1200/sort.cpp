#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, q;
	cin >> n >> q;

	string a, b;
	cin >> a >> b;

	vector<vector<int>> pa(n + 1, vector<int>(26, 0)), pb(n + 1, vector<int>(26, 0));
	for (int r = 1; r <= n; r++) 
		for (int c = 0; c < 26; c++) {
			pa[r][c] = pa[r - 1][c] + (a[r - 1] == c + 'a' ? 1 : 0);
			pb[r][c] = pb[r - 1][c] + (b[r - 1] == c + 'a' ? 1 : 0);
		}

	int l, r;
	while (q--) {
		cin >> l >> r, l--, r--;
		int cnt = 0;
		for (int c = 0; c < 26; c++) {
			int c1 = pb[r + 1][c] - pb[l][c], c2 = pa[r + 1][c] - pa[l][c];
			cnt += max(0ll, c1 - c2);
		}
		cout << cnt << endl;
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