#include <bits/stdc++.h>
using namespace std;

vector<int> build_sa(string &s) {
	int n = s.length();
	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1), t(n + 1), cnt(n + 1);

	vector<int> f(26 + 1, 0);
	for (int i = 1; i <= n; i++)
		f[s[i - 1] - 'a' + 1]++;
	for (int i = 1; i <= 26; i++)
		f[i] += f[i - 1];
	for (int i = n; i >= 1; i--) {
		int c = s[i - 1] - 'a' + 1;
		sa[f[c]--] = i;
	}

	rank[sa[1]] = 1;
	for (int i = 2; i <= n; i++)
		rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i] - 1] != s[sa[i - 1] - 1]);

	auto cmp = [&] (int a, int b, int k) {
		if (rank[a] != rank[b]) 
			return rank[a] < rank[b];
		int ra = (a + k <= n ? rank[a + k] : 0);
		int rb = (b + k <= n ? rank[b + k] : 0);
		return ra < rb;
	};

	for (int k = 1; k < n; k <<= 1) {
		int ptr = 1;
		for (int i = n - k + 1; i <= n; i++)
			t[ptr++] = i;

		for (int i = 1; i <= n; i++)
			if (sa[i] - k >= 1)
				t[ptr++] = sa[i] - k;

		fill(cnt.begin(), cnt.end(), 0);
		for (int i = 1; i <= n; i++)
			cnt[rank[t[i]]]++;
		for (int i = 1; i <= n; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) {
			int c = rank[t[i]];
			sa[cnt[c]--] = t[i];
		}

		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i], k);
		swap(tmp, rank);

		if (rank[sa[n]] == n)
			break;
	}
	sa[0] = n + 1;
	return sa;
}

int32_t main() {
	string s; cin >> s;
	vector<int> v =  build_sa(s);
	for (int e : v)
		cout << e - 1 << " ";
	cout << endl;
	return 0;
}