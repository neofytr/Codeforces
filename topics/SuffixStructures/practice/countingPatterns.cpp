#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s; cin >> s;
	int n = length();

	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1);
	for (int i = 1; i <= n; i++)
		sa[i] = i, rank[i] = s[i - 1] - 'a' + 1;
	for (int i = 1; i <= n; i++) {
		auto cmp = [&] (int a, int b) {
			if (rank[a] != rank[b])
				return rank[a] < rank[b];
			int ra = (a + k <= n ? rank[a + k] : 0);
			int rb = (b + k <= n ? rank[b + k] : 0);
			return ra < rb;
		};

		sort(sa.begin() + 1, sa.end(), cmp);
		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(rank, tmp);

		if (rank[sa[n]] == n)
			break;
	}

	string t;
	int k; cin >> k;
	while (k--) {
		cin >> t;
		int left = 1;
		int right = n;

		int first = -1;
		int len = t.length();
		while (left <= right) {
			int m = left + ((right - left) >> 1);
			int i = sa[m];
			if (t < s)
		}
	}
	return 0;
}