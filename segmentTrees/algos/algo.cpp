#include <bits/stdc++.h>
using namespace std;

#define int long long

// Point Update Range Query
// update(i, v) : set arr[i] to v
// query(l, r): get the value of arr[l] op arr[l + 1] ... op arr[r]

// The operation op should be associative and should have an identity element.
// op(p, q) = p op q and not the other way round
template<typename T>
class PURQ {
private:
	vector<T> tree;
	function<T(T, T)> op;
	int n;
	T iden;

	void build(int idx, int l, int r, vector<T> &arr) {
		if (l == r) {
			tree[idx] = arr[l];
			return;
		}

		int m = (l + r) / 2;
		build(2 * idx, l, m, arr);
		build(2 * idx + 1, m + 1, r, arr);

		tree[idx] = op(tree[2 * idx], tree[2 * idx + 1]);
	}

	T get(int idx, int l, int r, int ql, int qr) {
		if (r < ql || l > qr) return iden;
		if (l >= ql && r <= qr) return tree[idx];

		int m = (l + r) / 2;
		T left = get(2 * idx, l, m, ql, qr);
		T right = get(2 * idx + 1, m + 1, r, ql, qr);

		return op(left, right);
	}

	void set(int idx, int l, int r, int i, T v) {
		if (i < l || i > r) return;
		if (l == r) {
			tree[idx] = v;
			return;
		}

		int m = (l + r) / 2;
		if (i <= m) set(2 * idx, l, m, i, v);
		else set(2 * idx + 1, m + 1, r, i, v);

		tree[idx] = op(tree[2 * idx], tree[2 * idx + 1]);
	}

public:
	PURQ(int n, vector<T> &arr, function<T(T, T)> op, T iden)
		: n(n), op(op), iden(iden) {
			tree.resize(4 * n + 1);
			build(1, 1, n, arr);
		} 

	T query(int l, int r) {
		return get(1, 1, n, l, r);
	}

	T update(int i, T v) {
		return set(1, 1, n, i, v);
	}
}