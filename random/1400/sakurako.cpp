#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> p(n + 1), f(n + 1);
	for (int r = 1; r <= n; r++) cin >> p[r], f[p[r]] = r;

	int cnt = 0;
	for (int r = 1; r <= n; r++) {
		int alpha = p[r];
		if (p[alpha] == r) continue;
		int i = f[r];
		f[p[alpha]] = i;
		f[p[i]] = alpha;
		swap(p[alpha], p[i]), cnt++;
	}
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}