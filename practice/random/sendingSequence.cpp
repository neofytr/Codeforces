#include <bits/stdc++.h>
using namespace std;

#define int long long
#define N (int)(2 * 1e5)

int b[N + 1];
int dp[N + 1];
unordered_map<int, vector<int>> diff;

// sum(k) = n - |k|

// r (r + 1) (r + 2) ... k

int calc(int r, int n) {
	if (r == n + 1)
		return 1;
	else if (r > n + 1)
		return 0;
	if (dp[r] != -1)
		return dp[r];

	int first = calc(r + b[r] + 1, n);
	if (first)
		return dp[r] = 1; 

	for (int idx : diff[r])
		if (idx > r && calc(idx + 1, n))
			return dp[r] = 1;

	// for (int k = r + 1; k <= n; k++)
	// 	if (k - r == b[k] && calc(k + 1, n)) 
	// 		return dp[r] = 1;

	return dp[r] = 0;
}

void solve() {
	int n;
	cin >> n;

	memset((void *)dp, 0xff, sizeof(int) * (n + 1));
	diff.clear();
	
	for (int r = 1; r <= n; r++) cin >> b[r];
	for (int r = 1; r <= n; r++)
		diff[r - b[r]].push_back(r);

	// dp[r] is true iff the segment [r, n] can be sent over the network
	calc(1, n);

	cout << (dp[1] ? "YES" : "NO") << endl;
} 

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}

	return 0;
}