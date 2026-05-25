#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<int> sa(n), rank(n), tmp(n);
	for (int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i] - 'a';

	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
			if (rank[a] != rank[b]) return rank[a] < rank[b];
			int ra = (a + k < n ? rank[a + k] : -1);
			int rb = (b + k < n ? rank[b + k] : -1);
			return ra < rb;
		};
		sort(sa.begin(), sa.end(), cmp);
		tmp[sa[0]] = 0;
		for (int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(tmp, rank);
	}

	cout << s.length() << " ";
	for (int e : sa) cout << e << " ";
	cout << endl;
	return 0;
}