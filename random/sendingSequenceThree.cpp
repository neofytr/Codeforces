#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];

	// dp[r] is 1 iff b[1, r] can be sent over the network
	vector<int> dp(n + 1, 0);

    dp[0] = 1;
    for (int r = 1; r <= n; r++) { 
    	if (dp[r - 1] && r + b[r] <= n)
    		dp[r + arr[r]] = 1;
    	if (r - arr[r] - 1 >= 0)
    		dp[r] |= dp[r - b[r] - 1];
 	}

 	cout << (dp[n] ? "YES" : "NO") << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}