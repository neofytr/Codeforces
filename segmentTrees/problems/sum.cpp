#include <bits/stdc++.h>
using namespace std;

#define int long long

class SegmentTree {
	int len;
	vector<int> values;

	void build(int idx, int l, int r, vector<int> &arr) {
		if (l == r) {
			values[idx] = arr[l];
			return;
		}
	}

	SegmentTree(int n, vector<int> &arr) {
		values.resize(4 * n + 1);
		len = n;

		build()
	}
}