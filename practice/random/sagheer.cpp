#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, s;
	cin >> n >> s;

	vector<int> base(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> base[r];

	vector<int> prices(n + 1);
	auto can = [&](int x) -> bool {
		// can he buy x souvenirs?
		prices = base;
		for (int r = 1; r <= n; r++)
			prices[r] += (r * x);
		sort(prices.begin(), prices.end());

		int cost = 0;
		for (int r = 1; r <= x; r++)
			cost += prices[r];
		return cost <= s;
	};

	int left = 0; // he can buy 0 souvenirs
	int right = n + 1; // it is impossible to buy n + 1 souvenirs

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			left = mid;
		else 
			right = mid;
	}

	cout << left << " ";
	prices = base;
	for (int r = 1; r <= n; r++)
		prices[r] += (r * left);
	sort(prices.begin(), prices.end());
	int cost = 0;
	for (int r = 1; r <= left; r++)
		cost += prices[r];
	cout << cost << endl;
	return 0;
}