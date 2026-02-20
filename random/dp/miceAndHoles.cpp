#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e3)
#define INF (int)(1e12)

int dp[MAX + 1][MAX + 1];
int x[MAX + 1];
int cost[MAX + 1][MAX + 1];
pair<int, int> h[MAX + 1];

void solve() {
	int n, m; cin >> n >> m;
	for (int r = 1; r <= n; r++) cin >> x[r];
	for (int r = 1; r <= m; r++)
		cin >> h[r].first >> h[r].second;

	sort(x + 1, x + n + 1);
	sort(h + 1, h + m + 1);

	for (int j = 1; j <= m; j++) {
		cost[j][0] = 0; 
		for (int i = 1; i <= n; i++)
			cost[j][i] = cost[j][i - 1] + llabs(h[j].first - x[i]);
	}

	for (int j = 0; j <= m; j++)
		for (int i = 0; i <= n; i++)
			dp[j][i] = INF;

	// dp[j][i] is the min cost to fill the first j holes with the first i mice
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) dp[0][i] = INF;
	for (int j = 1; j <= m; j++) dp[j][0] = 0;

	for (int j = 1; j <= m; j++) {
		deque<int> dq;
		for (int i = 1; i <= n; i++) {
			dp[j][i] = dp[j - 1][i];
			int left = i - min(i, h[j].second);
			int right = i - 1;

			while (!dq.empty() && dq.front() < left)
				dq.pop_front();

			int ins = dp[j - 1][right] - cost[j][right];
			while (!dq.empty() && dp[j - 1][dq.back()] - cost[j][dq.back()] >= ins)
				dq.pop_back();
			dq.push_back(right);

			dp[j][i] = min(dp[j][i], dp[j - 1][dq.front()] - cost[j][dq.front()]) + cost[j][i];
		}
	}

	if (dp[m][n] >= INF) cout << -1 << endl;
	else cout << dp[m][n] << endl;
}

int32_t main() {
	solve();
	return 0;
}