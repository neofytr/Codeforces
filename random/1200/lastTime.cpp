#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, k;
	cin >> n >> k;

	int left, right, val;
	vector<pair<int, int>> cas(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> left >> right >> val, cas[r] = {left, val};

	sort(cas.begin() + 1, cas.end());
	int previdx = 1, curridx = 0, curr = k;

	while (true) {
		int tmp = curr;
		int tmpidx = curridx;
		for (int r = previdx; r <= n; r++) {
			left = cas[r].first, val = cas[r].second;
			if (left > tmp)
				break;
			if (val > curr)
				curr = val, curridx = r;
		}

		if (tmp == curr)
			break;

		previdx = curridx;
	}

	cout << curr << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}