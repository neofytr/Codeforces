#include <bits/stdc++.h>
using namespace std;

#define int long long
#define OFFSET (int)(1e6)
#define INF (int)(1e17)

typedef pair<int, int> Line;
Line tree[8 * OFFSET + 1];

void init(int l = 0, int r = 2 * OFFSET, int idx = 1) {
	tree[idx] = {INF, INF};
	if (l == r) return;

	int m = (l + r) >> 1;
	init(l, m, idx << 1);
	init(m + 1, r, (idx << 1) | 1);
}

int val(const Line &l, int x) {
	return l.first * (x - OFFSET) + l.second;
}

void insert(Line L, int l = 0, int r = 2 * OFFSET, int idx = 1) {
	if (tree[idx].first == INF) {
		tree[idx] = L;
		return;
	}

	int m = (l + r) >> 1;
	bool mid = (val(L, m) < val(tree[idx], m));
	if (mid) swap(L, tree[idx]);
	if (l == r) return;

	if (val(L, l) < val(tree[idx], l)) insert(L, l, m, idx << 1);
	else if (val(L, r) < val(tree[idx], r)) insert(L, m + 1, r, (idx << 1) | 1);
}

int query(int x, int l = 0, int r = 2 * OFFSET, int idx = 1) {
	if (tree[idx].first == INF) return INF;
	if (l == r) return val(tree[idx], x + OFFSET);

	int m = (l + r) >> 1;
	if ((x + OFFSET) <= m) return min(val(tree[idx], x + OFFSET), query(x, l, m, idx << 1));
	return min(val(tree[idx], x + OFFSET), query(x, m + 1, r, (idx << 1) | 1));
}


int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1), p(n + 1, 0);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + a[r];

	init();
	vector<int> dp(n + 1);
	dp[1] = 0, insert({-p[1 - 1], dp[1]});
	for (int r = 2; r <= n; r++)
		dp[r] = query(b[r]) + b[r] * p[r], insert({-p[r - 1], dp[r]});

	for (int r = 1; r <= n; r++)
		cout << dp[r] << " ";
	cout << endl;
	return 0;
}