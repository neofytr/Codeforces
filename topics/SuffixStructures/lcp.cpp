#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

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
// Let LCP(i, j) = k

// Lemma 1:
// For any r in the range sa[ri, rj], the suffix S[r] has in common with suffixes S[i] and S[j] a prefix of length
// atleast k

// Proof 1:
// The lemma is trivial for r = sa[ri] = i and r = sa[rj] = j. So, we prove it for r in the range sa[ri + 1, rj - 1] (if possible)
// We prove the lemma via contradiction
// Assume that the lemma is false. Thus, there is an r in the range sa[ri + 1, rj - 1] such that S[r] has in common with atleast one
// of the suffixes S[i] or S[j], a prefix of length exactly p < k
// Without a loss in generality, we can assume that there is an r in the range sa[ri + 1, rj - 1] such that
// S[r] has in common with suffix S[i] a prefix of length exactly p < k

// Now, since the suffix array is sorted in lexicographical order, we have
// 					S[i] < S[r] < S[j]

// Since S[i] and S[r] have their first p characters equal, it then follows from lexicographical ordering that
// 					s[i + p] < s[r + p]

// Also, LCP(i, j) = k > p, it follows that s[i + p] = s[j + p], and thus s[j + p] < s[r + p]
// Now, since S[i] and S[r] have their first p characters equal, and LCP(i, j) = k > p, it follows that
// S[j] and S[r] have their first p characters common
// Then, since s[j + p] < s[r + p], it follows that S[j] < S[r], which is a contradiction to the fact that S[r] < S[j]


// Lemma 2:
// There is some ri + 1 <= r <= rj such that lcp[r] <= k

// Proof 2:
// We prove the lemma via contradiction
// Assume that the lemma is false, i.e, for any ri + 1 <= r <= rj, we have lcp[r] > k
// Thus, the suffixes S[sa[r]] and S[sa[r - 1]] have in common a prefix of length > k for ri + 1 <= r <= rj
// It then follows from transitivity that S[sa[ri]] = S[i] and S[sa[rj]] = S[j] have in common a prefix of length > k
// This is a contradiction to the fact that the length of the longest common prefix of S[i] and S[j] is k, i.e, LCP(i, j) = k

// Theorem
// LCP(i, j) = min(lcp[r] for rank[i] + 1 <= r <= rank[j])

// Proof:
// Let t = min(lcp[r] for ri + 1 <= r <= rj)
// We show that t <= k and t >= k. The theorem then follows.

// Using lemma 1, we conclude that all suffixes S[sa[r]] for ri + 1 <= r <= rj have in common a prefix of length atleast k
// Thus, lcp[r] >= k for any ri + 1 <= r <= rj, and thus t >= k

// Also, using lemma 2, we conclude that there is a ri + 1 <= b <= rj such that lcp[b] <= k
// Thus, since t <= lcp[b], it follows that t <= k

int tree[4 * MAX + 1];
void build(vector<int> &lcp, int l, int r, int idx) {

}