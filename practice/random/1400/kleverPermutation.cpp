#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	vector<int> p(n + 1);

	int start = 1;
	for (int r = 1; r <= k; r++) {
		int cnt = 0;
		for (int i = r; i <= n; i += k) cnt++;
		if (r & 1)
			for (int i = r; i <= n; i += k) p[i] = start++;
		else {
			start += (cnt - 1);
			for (int i = r; i <= n; i += k) p[i] = start--;
			start += cnt + 1;
		}
	}

	for (int r = 1; r <= n; r++)
		cout << p[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}