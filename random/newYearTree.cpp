#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(4 * 1e5)

int c[MAX + 1];
vector<int> graph[MAX + 1];

int lin[MAX + 1];
int pre[MAX + 1], post[MAX + 1];

int tree[4 * MAX + 1];
int lazy[4 * MAX + 1];

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] |= (1ll << lin[l]);
		return;
	}

	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] | tree[(idx << 1) | 1];
}

void push(int l, int r, int idx) {
	if (!lazy[idx]) return;
	tree[idx] = (1ll << lazy[idx]);

	if (l != r) {
		lazy[idx << 1] = lazy[idx];
		lazy[(idx << 1) | 1] = lazy[idx];
	}

	lazy[idx] = 0;
}

int query(int ql, int qr, int l, int r,  int idx) {
	push(l, r, idx);
	if (r < ql || l > qr) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	return query(ql, qr, l, m, idx << 1) | query(ql, qr, m + 1, r, (idx << 1) | 1);
}

void update(int ql, int qr, int v, int l, int r, int idx) {
	if (r < ql || l > qr) return;
	if (l >= ql && r <= qr) {
		lazy[idx] = v;
		push(l, r, idx);
		return;
	}

	push(l, r, idx);
	int m = (l + r) >> 1;
	update(ql, qr, v, l, m, idx << 1), update(ql, qr, v, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] | tree[(idx << 1) | 1];
}

int32_t main() {
	int n, m; cin >> n >> m;
}