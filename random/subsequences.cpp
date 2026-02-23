#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (int)(1e5)
#define MAX_K (int)(11)

int n, k;
int arr[MAX_N + 1];
int tree[MAX_N + 1][MAX_K + 1];

void update(int elt, vector<int> &dp, int l, int r, int idx) {
	if (l == r) {
		for (int i = 0; i <= k + 1; i++)
			tree[idx][i] = dp[i];
		return;
	}

	int m = (l + r) >> 1;
	if (elt <= m) update(elt, dp, l, m, idx << 1);
	else update(elt, dp, m + 1, r, (idx << 1) | 1);

	for (int i = 0; i <= k + 1; i++)
		tree[idx][i] = tree[idx << 1][i] + tree[(idx << 1) | 1][i];
}

int query(int elt, int j, int l, int r, int idx) {
	if (elt < l || 1 > r) return 0;
	if (l >= 1 && r <= elt) return tree[idx][j];

	int m = (l + r) >> 1; 
	int left = query(elt, j, l, m, idx << 1);
	int right = query(elt, j, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	cin >> n >> k;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<vector<int>> dp(n + 1, vector<int>(k + 2, 0));
	dp[1][0] = 0, dp[1][1] = 1;
	return 0;
}