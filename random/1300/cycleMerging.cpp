#include <bits/stdc++.h>
using namespace std;

#define int long long

int next(int r, int n) {
	if (r == n) return 1;
	return r + 1;
}

int prev(int r, set<int> &notdone) {
	auto itr = notdone.lower_bound(r);
	if (itr == notdone.begin())
		return *notdone.rbegin();
	return *(--itr);
}

int next(int r, set<int> &notdone) {
	auto itr = notdone.upper_bound(r);
	if (itr == notdone.end())
		return *notdone.begin();
	return *(itr);
}

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	set<int> notdone;
	for (int r = 1; r <= n; r++) notdone.insert(r);

	set<pair<int, int>> m;
	for (int r = 1; r <= n; r++) m.insert({arr[r], r});

	int cost = 0;
	while (notdone.size() > 1) {
		auto [x, r] = *m.begin();
		m.erase(m.begin());

		int nxt = next(r, notdone);
		while (arr[nxt] <= x) {
			cost += x, notdone.erase(nxt), m.erase({arr[nxt], nxt}), nxt = next(r, notdone);
			if (nxt == r)
				break;
		}

		if (notdone.size() > 1) {
			int prv = prev(r, notdone);
			while (arr[prv] <= x) {
				cost += x, notdone.erase(prv), m.erase({arr[prv], prv}), prv = prev(r, notdone);
				if (prv == r)
					break;
			}
		} else 
			break;
	}

	cout << cost << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}