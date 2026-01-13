#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(2 * 1e5)
#define INF (int)(1e16)

int arr[MAX];
pair<int, int> dp[MAX + 1];

void solve() {
	int n;
	cin >> n;

	arr[0] = INF;
	for (int r = 1; r <= n; r++) cin >> arr[r];

	p[0] = 0;
	for (int r = 1; r <= n; r++)
		p[r] += p[r - 1] + (arr[r] > arr[r - 1] ? 1 : 0);

	dp[1] = {0, 0};
	for (int i = 2; i <= n; r++) {
		// all the elements are in the other array
		dp[i] = {p[i - 1] - p[1], i - 1};
		for (int j = 1; j <= i - 1; j++) {
			auto [v, idx] = dp[j];
		}
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