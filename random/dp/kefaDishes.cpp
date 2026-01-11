#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	int x, y, c;
	vector<pair<pair<int, int>, int>> rules(k + 1);
	for (int r = 1; r <= k; r++)
		cin >> x >> y >> c, rules[r] = {{x, y}, c};

	return 0;
}