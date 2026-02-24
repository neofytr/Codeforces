#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define INF (int)(1e18)

int n;  
int a[MAX + 1], b[MAX + 1], c[MAX + 1];
int dp[MAX + 1];
unordered_map<int, int> f;

typedef pair<int, int> Line;
Line tree[4 * MAX + 1];

void init(int l = 0, int r = n, int idx = 1) {
	tree[idx] = {INF, INF};
	if (l == r) return;
	int m = (l + r) >> 1;
	init(l, m, idx << 1), init(m + 1, r, (idx << 1) | 1);
}

int val(const Line &l, int x) {
	return l.first * c[x] + l.second;
}

void insert(Line L, int l = 0, int r = n, int idx = 1) {
	if (tree[idx].first == INF) {
		tree[idx] = L;
		return;
	}

	int m = (l + r) >> 1;
	bool mid = val(L, m) < val(tree[idx], m);
	if (mid) swap(L, tree[idx]);
	if (l == r) return;

	if (val(L, l) < val(tree[idx], l)) insert(L, l, m, idx << 1);
	else if (val(L, r) < val(tree[idx], r)) insert(L, m + 1, r, (idx << 1) | 1);
}

int query(int x, int l = 0, int r = n, int idx = 1) {
	if (tree[idx].first == INF) return INF;
	if (l == r) {
		return val(tree[idx], x);
	}

	int m = (l + r) >> 1;
	if (x <= m) return min(val(tree[idx], x), query(x, l, m, idx << 1));
	return min(val(tree[idx], x), query(x, m + 1, r, (idx << 1) | 1));
}

int32_t main() {
	cin >> n;
	for (int r = 1; r <= n; r++) cin >> a[r], c[r] = a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	init();
	sort(c + 1, c + n + 1);
	for (int r = 1; r <= n; r++) f[c[r]] = r;

	dp[1] = 0, insert({b[1], dp[1]});
	for (int r = 2; r <= n; r++)
		dp[r] = query(f[a[r]]), insert({b[r], dp[r]});

	cout << dp[n] << endl;
	return 0;
}