#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e5)
#define INF (int)(1e17)

int x[MAX + 1];
pair<int, int> tree[4 * MAX + 1];

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = {x[l], l};
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	auto left = tree[idx << 1], right = tree[(idx << 1) | 1];
	if (left.first < right.first) tree[idx] = left;
	else if (right.first < left.first) tree[idx] = right;
	else tree[idx] = {left.first, min(left.second, right.second)};
}

pair<int, int> query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return {INF, INF};
	if (l >= ql && r <= qr) return tree[idx];
	int m = (l + r) >> 1;
	auto left = query(ql, qr, l, m, idx << 1), right = query(ql, qr, m + 1, r, (idx << 1) | 1);
	if (left.first < right.first) return left;
	else if (right.first < left.first) return right;
	else return {left.first, min(right.second, left.second)};
}

void solve() { 
	string str; cin >> str;
	int k; cin >> k;
	int n = str.length();
	for (int i = 1; i <= n; i++)
		x[i] = str[i - 1] - '0';

	build(1, n, 1);
	string f;
	pair<int, int> m = {INF, INF};
	int req = n - k;
	for (int i = 1; i <= n - req + 1; i++)
		if (x[i] && x[i] < m.first) m = {x[i], i};

	f.push_back(m.first + '0');
	int i = m.second + 1;
	req--;
	while (f.size() < n - k) {
		m = query(i, n - req + 1, 1, n, 1);
		i = m.second + 1;
		f.push_back(m.first + '0');
		req--;
	}

	cout << f << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}