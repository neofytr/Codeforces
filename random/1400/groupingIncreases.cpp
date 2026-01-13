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

	arr[0] = -INF;
	for (int r = 1; r <= n; r++) cin >> arr[r];

	p[1] = 0;
	for (int r = 2; r <= n; r++)
		p[r] = (p[r - 1] + (arr[r] > arr[r - 1] ? 1 : 0));

	// dp[i][0] is the minimum possible penality for arr[1, r] if r goes into s
	// dp[i][1] is the minimum possible penality for arr[1, r] if r goes into t
	for (int i = 0; i <= n; i++)
		dp[i][0] = dp[i][1] = INF;

	for (int i = 1; i <= n; r++) 
		for (int j = 0; j <= i; i++) { // index j is the last element in s

		}
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}