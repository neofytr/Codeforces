#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++) str[r] = s[r - 1] - 'a';

	int l = 1, r = k;
	int cost = 0;
	while (l <= r) {
		vector<int> cnt(26, 0);
		int t = 0;
		for (int i = l; i <= n; i += k)
			cnt[str[i]]++, t++;
		if (r != l)
			for (int i = r; i <= n; i += k)
				cnt[str[i]]++, t++;

		int maxi = LLONG_MIN;
		for (int c = 0; c < 26; c++) maxi = max(maxi, cnt[c]);

		cost += (t - maxi);
		l++, r--;
	}

	cout << cost << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}