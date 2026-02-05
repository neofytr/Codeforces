#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(m + 1);

	int v;
	for (int r = 1; r <= m; r++) {
		cin >> v;
		int d = 1;
		vector<int> dig(11, -1);
		while(v) {
			dig[d++] = v % 10;
			v /= 10;
		}

		for (int d = 10; d >= 1; d--) {
			if (dig[d] == -1) continue;
			if (d >= 4)
				a[r] = dig[d] * 10 + dig[d - 1];
			else 
				a[r] = dig[d];
			break;
		}
	}

	sort(a.begin() + 1, a.end());
	for (int r = 1; r <= m; r++)
		cout << a[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}