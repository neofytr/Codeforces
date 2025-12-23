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
		return *itr.begin();
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

		while (arr[next(r, notdone)] <= x)
			notdone.erase({arr[next(r, notdone)], next(r, notdone)}), r++;
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