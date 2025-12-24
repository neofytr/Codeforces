#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x;
	cin >> n >> x;

	string str;
	cin >> str;

	vector<int> grid(n + 1);
	for (int r = 1; r <= n; r++)
		if (str[r - 1] == '.') grid[r] = 0;
		else grid[r] = 1;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}