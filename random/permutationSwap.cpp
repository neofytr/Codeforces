#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

void solve() {
	int n;
	cin >> n;

	unordered_map<int, int> mp;
	vector<int> perm(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> perm[r], mp[perm[r]] = r;

	int g = 0;
	for (int r = 1; r <= n; r++)
		if (r != perm[r]) {
			int ex = perm[r];
			g = gcd(g, abs(r - perm[r]));
		}

	cout << g << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}

	return 0;
}