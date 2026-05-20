#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (2 * 1e9)

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	set<int> s;
	for (int i = 1; i <= n; i++) cin >> a[i], s.insert(a[i]);

	if (s.size() <= 3) {
		cout << 0 << endl;
		return;
	}

	sort(a.begin() + 1, a.end());
	int left = 0;
	int right = INF;

	auto can = [&] (int x) {
		// can we finish all the work in atmost x time?
		int l1 = -INF, r1 = INF;
		int l2 = -INF, r2 = INF;
		int l3 = -INF, r3 = INF;
		for (int i = 1; i <= n; i++) {
			int left = a[i] - x, right = a[i] + x;
			if (left > r1 || right < l1) {
				if (left > r2 || right < l2) {
					if (left > r3 || right < l3)
						return false;
					else l3 = max(l3, left), r3 = min(r3, right);
				} else l2 = max(l2, left), r2 = min(r2, right);
			} else l1 = max(l1, left), r1 = min(r1, right);
		}
		return true;
	};

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid)) right = mid;
		else left = mid;
	}

	cout << right << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}