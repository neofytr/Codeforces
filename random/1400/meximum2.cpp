#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(int tc) {
	int n, k, q;
	cin >> n >> k >> q;

	vector<pair<int, int>> mini, mexi;
	vector<array<int,3>> queries;
	vector<int> arr(n + 1, -1);

	for (int i = 0; i < q; i++) {
		int c, l, r;
		cin >> c >> l >> r;
		queries.push_back({c, l, r});
		if (c == 1) mini.push_back({l, r});
		else mexi.push_back({l, r});
	}

	for (auto [l, r] : mini)
		for (int i = l; i <= r; i++) 
			arr[i] = k;

	for (auto [l, r] : mexi) {
		set<int> s;
		for (int i = 0; i <= k - 1; i++)
			s.insert(i);
		for (int i = l; i <= r; i++)
			if (arr[i] == k) arr[i]++;

		for (int i = l; i <= r; i++)
			if (arr[i] == -1 && !s.empty())
				arr[i] = *s.begin(), s.erase(s.begin());
	}

	for (int i = 1; i <= n; i++)
		if (arr[i] == -1) arr[i] = 0;

	for (int i = 1; i <= n; i++)
		cout << arr[i] << " ";
	cout << "\n";
}

int32_t main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++)
		solve(tc);

	return 0;
}
