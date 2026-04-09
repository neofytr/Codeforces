#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
public:
	int len;
	vector<int> values;

	void build(int idx, int l, int r, vector<int> &arr) {
		if (l == r) {
			values[idx] = arr[l];
			return;
		}

		int m = l + (r - l) / 2;
		build(2 * idx, l, m, arr);
		build(2 * idx + 1, m + 1, r, arr);

		values[idx] = values[2 * idx] + values[2 * idx + 1];
	}

	void update(int i, int v, int idx, int l, int r) {
		if (l == r) {
			values[idx] = v;
			return;
		}

		if (i < l || i > r)
			return;

		int m = l + (r - l) / 2;
		if (i <= m)
			update(i, v, 2 * idx, l, m);
		else 
			update(i, v, 2 * idx + 1, m + 1, r);

		values[idx] = values[2 * idx] + values[2 * idx + 1];
	}

	int get(int l, int r, int rangeL, int rangeR, int idx) {
		if (r < rangeL || rangeR < l) return 0;
		if (l >= rangeL && r <= rangeR) return values[idx];

		if (l == r) return values[idx];

		int m = l + (r - l) / 2;
		int left = get(l, m, rangeL, rangeR, 2 * idx);
		int right = get(m + 1, r, rangeL, rangeR, 2 * idx + 1);

		return left + right;
	}

	SegmentTree(int n, vector<int> &arr) {
		values.resize(4 * n + 1);
		len = n;

		build(1, 1, len, arr);
	}

	void set(int i, int v) {
		update(i, v, 1, 1, len);
	}

	int sum(int l, int r) {
		return get(1, len, l, r, 1);
	}
};

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	SegmentTree s(n, arr);
	while (m--) {
		int type; cin >> type;
		if (type == 1) {
			int i, v;
			cin >> i >> v;

			s.set(i + 1, v);
		} else {
			int l, r;
			cin >> l >> r;

			cout << s.sum(l + 1, r) << endl;
		}
	}

	return 0;
}