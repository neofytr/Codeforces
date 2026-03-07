#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, c, d; cin >> n >> c >> d;
	vector<int> a(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];

	sort(a.rbegin(), a.rend() - 1);
	for (int i = 1; i <= n; i++) p[i] += p[i - 1] + a[i];

	int g = -1;
	for (int k = d; k >= 0; k--) {
		int s = min(k + 1, n);
		int res = p[s] * (d / max(s, k + 1)) + p[min(s, d % max(k + 1, s))];
		if (res >= c) {
			g = k;
			break;
		}
	}

	if (g == -1) 
		cout << "Impossible";
	else if (g + 1 >= d) cout << "Infinity";
	else cout << g;
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
} 