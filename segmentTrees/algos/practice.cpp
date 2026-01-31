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
// eliminates the need for the operation to be commutative
// just requires the operation to be associative and have an identity element
template <typename T>
class RUPQ {
private:
	vector<T> tree, A;
	T identity;
	function<T(T, T)> op;
	int n;

	void build(int idx, int l, int r) {
		tree[idx] = identity;
		if (l == r) return;
		int m = (l + r) / 2;
		build(2*idx, l, m);
		build(2*idx+1, m+1, r);
	}

	void set(int idx, int l, int r, int ql, int qr, T v) {
		if (r < ql || l > qr) return;

		if (ql <= l && r <= qr) {
			tree[idx] = op(tree[idx], v);
			return;
		}

		// push lazy value
		tree[2*idx] = op(tree[2*idx], tree[idx]);
		tree[2*idx+1] = op(tree[2*idx+1], tree[idx]);
		tree[idx] = identity;

		int m = (l + r) / 2;
		set(2*idx, l, m, ql, qr, v);
		set(2*idx+1, m+1, r, ql, qr, v);
	}

	T get(int idx, int l, int r, int i) {
		if (l == r) return tree[idx];
		int m = (l + r) / 2;
		if (i <= m) return op(tree[idx], get(2*idx, l, m, i));
		return op(tree[idx], get(2*idx+1, m+1, r, i));
	}

public:
	RUPQ(int n, vector<T> &arr, T identity, function<T(T, T)> op)
		: n(n), identity(identity), op(op) {
		tree.resize(4*n + 1, identity);
		A = arr;
		build(1, 1, n);
	}

	T query(int i) {
		return op(A[i], get(1, 1, n, i));
	}

	void update(int l, int r, T val) {
		set(1, 1, n, l, r, val);
	}
};

template<typename T>
class RURQ {
private:
	vector<T> qtree, utree; // query tree, update tree
	function<T(T, T)> qop, uop; // query operation, update operation
	T qiden, uiden; // query identity value, update identity value
	int n;

	void build(int idx, int l, int r, vector<int> &arr) {
		if (l == r) {
			qtree[idx] = arr[l];
			utree[idx] = uiden;
		}
	}

public:
	RURQ(int n, vector<T> &arr, T qiden, T uiden, function<T(T, T)> qop, function<T, T> uop)
		: n(n), qiden(qiden), uiden(uiden), qop(qop), uop(uop) {
			qtree.resize(4 * n + 1, qiden);
			utree.resize(4 * n + 1, uiden);

			build(1, 1, n, arr);
		}
}