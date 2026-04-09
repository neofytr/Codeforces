#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	int v;
	vector<int> cnt(n + 1, 0);
	for (int r = 1; r <= n; r++)
		cin >> v, cnt[v]++;

	vector<int> f(n + 1, 0);
	for (int r = 1; r <= n; r++)
		f[cnt[r]]++;

	int res = 0;
	for (int r = n; r >= 1; r--) 
		if (f[r]) res += r, f[r - 1] += f[r] - 1;
	
	cout << res << endl;
}

int32_t main() {
	int q;
	cin >> q;

	while (q--) {
		solve();
	}
	return 0;
}