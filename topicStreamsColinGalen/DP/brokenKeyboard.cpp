#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, k;
	cin >> n >> k;

	string s; cin >> s;
	vector<char> str(n + 1);
	for (int r = 1; r <= n; r++) str[r] = s[r - 1];

	char c;
	unordered_map<char, bool> f;
	for (int r = 1; r <= k; r++) cin >> c, f[c] = true;

	// dp[r] is the number of substrings ending at r that can be
	// typed for 1 <= r <= n
	vector<int> dp(n + 1, 0);

	dp[1] = f[str[1]];
	for (int r = 2; r <= n; r++)
		if (f[str[r]]) 
			dp[r] += (dp[r - 1] + 1);
		

	int cnt = 0;
	for (int r = 1; r <= n; r++) cnt += dp[r];
	cout << cnt << endl;
}