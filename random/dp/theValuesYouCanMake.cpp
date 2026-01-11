#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 500

int c[MAX + 1];
bool dp[MAX + 1];
set<pair<int, int>> where[MAX + 1];

int32_t main() {
	int n, k;
	cin >> n >> k;

	for (int r = 1; r <= n; r++)
		cin >> c[r];

	dp[0] = true;
	for (int r = 1; r <= n; r++) {
		vector<int> up;
		for (int s = 0; s <= k; s++)
			if (dp[s] && (s + c[r] <= k))
				up.push_back(s + c[r]), where[s + c[r]].insert({s, c[r]});
		for (int e : up)
			dp[e] = true;
	}

	for (auto &[s, e] : where[k])
		cout << s << " " << e << endl;
	return 0;
}
