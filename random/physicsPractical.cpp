#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (5000)

int calc(int l, int r, vector<pair<int, int>> &v, vector<vector<int>> &dp) {
	int sz = v.size();
	if (l >= sz || r < 0)
		return 0;
	if (l > r)
		return 0;
	int mini = v[l].first, maxi = v[r].first;
	if (mini * 2 >= maxi)
		return dp[mini][maxi] = 0;
	if (dp[mini][maxi] != -1)
		return dp[mini][maxi];

	int r1 = calc(l + 1, r, v, dp) + v[l].second;
	int r2 = calc(l, r - 1, v, dp) + v[r].second;
	return dp[mini][maxi] = min(r1, r2);
}

int32_t main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	int val;
	map<int, int> f;
	for (int r = 1; r <= n; r++) cin >> val, f[val]++;

	vector<pair<int, int>> v;
	for (auto &[elt, cnt] : f)
		v.push_back({elt, cnt});
	int sz = (int)v.size();

	vector<vector<int>> dp(MAX + 1, vector<int>(MAX + 1, -1));
	calc(0, sz - 1, v, dp);
	cout << dp[v[0].first][v[sz - 1].first] << endl;
	return 0;
}