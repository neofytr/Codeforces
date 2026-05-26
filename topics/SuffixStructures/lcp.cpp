#include <bits/stdc++.h>
using namespace std;

#define int long long

// Let s[1, n] is a string for n >= 1
// Let sa[1, n] is the suffix array of s, and let rank[1, n] is it's rank array
// Define sa[0] = n + 1 (the empty suffix)

// Define lcp(i) as the length of the longest common prefix for the suffixes with index sa[i] and sa[i - 1] for 2 <= i <= n
// Define lcp(1) = 0 (the empty suffix and sa[1] don't have any prefix in common)

// Define LCP(i, j) as the length of the longest common prefix for the suffixes with index i and j for 1 <= i, j <= n
// Let 1 <= i, j <= n such that rank[i] < rank[j]
// We then claim that LCP(i, j) = min(lcp[r] for rank[i] + 1 <= r <= rank[j])

// Proof 
// Assume that LCP(i, j) = k for some k >= 0
// Let rank[i] = ri and rank[j] = rj
// Let t = min(lcp[r] for ri + i <= r <= rj)
// We show that t >= k and t <= k. The claim then follows

// We first show that t >= k
// Since the suffix array is sorted in lexicographical order, if the suffixes sa[ri] = i and sa[rj] = j have a common
// prefix of length k, any two consecutive suffixes in the range sa[ri, rj] must have a common prefix
// of length atleast k
// Thus, lcp[r] >= k for ri + 1 <= r <= rj

// We now show that t <= k