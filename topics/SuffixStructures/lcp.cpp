#include <bits/stdc++.h>
using namespace std;

#define int long long

// Let s[1, n] is a string for some n >= 1

// Define S[i] = s[i, n] for 1 <= i <= n
// Define S[n + 1] = "" (the empty suffix)
// The suffix with index i is S[i] for 1 <= i <= n

// Let sa[1, n] is the suffix array of s
// Define sa[0] = n + 1 (to denote the empty suffix)

// Let rank[1, n] is the rank array of s
// Define rank[n + 1] = 0 (to denote the empty suffix)

// Define LCP(i, j) to be the length of the longest common prefix of S[i] and S[j] for 1 <= i, j <= n
// Define lcp[1, n] to be an array such that lcp[i] = LCP(sa[i], sa[i - 1]) for 1 <= i <= n

// Let 1 <= i, j <= n such that rank[i] < rank[j]
// Let ri = rank[i], and rj = rank[j]

// Lemma 1:
// For any r in the range sa[ri, rj], the suffix S[r] has in common with suffixes S[i] and S[j] a prefix of length
// atleast k

// Proof 1:
// The lemma is trivial for r = sa[ri] = i and r = sa[rj] = j. So, we prove it for r in the range sa[ri + 1, rj - 1] (if possible)
// We prove the lemma via contradiction
// Assume that the lemma is false. Thus, there is an r in the range sa[ri + 1, rj - 1] such that S[r] has in common with suffixes S[i]
// and S[j] a prefix of length p < k

// Since the suffix array is sorted in lexicographical order, we have:
// 			S[i] < S[r] < S[j]

// Now, since S[i] and S[r] have their first p characters common, it then follows from lexicographical ordering that s[i + p] < s[r + p]
// Similarly, we have s[r + p] < s[j + p]
// Thus, we conclude that s[i + p] < s[j + p]
// Since p < k, this is a contradiction to the fact that the first k characters of S[i] and S[j] are equal (because
// LCP(i, j) = k)

// Lemma 2:
// There is some ri + 1 <= r <= rj such that lcp[rank[r]] <= k

// Proof 2:
// We prove the lemma via contradiction
// Assume that the lemma is false, i.e, for any r in the range sa[ri + 1, rj] we have lcp[rank[r]] > k
// Thus, for any r in the range sa[ri + 1, rj], the suffixes S[r] and S[r - 1] have in common a prefix of length > k
// It then follows using transitivity that suffixes S[sa[ri]] = S[i] and S[sa[rj]] = S[j] have in common a prefix of
// length > k
// This is a contradiction to the fact that the longest common prefix of the suffixes S[i] and S[j] is k
