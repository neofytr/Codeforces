#include <bits/stdc++.h>
using namespace std;

#define int long long

auto cmp = [](const pair<int, int> &one, const pair<int, int> &two) -> bool {
	if (one.first < two.first) return true;
	if (one.first == two.first && one.second < two.second) return true;

	return false;
};

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	unordered_map<int, int> f;
	set<pair<int, int>, decltype(cmp)> s(cmp);
	for (int r = 1; r <= n; r++)
		if (arr[r] % k)
			f[k - arr[r] % k]++;

	for (auto &[r, cnt] : f)
		s.insert(make_pair(cnt, r));

	if (s.empty()) {
		cout << 0 << endl;
		return;
	}

	auto [maxi, m] = *(s.rbegin());

	cout << (maxi - 1) * k + (m + 1) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}