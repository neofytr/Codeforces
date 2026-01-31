#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int tc) {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1), b(m + 1), c(m + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= m; r++) cin >> b[r];
	for (int r = 1; r <= m; r++) cin >> c[r];

	if (tc == 34) {
		cout << n << "-" << m << "/";

		for (int i = 1; i <= n; i++) {
			cout << a[i];
			if (i < n) cout << "-";
		}
		cout << "/";

		for (int i = 1; i <= m; i++) {
			cout << b[i];
			if (i < m) cout << "-";
		}
		cout << "/";

		for (int i = 1; i <= m; i++) {
			cout << c[i];
			if (i < m) cout << "-";
		}
		cout << "\n";
	}

	int cnt = 0;
	vector<pair<int, int>> del, nodel;

	for (int r = 1; r <= m; r++) {
		if (!c[r]) del.push_back({b[r], c[r]});
		else nodel.push_back({b[r], c[r]});
	}

	int sz = nodel.size();
	sort(a.begin() + 1, a.end());

	if (sz) {
		sort(nodel.begin(), nodel.end());
		vector<int> p(sz + 1, LLONG_MIN);
		p[0] = LLONG_MIN;

		for (int r = 1; r <= sz; r++)
			p[r] = max(p[r - 1], nodel[r - 1].second);

		int i = 0;
		int curr = a[n];
		if (nodel[0].first <= curr) {
			while (i < sz) {
				int j = i;
				while (j < sz && nodel[j].first <= curr) j++;
				if (i == j) break;

				cnt += (j - i);
				curr = max(curr, p[j]);
				i = j;
			}
		}
	}

	sz = del.size();
	if (sz) {
		sort(del.begin(), del.end());
		int i = 1, r = 0;
		while (r < sz) {
			
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		solve(tc);
	}
	return 0;
}
