#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<pair<int, int>> vec(n + 1);
	for (int j = 1; j <= n; j++) cin >> vec[j].first;
	for (int j = 1; j <= n; j++) cin >> vec[j].second;

	unordered_map<int, int> f;
	for (int j = 1; j <= n; j++) {
		int x = vec[j].first, r = vec[j].second;
		for (int i = x - r; i <= x + r; i++) {
			long long val = 1LL*r*r - 1LL*(x - i)*(x - i);
			int y = sqrt((long double)val);
			while ((long long)(y + 1) * (y + 1) <= val) y++;
			while ((long long)y * y > val) y--;
			f[i] = max(f[i], y);
		}
	}

	unordered_map<int, bool> done;
	int cnt = 0;
	for (int j = 1; j <= n; j++) { 
		int x = vec[j].first, r = vec[j].second;
		for (int i = x - r; i <= x + r; i++) {
			if (!done[i]) {
				int y = f[i];
				cnt += 2 * y + 1;
				done[i] = true;
			}
		}
	}
	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}