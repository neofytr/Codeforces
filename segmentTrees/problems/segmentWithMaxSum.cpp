#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef struct _Node {
	int r, s, t, u;
	// r is the maximum sum in any subsegment of the node
	// s if the maximum prefix in the segment of the node
	// t is the maximum suffix in the segment of the node
	// u is the sum of the elements in the segment
} Node;

typedef struct _Op {
	inline Node operator() (const Node &left, const Node &right) const {
		Node parent;
		parent.r = max({left.r, right.r, left.t + right.s});
		parent.s = max({left.s, left.u + right.s});
		parent.t = max({right.t, right.u + left.t});
		parent.u = left.u + right.u;
		return parent;
	}
} Op;

template<typename T, typename Op>
class PURQ {
private:
	vector<T> tree;
	const T iden;
	Op op;
	int n;

	inline void build(int idx, int l, int r, const vector<T>& arr) {
		if (l == r) {
			tree[idx] = arr[l];
			return;
		}

		int lc = idx << 1;
		int rc = lc | 1;
		int m = (l + r) >> 1;

		build(lc, l, m, arr);
		build(rc, m + 1, r, arr);

		tree[idx] = op(tree[lc], tree[rc]);
	}

	inline T queryImpl(int idx, int l, int r, int ql, int qr) const {
		if (r < ql || l > qr)
			return iden;

		if (ql <= l && r <= qr)
			return tree[idx];

		int lc = idx << 1;
		int rc = lc | 1;
		int m = (l + r) >> 1;

		return op(
			queryImpl(lc, l, m, ql, qr),
			queryImpl(rc, m + 1, r, ql, qr)
		);
	}

	inline void updateImpl(int idx, int l, int r, int pos, const T& val) {
		if (l == r) {
			tree[idx] = val;
			return;
		}

		int lc = idx << 1;
		int rc = lc | 1;
		int m = (l + r) >> 1;

		if (pos <= m) updateImpl(lc, l, m, pos, val);
		else updateImpl(rc, m + 1, r, pos, val);

		tree[idx] = op(tree[lc], tree[rc]);
	}

public:
	PURQ(int n, const vector<T>& arr, Op op, T iden)
		: n(n), iden(iden), op(op) {
		tree.resize(4 * n + 5);
		build(1, 1, n, arr);
	}

	inline T query(int l, int r) const {
		return queryImpl(1, 1, n, l, r);
	}

	inline void update(int pos, const T& val) {
		updateImpl(1, 1, n, pos, val);
	}
};

Node conv(int x) {
	Node node;
	node.r = max(0ll, x);
	node.s = max(0ll, x);
	node.t = max(0ll, x);
	node.u = x;
	return node;
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<Node> arr(n + 1);
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		arr[i] = conv(x);
	} 

	PURQ<Node, Op> seg(n, arr, Op(), (Node){.r = LLONG_MIN, .s = LLONG_MIN, .t = LLONG_MIN, .u = 0});
	cout << seg.query(1, n).r << endl;
	while (m--) {
		int i, v;
		cin >> i >> v;
		i++;

		// update the value of a[i] to v and find m = maximum sum on any segment
		// of the array

		seg.update(i, conv(v));
		cout << seg.query(1, n).r << endl;
	}
	return 0;
}