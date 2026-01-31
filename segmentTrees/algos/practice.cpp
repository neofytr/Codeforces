#include <bits/stdc++.h>
using namespace std;

#define int long long

// point update range query
// the operation is assumed to be applied from left to right in the array
template <typename T>
class PURQ {
private:
	vector<T> tree;
	T identity;
	function<T(T, T)> op;
	int n;

	void build(int idx, int l, int r, vector<T> &arr) {
		if (l == r) {
			tree[idx] = arr[l];
			return;
		}
		int m = l + (r - l) / 2;
		build(2*idx, l, m, arr);
		build(2*idx+1, m+1, r, arr);
		tree[idx] = op(tree[2*idx], tree[2*idx+1]);
	}

	T get(int idx, int l, int r, int ql, int qr) {
		if (r < ql || l > qr) return identity;
		if (ql <= l && r <= qr) return tree[idx];
		int m = l + (r - l) / 2;
		return op(
			get(2*idx, l, m, ql, qr),
			get(2*idx+1, m+1, r, ql, qr)
		);
	}

	void set(int idx, int l, int r, int i, T val) {
		if (l == r) {
			tree[idx] = val;
			return;
		}
		int m = l + (r - l) / 2;
		if (i <= m) set(2*idx, l, m, i, val);
		else set(2*idx+1, m+1, r, i, val);
		tree[idx] = op(tree[2*idx], tree[2*idx+1]);
	}

public:
	PURQ(int n, vector<T> &arr, T identity, function<T(T,T)> op)
		: n(n), identity(identity), op(op) {
		tree.resize(4*n + 1, identity);
		build(1, 1, n, arr);
	}

	T query(int l, int r) {
		return get(1, 1, n, l, r);
	}

	void update(int i, T val) {
		set(1, 1, n, i, val);
	}
};

// range update point query 
// maintains the order of operations using lazy propagation
template <typename T>

class RUPQ {
private:
	vector<T> tree, A;
	T identity;
	function<T(T, T)> op;
	int n;

	void build(int idx, int l, int r) {
		if (l == r) {
			tree[idx] = identity;
			return;
		}

		int m = l + (r - l) / 2;
		build(2 * idx, l, m);
		build(2 * idx + 1, m + 1, r);

		tree[idx] = op(tree[2 * idx], tree[2 * idx + 1]);
	}

	void set(int idx, int l, int r, int ql, int qr, int v) {
		if (r < ql || l > qr) return;
		if (l >= ql && r <= qr) {
			tree[idx] = op(tree[idx], v); // apply the operation
			return;
		}

		// push the unapplied operation lazily downwards
		tree[2 * idx] = op(tree[2 * idx], tree[idx]);
		tree[2 * idx + 1] = op(tree[2 * idx + 1], tree[idx]);
		tree[idx] = identity;

		int m = l + (r - l) / 2;
	}

public:

	RUPQ(int n, vector<T> &arr, T identity, function<T(T, T)> op)
		: n(n), identity(identity), op(op) {
			tree.resize(4 * n + 1, identity);
			A.resize(n + 1);

			for (int r = 1; r <= n; r++) A[r] = arr[r];
			build(1, 1, n);
		}

	T query(int i) {
		return get(1, 1, n, i);
	}

	void update(int l, int r, int val) {
		set(1, 1, n, l, r, val);
	}
}