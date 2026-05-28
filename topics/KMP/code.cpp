#include <bits/stdc++.h>
using namespace std;

#define int long long

// Let s[1, n] is a string of length n >= 1

// s[i, j] represents the substring (s[i], s[i + 1], .., s[j]) of s for 1 <= i <= j <= n
// s[i, j] is defined as the empty string (e) for 1 <= i, j <= n such that i > j

// The prefix of length k of s is the string s[1, k] for 0 <= k <= n; It is proper iff k < n
// The suffix of length k of is the string s[n - k + 1, n] for 0 <= k <= n; It is proper iff k < n

// Thus, s has n + 1 prefixes, out of which n are proper, out of which n - 1 are non-empty
// and proper. Similarly, s has n + 1 suffixes, out of which n are proper, out of which n - 1
// are non-empty and proper.
 
// A border of s is a string f that is both a proper suffix and proper prefix of s
// Equivalently, a string f is a border of s iff there is a 0 <= k < n such that
// 				   f = s[1, k] = s[n - k + 1, n]

// We define the set 
//			B(s) = {k such that 0 <= k < n and s[1, k] = s[n - k + 1, n]}
// to be the set of border lengths of s

// The empty string (length 0) is in B(s)