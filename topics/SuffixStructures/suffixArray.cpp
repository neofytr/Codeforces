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
	vector<int> sa(n), rank(n), tmp(n);

	// initially, every suffix is ranked only using it's first character
	// so rank[i] is simply the character value of s[i]
	// initially, the suffix ordering is unknown, so sa = [0,1,2,...,n-1]
	for (int i = 0; i < n; i++)
		sa[i] = i, rank[i] = s[i] - 'a';

	// the invariant we maintain is that after iteration with k = j:
	// 1. sa contains the suffix ordering with respect to only the first 2 * j characters of each suffix
	// 2. rank assignes each suffix it's ordering rank with respect to only the first 2 * j characters of each suffix

	// after every iteration:
	// rank[i] correctly stores the rank of the suffix starting at i
	// considering only it's first k characters
	//
	// then, using these ranks, we construct ranks for first 2k characters
	//
	// k doubles every iteration:
	// 1 -> 2 -> 4 -> 8 -> ...
	for (int k = 1; k < n; k <<= 1) {

		// we will sort all suffixes of s using their first 2k characters in this iteration
		// every substring of length 2k can be split into:
		// [first k chars][next k chars]

		// since rank[] already correctly stores ordering of substrings of length k,
		// we can compare suffixes using only:
		// (rank of first half, rank of second half)
		// instead of comparing actual strings

		// returns true if the suffix with index a < suffix with index b
		auto cmp = [&](int a, int b) {

			// compare first halves
			// if they differ, we already know the answer
			if (rank[a] != rank[b])
				return rank[a] < rank[b];
			// otherwise compare second halves

			// rank[a + k] represents the next k characters after the first half
			// if a + k >= n, then the suffix has no second half

			// we use -1 because:
			// empty string < every non-empty string lexographically
			// this correctly handles cases like:
			// "a" < "aa"
			int ra = (a + k < n ? rank[a + k] : -1);
			int rb = (b + k < n ? rank[b + k] : -1);

			return ra < rb;
		};

		// sort suffix indices using the comparator above
		// after sorting:
		// sa[0] = index of smallest suffix
		// sa[1] = index of second smallest suffix
		// ...
		// this ordering is done using only first 2k characters of each suffix
		sort(sa.begin(), sa.end(), cmp);

		// now we assign new compressed ranks
		// smallest suffix gets rank 0
		tmp[sa[0]] = 0;

		for (int i = 1; i < n; i++) {

			// if previous suffix < current suffix,
			// then current suffix gets a new rank
			// otherwise they are equal and share same rank

			// cmp(sa[i - 1], sa[i]) is:
			// 1 if different
			// 0 if equal
			tmp[sa[i]] =
				tmp[sa[i - 1]] +
				cmp(sa[i - 1], sa[i]);
		}

		// update ranks
		// now:
		// rank[i] correctly stores ordering of first 2k characters
		swap(rank, tmp);
	}

	// eventually k >= n
	// at that point, every suffix has been fully compared,
	// so sa becomes the complete suffix ordering

	// At the end, necessarily, the rank[i], i.e., the rank of each suffix i must be unique, since each
	// of the suffixes i differ from each other (atleast in length).
	// We can stop thus the algorithm prematurely when this condition is met, and we'll have the correct suffix array.

	// Time Complexity O(n log^2(n))
	// Space Complexity O(n) 
	return sa;
}