#include <bits/stdc++.h>
using namespace std;

#define int long long

// Point Update Range Query
// update(i, v) : set arr[i] to v
// query(l, r): get the value of arr[l] op arr[l + 1] ... op arr[r]
// The operation op should be associative and should have an identity element.
// op(p, q) = p op q and not the other way round
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
