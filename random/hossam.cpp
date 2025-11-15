#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	// a segment [l, r], where 1 <= l <= r <= n, is good iff all pairs of people in the
	// segment are friends

	// the property "good" is subsegment monotonic

	int x, y;
	vector<vector<int>> bad(n + 1);
	set<pair<int, int>> seen;
	while(m--) {
		cin >> x >> y;
		if (!seen.count({x, y}) && !seen.count({y, x})) {
		 	bad[x].push_back(y), bad[y].push_back(x);
		 	seen.insert({x, y}), seen.insert({y, x});
		}
	}

	int l = 1, cnt = 0;
	vector<bool> present(n + 1, false);
	int badcnt = 0;
	for (int r = 1; r <= n; r++) {
		present[r] = true;
		for (int v : bad[r])
			if (present[v])
				badcnt++;

		while (l <= r && badcnt) {
			for (int v : bad[l])
				if (present[v])
					badcnt--;
			present[l++] = false;
		}

		if (l <= r)
			cnt += (r - l + 1);
	}
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}