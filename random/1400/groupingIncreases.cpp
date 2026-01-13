#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(2 * 1e5)
#define INF (int)(1e16)

int arr[MAX + 1];
int dp[MAX + 1][2];
int p[MAX + 1];

void solve() {
	int n;
	cin >> n;

	arr[0] = INF;
	for (int r = 1; r <= n; r++) cin >> arr[r];

	p[0] = 0;
	for (int r = 2; r <= n; r++)
		p[r] = (p[r - 1] + (arr[r] > arr[r - 1] ? 1 : 0));

	// dp[i][0] is the minimum possible penality for arr[1, r] if r goes into s
	// dp[i][1] is the minimum possible penality for arr[1, r] if r goes into t
	for (int i = 0; i <= n; i++)
		dp[i][0] = dp[i][1] = INF;

	dp[0][0] = dp[0][1] = 0;
	for (int i = 1; i <= n; i++) 
		for (int j = 0; j <= i - 1; j++) {
			dp[i][0] = min(dp[i][0], dp[j][0] + p[i - 1] - p[j + 1] + (arr[i] > arr[j] ? 1 : 0));
			dp[i][1] = min(dp[i][1], dp[j][1] + p[i - 1] - p[j + 1] + (arr[i] > arr[j] ? 1 : 0));
		}


	cout << min(dp[n][0], dp[n][1]) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}