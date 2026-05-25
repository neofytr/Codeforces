#include <bits/stdc++.h>
using namespace std;

#define int long long

// sa[i] is the suffix at index i in the suffix ordering
// rank[i] is the index of suffix i in the suffix ordering

vector<int> build_sa(string &s) {
	vector<int> sa(n), rank(n), tmp(n);

	for (int i = 0; i < n; i++) {
		sa[i] = i;  // garbage
		rank[i] = s[i] - 'a'; // ordering by the first character of the suffixes
	}

	// the invariant we maintain is that after iteration with k = j:
	// 1. sa contains the suffix ordering with respect to only the first 2 * j characters of each suffix
	// 2. rank assignes each suffix it's ordering rank with respect to only the first 2 * j characters of each suffix

	for (int k = 1; k < n; k <<= 1) {
		// returns true if suffix a < suffix b using only the first 2 * k characters of the suffixes
		auto cmp = [&](int a, int b){
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
		swap(rank, tmp);
	} 
	return sa;
}