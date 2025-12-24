#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];
	
	vector<int> div;
	for (int r = 1; r * r <= b[n]; r++)
		if (!(b[n] % r)) {
			int one = r, two = b[n] / r;
			div.push_back(one);
			if (one != two) div.push_back(two);
		}
	sort(div.begin(), div.end());

	for (int d : div) {
		if (d > b[1]) break;
		if (b[1] % d) continue;
	}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}