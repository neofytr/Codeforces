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

	// all walls to the left?
	bool allLeft = true;
	for (int r = 1; r <= x - 1; r++)
		if (!g[r]) {
			allLeft = false;
			break;
		} 

	// all walls to the right?
	bool allRight = true;
	for (int r = x + 1; r <= n; r++)
		if (!g[r]) {
			allRight = false;
			break;
		}

	if (allLeft || allRight) {
		cout << min(x, n - x + 1) << endl;
		return;
	}

	set<int> walls;
	for (int r = 1; r <= n; r++)
		if (g[r]) walls.insert(r);
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}