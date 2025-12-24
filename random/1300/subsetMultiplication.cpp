#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];
	
	int i = n;
	while (i >= 2 && !(b[i] % b[i - 1])) i--;

	if (i == 1) {
		cout << 1 << endl;
		return;
	}

	set<int> div;
	for (int r = 1; r * r <= b[i]; r++)
		if (!(b[i] % r))
			div.insert(r), div.insert(b[i] / r);

	set<pair<int, int>> p;
	for (int d : div)
		if (!(b[i - 1] % d))
			p.insert({d, b[i - 1] / d});

	for (int r = i - 2; r >= 1; r--) {
		set<pair<int, int>> tmp;
		for (auto &[d, x] : p) 
			if (!(d % b[r])) {
				tmp.insert({b[r], x});
            }
			else if (!(b[r] % x)) {
				int dd = b[r] / x;
				if (!(d % dd)) { 
					tmp.insert({dd, x});
				}
			}
		p = tmp;
	}

	cout << (p.begin())->second << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}