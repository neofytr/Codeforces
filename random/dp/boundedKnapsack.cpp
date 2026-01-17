#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX_N (int)(1e3)
#define MAX_W (int)(1e3)

int dp[MAX_W + 1];

int32_t main() {
	int n, W;
	cin >> n >> W;

	vector<pair<int, int>> items(1, {0, 0});

	int w, v, k;
	for (int r = 1; r <= n; r++) {
		cin >> w >> v >> k;

		for (int b = 0; b <= 63; b++)
			if ((1ll << b) & k) items.push_back({w * (1ll << b), v * (1ll << b)});
	}

	n = items.size() - 1;
	dp[0] = 0;
	for (int r = 1; r <= n; r++) {
		w = items[r].first, v = items[r].second;
		for (int x = W; x >= w; x--)
			dp[x] = max(dp[x], dp[x - w] + v);
	}
	return 0;
}