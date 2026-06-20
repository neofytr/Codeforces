#include <bits/stdc++.h>
using namespace std;

// A string s of length n (for n >= 1) is a sequence of n characters, with the ith of them being denoted
// as s[i], for 1 <= i <= n

// The string of length 0 is defined to be ""

// Let s is a string of length n >= 1
// s[i, j] is defined to be the string s[i], ..., s[j] for 1 <= i <= j <= n, and the
// empty string for 1 <= i, j <= n such that i > j

// The prefix of s of length k, for 0 <= k <= n, is defined to be the string s[1, k]; it
// is proper iff k < n

// The suffix of s of length k, for 0 <= k <= n, is defined to be the string s[n - k + 1, n]
// ; it is proper iff k < n

// The border of length k (for 0 <= k < n) of s is said to exist iff s[1, k] == s[n - k + 1, n]
// and is the string s[1, k]

// A string t is a border of s iff |t| < |s| and the border of length |t| of s exists 
// and is equal to t

// We define
// B(s) = {t | t is a border of s}
// b(s) = {|t| such that t is a border of s}


// -------------------------------------------------------------------------------------------------
// Theorem 1
// Let t, s are strings such that |t| >= 0 and |s| >= 1
// If t is a border of s, then |t| < |s|
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 2
// For any non-empty string t, 0 ∈ b(t) and "" ∈ B(t)
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 3
// Let p, q, r are strings such that 0 <= |p| < |q| < |r|
//
// (3.1) If p is a border of q, and q is a border of r, then p is a border of r
// (3.2) If p and q are borders of r, then p is a border of q
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 4
// For any non-empty string t, the maximum of the set b(t) exists
// -------------------------------------------------------------------------------------------------

// For any non-empty string t, we define
// L(t) := max(b(t))                          -- the length of the longest border of t
// U(t) := t[1, L(t)]                         -- the longest border of t