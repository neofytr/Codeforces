#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MAX (int)(4 * 1e5)
#define INF (int)(1e17)

int tree[4 * MAX + 1];
int lcp[MAX + 1], rnk[MAX + 1], sa[MAX + 1], tmp[MAX + 1];
pair<int, int> p[MAX + 1];
int n;
void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = lcp[l];
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
}

int query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || qr < l) 
		return INF;
	if (l >= ql && r <= qr)
		return tree[idx];
	int m = (l + r) >> 1;
	return min(query(ql, qr, l, m, idx << 1), query(ql, qr, m + 1, r, (idx << 1) | 1)); 
}

int LCP(int i, int j) {
	if (i == j)
		return n - i + 1;
	if (rnk[i] > rnk[j])
		swap(i, j);
	return query(rnk[i] + 1, rnk[j], 1, n, 1);
}

int32_t main() {
	string s; cin >> s;
	n = s.length();

	int m; cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> p[i].first >> p[i].second;

	for (int i = 1; i <= n; i++)
		sa[i] = i, rnk[i] = s[i - 1] - 33 + 1;
	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
			if (rnk[a] != rnk[b])
				return rnk[a] < rnk[b];
			int ra = (a + k <= n ? rnk[a + k] : 0);
			int rb = (b + k <= n ? rnk[b + k] : 0);
			return ra < rb;
		};

		sort(sa + 1, sa + n + 1, cmp);
		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(tmp, rnk);

		if (rnk[sa[n]] == n)
			break;
	}

	int h = 0;
	for (int i = 1; i <= n; i++) {
		if (rnk[i] == 1) {
			lcp[rnk[i]] = h = 0;
			continue;
		}

		int j = sa[rnk[i] - 1];
		while (i + h <= n && j + h <= n && s[i + h - 1] == s[j + h - 1])
			h++;
		lcp[rnk[i]] = h;
		if (h)
			h--;
	}

	build(1, n, 1);
	auto cmp = [&](auto &one, auto &two) {
		auto [l1, r1] = one;
		auto [l2, r2] = two;
	
		int len1 = r1 - l1 + 1;
		int len2 = r2 - l2 + 1;

		int a = LCP(l1, l2);
		if (a >= min(len1, len2)) {
			if (len1 != len2)
				return len1 < len2;
			if (l1 != l2)
				return l1 < l2;
			return r1 < r2;
		}
		return s[l1 + a - 1] < s[l2 + a - 1];
	};

	sort(p + 1, p + m + 1, cmp);
	for (int i = 1; i <= m; i++)
		cout << p[i].first << " " << p[i].second << endl;
	return 0;
}