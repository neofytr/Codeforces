#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int) (1e5)

int tree[4 * MAX + 1];
int lazy[4 * MAX + 1];

void push(int l, int r, int idx) {
	if (!lazy[idx]) return;

	tree[idx] += (r - l + 1) * lazy[idx];
	if (l != r) {
		lazy[idx << 1] += lazy[idx];
		lazy[(idx << 1) | 1] += lazy[idx];
	}

	lazy[idx] = 0;
}

int query(int ql, int qr, int l, int r, int idx) {
	push(l, r, idx);
	if (qr < l || r < ql) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

void update(int ql, int qr, int v, int l, int r, int idx) {
	if (qr < l || r < ql) return;
	if (l >= ql && r <= qr) {
		lazy[idx] += v;
		push(l, r, idx);
		return;
	}

	push(l, r, idx);
	int m = (l + r) >> 1;
	update(ql, qr, v, l, m, idx << 1), update(ql, qr, v, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}