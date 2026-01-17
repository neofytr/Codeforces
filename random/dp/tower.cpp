#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)1e18
#define MAX_W 10000000  // 1e7

int dp[MAX_W + 1];

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> w(n), s(n), v(n);
	vector<int> ord(n);

	for (int i = 0; i < n; i++) {
		cin >> w[i] >> s[i] >> v[i];
		ord[i] = i;
	}

	sort(ord.begin(), ord.end(), [&](int a, int b) {
		return w[a] + s[a] < w[b] + s[b];
	});

	for (int i = 0; i <= MAX_W; i++) dp[i] = -INF;
	dp[0] = 0;

	for (int idx : ord) {
		for (int x = s[idx]; x >= 0; x--) {
			if (dp[x] == -INF) continue;
			dp[x + w[idx]] = max(dp[x + w[idx]], dp[x] + v[idx]);
		}
	}

	int ans = 0;
	for (int i = 0; i <= MAX_W; i++)
		ans = max(ans, dp[i]);

	cout << ans << '\n';
	return 0;
}
