#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> build_sa(string &s) {
	int n = s.length();

	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1);
	vector<pair<char, int>> vals;
	for (int i = 1; i <= n; i++)
		vals.push_back({s[i - 1], i});
	sort(vals.begin(), vals.end());

	int r = 1;
	rank[vals[0].second] = r;
	for (int i = 1; i < n; i++) {
		if (vals[i].first != vals[i - 1].first)
			r++;
		rank[vals[i].second] = r;
	}

	for (int i = 0; i < n; i++)
		sa[i + 1] = vals[i].second;

	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
			if (rank[a] != rank[b])
				return rank[a] < rank[b];

			int ra = (a + k <= n ? rank[a + k] : 0);
			int rb = (b + k <= n ? rank[b + k] : 0);
			return ra < rb;
		};

		vector<int> cntrank(n + 1, 0), startrank(n + 1, 0);
		for (int suf = 1; suf <= n; suf++)
			cntrank[((suf + k <= n) ? rank[suf + k] : 0)]++;

		startrank[0] = 1;
		for (int r = 1; r <= n; r++)
			startrank[r] = startrank[r - 1] + cntrank[r - 1];

		for (int suf = 1; suf <= n; suf++) {
			int r = (suf + k <= n ? rank[suf + k] : 0);
			sa[startrank[r]++] = suf;
		}

		for (int i = 0; i <= n; i++) 
			cntrank[i] = startrank[i] = 0;

		for (int i = 1; i <= n; i++) {
			int suf = sa[i];
			cntrank[rank[suf]]++;
		}

		startrank[0] = 1;
		for (int r = 1; r <= n; r++)
			startrank[r] = startrank[r - 1] + cntrank[r - 1];
		for (int i = 1; i <= n; i++) {
			int suf = sa[i]; int r = rank[suf];
			tmp[startrank[r]++] = suf;
		}
		swap(tmp, sa);

		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(tmp, rank);
	}

	sa[0] = n;
	for (int i = 1; i <= n; i++) --sa[i];
	return sa;
}

int32_t main() {
	string s; cin >> s;
	for (int e : build_sa(s))
		cout << e << " ";
	cout << endl;
	return 0;
}