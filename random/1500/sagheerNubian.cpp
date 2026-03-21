#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, S; cin >> n >> S;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	auto can = [&] (int x) -> bool {
		vector<int> b(n + 1);
		for (int i = 1; i <= n; i++) b[i] = a[i] + i * x;
		sort(b.begin() + 1, b.end());

		int cost = 0;
		for (int i = 1; i <= x; i++) cost += b[i];
		return cost <= S;
	};

	int left = 0;
	int right = n + 1;
	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (can(mid)) left = mid;
		else right = mid;
	}

	cout << left << " ";
	vector<int> b(n + 1);
	for (int i = 1; i <= n; i++) b[i] = a[i] + i * left;
	sort(b.begin() + 1, b.end());
	int cost = 0;
	for (int i = 1; i <= left; i++) cost += b[i];
	cout << cost << endl;
	return 0;
}