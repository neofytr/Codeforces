#include <bits/stdc++.h>
using namespace std;

int main() {
	string t; cin >> t;
	int n = t.length();
	vector<int> sa(n), rank(n), tmp(n);
	for (int i = 0; i < n; i++)
		sa[i] = i, rank[i] = t[i] - 'a';

	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
			if (rank[a] != rank[b])
				return rank[a] < rank[b];

			int ra = (a + k < n ? rank[a + k] : -1);
			int rb = (b + k < n ? rank[b + k] : -1);
			return ra < rb;
		};

		sort(sa.begin(), sa.end(), cmp);
		tmp[sa[0]] = 0;
		for (int i = 1; i < n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(tmp, rank);
		if (rank[sa[n - 1]] == n - 1)
			break;
	}

	string s;
	int q; cin >> q;
	while (q--) {
		cin >> s;
		int l = s.length();
		int left = 0;
		int right = n - 1;

		int first = -1;
		while (left <= right) {
			int m = left + ((right - left) >> 1);
			int i = sa[m];
			if (t.substr(i, l) < s)
				left = m + 1;
			else if (t.substr(i, l) > s)
				right = m - 1;
			else {
				first = m;
				right = m - 1;
			}
		}
		if (first == -1) {
			cout << 0 << endl;
			continue;
		}

		left = 0; right = n - 1;
		int last = -1;
		while (left <= right) {
			int m = left + ((right - left) >> 1);
			int i = sa[m];
			if (t.substr(i, l) < s)
				left = m + 1;
			else if (t.substr(i, l) > s)
				right = m - 1;
			else {
				last = m;
				left = m + 1;
			}
		}

		cout << last - first + 1 << endl;
	}
	return 0;
}