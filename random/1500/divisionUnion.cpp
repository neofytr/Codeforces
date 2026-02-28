#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> l(n + 1), r(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> l[i].first >> r[i].first;
		l[i].second = i, r[i].second = i;
	}

	sort(l.begin() + 1, l.end()), sort(r.begin() + 1, r.end());
	vector<int> g(n + 1, -1);
	for (int i = 1; i <= n; i++) {
		int x = r[i].first;
		int j = lower_bound(l.begin() + 1, l.end(), make_pair(x + 1, 0ll)) - l.begin();
		if ((n >= j) && (j - i == 1)) {
			for (int k = 1; k <= i; k++)
				g[r[k].second] = 1;
			for (int k = j; k <= n; k++)
				g[l[k].second] = 2;
			break;
		}
	}

	if (g[1] == -1) {
		cout << "-1" << endl;
		return;
	}

	for (int i = 1; i <= n; i++)
		cout << g[i] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}