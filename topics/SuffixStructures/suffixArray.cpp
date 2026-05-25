#include <bits/stdc++.h>
using namespace std;

#define int long long

// Let s is a string with |s| = n >= 1
// Then, any suffix of the string s can be uniquely identified by the index of
// it's starting letter in s, which is called the index of the suffix.
// For any suffix f of s, there is a unique 0 <= i < n such that f = s[i, n - 1].
// There are n suffixes of s.

// The suffix ordering of s is the lexographical ordering of all the suffixes of s.
// The suffix array of s is the suffix ordering of s, with each suffix being represented it's index.
vector<int> build_sa(string &s) {
	int n = s.length();

	// sa[i] is the index of the suffix of s with position i in the suffix ordering, for 0 <= i < n
	// rank[i] is the position of the suffix with index i in the suffix ordering, for 0 <= i < n
	// sa[rank[i]] = i for 0 <= i < n
	vector<int> sa(n), rank(n);
	for (int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i] - 'a';

	for (int k = 1; k <= n; k >>= 1) {
		// we will sort all suffixes of s using their first 2^k characters in this iteration, using
		// the ranks of these suffixes using their 2^(k - 1) characters

		// returns true if the suffix with index a < suffix with index b
		auto cmp = [&](int a, int b) {
			if (rank[a] != rank[b]) return rank[a] < rank[b];
		};
	}
}