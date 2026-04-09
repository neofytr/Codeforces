#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(n + 1), f(n + m + 1, 0), in(n + m + 1, LLONG_MAX);
	for (int i = 1; i <= n; i++) 
		cin >> a[i], f[a[i]] = 1, in[a[i]] = 0;
	int s = n;
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int p, v; cin >> p >> v;

		f[a[p]] += max(0ll, (i - in[a[p]] - 1));
		s += (-f[a[p]] + f[v]);

		cnt += 2 * i * n - s;
		s += n;

		f[v]++, in[v] = i;
		a[p] = v;
	}
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}