#include <bits/stdc++.h>
using namespace std;

#define int long long 

int getMask(string &f) {
	int m = 0;
	if (f.find("A") != f.npos()) m |= 1;
	if (f.find("B") != f.npos()) m |= 2;
	if (f.find("C") != f.npos()) m |= 4;
	return m;
}

int32_t main() {
	int n;
	cin >> n;

	vector<pair<int, string>> v(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v.first >> v.second;

	// Let 0 <= r < 7
	// Bit 0 of r represents if A is present or not
	// Bit 1 of r represents if B is present or not
	// Bit 2 of r represents if C is present or not
	// dp[k][r] is the minimum cost of having r in [1, k]
	vector<int> dp(n + 1, vector<int>(8, LLONG_MAX));

	int m = getMask(v[1].second);
	for (int submask = m; submask = (submask - 1) & m;) {
		if (!submask) {
			dp[1][submask] = 0;
			break;		
		} 
		dp[submask] = v[1].first;
	}
		

	for (int r = 1; r <= n; r++) {
		int cost = v[r].first;
		string &f = v[r].second;

		int mask = getMask(f);
		for (int submask = m; submask = (submask - 1) & m;) {
			if (!submask) {
				dp[r][submask] = dp[r - 1][submask];
				break;
			}
		}
	}
}