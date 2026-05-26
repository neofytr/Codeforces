#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s, t; cin >> s >> t;
	int len_s = s.length(), len_t = t.length(); 
	s.push_back('#');
	for (int i = 0; i < t.length(); i++)
		s.push_back(t[i]);

	int n = s.length();
	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1);
	for (int i = 1; i <= n; i++)
		sa[i] = i, rank[i] = s[i - 1] - 'a' + 1;
	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
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

	int h = 0;
	vector<int> lcp(n + 1);
	for (int i = 1; i <= n; i++) {
		if (rank[i] == 1) {
			lcp[rank[i]] = h = 0;
			continue;
		}

		int j = sa[rank[i] - 1];
		while (i + h <= n && j + h <= n && s[i + h - 1] == s[j + h - 1])
			h++;
		lcp[rank[i]] = h;
		if (h) 
			h--;
	}

	int maxi = 0;
	for (int i = 2; i <= n; i++) {
		int one = sa[i], two = sa[i - 1];
		if ((one <= len_s && two <= len_s) || (one >= len_s + 1 && two >= len_s + 1))
			continue;
		maxi = max(maxi, lcp[i]);
	}

	for (int i = 2; i <= n; i++) {
		int one = sa[i], two = sa[i - 1];
		if ((one <= len_s && two <= len_s) || (one >= len_s + 2 && two >= len_s + 2))
			continue;

		if (lcp[i] == maxi) {
			cout << s.substr(one - 1, maxi) << endl;
			return 0;
		}
	}

	cout << "" << endl;
	return 0;
}