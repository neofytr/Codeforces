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

// A border of s, of length 0 <= k < n, if it exists, is unique
// This is true since a border of length k of s, if it exists, is the prefix s[1, k], and
// all the prefixes of a string are distinct (atleast in length)

// We define the set 
//			b(s) = {k such that 0 <= k < n and s[1, k] = s[n - k + 1, n]}
// to be the set of border lengths of s

// We define the set
// 			B(s) = {s[1, k] for k in b(s)}
// to be the border set of s

// The empty string (length 0) is in B(s)

// --------------------------------------------------------------------------------------------------------

// The Nested-Borders Lemma
// Let s[1, n] is a string for n >= 1

// 1.1 If a string p is a border of s, and a string q is a border of p, then q is a border of s
// Proof
// Let p is a border of s, and let q is a border of p
// We then claim that q is a border of s. We give a direct proof of the claim

// Let |p| = i, and |q| = j
// Then, n > i > j by our assumption
// Also, by definition of border strings, there exist  0 <= k1 < n, 0 <= k2 < i such that

// p = s[1, k1] = s[n - k1 + 1, n] and q = p[1, k2] = p[i - k2 + 1, i]
// Now, since p = s[1, k1] and q = p[1, k2], it follows that k2 < k1, and that q = s[1, k2]
// It also follows from p = s[1, k1] that i = k1 - 1 + 1 = k1
// Thus, it follows from q = p[i - k2 + 1, i] = p[k1 - k2 + 1, k1]
// We can then conclude from p = s[n - k1 + 1, n] that q = s[n - k2 + 1, n]

// Thus, q = s[1, k2] = s[n - k1 + 1, n], from which the claim follows.

// 1.2 If strings p and q are borders of string s such that |q| < |p|, then q is a border of p
// Proof
// Let p and q are borders of s such that |q| = i < |p| = j
// We then claim that q is a border of p. We give a direct proof of the claim
// It follows from the definition of borders that there exist
// 			0 <= k1 < n and 0 <= k2 < n such that
//				p = s[1, k1] = s[n - k1 + 1, n], and
//				q = s[1, k2] = s[n - k2 + 1, n]

// Also, since i < j, it follows that k2 < k1
// It then follows from p = s[1, k1] and q = s[1, k2] that q = p[1, k2]
// Similarly, we can conclude from p = s[n - k1 + 1, n] and q = s[n - k2 + 1, n] that 
// q = p[n - k2 + 1, n]

// Thus, q = p[1, k2] = p[n - k2 + 1, n], from which the claim follows directly

// --------------------------------------------------------------------------------------------------------

// The Prefix Function

// Let s[1, n] is a string for n >= 1
// We define the prefix function of s, p: [1, n] -> W such that
//	 p(i) = max {k such that 0 <= k < i and s[1, k] == s[i - k + 1, i]} for 1 <= i <= n
// Since the empty string (k = 0) always works and k is bounded in [0, i), the maximum of this set always exists

// We define the prefix function array p[1, n] of s as p[i] = p(i) for 1 <= i <= n
// Thus, p[i] is the length of the longest proper border of the prefix s[1, i] for 1 <= i <= n
// Equivalently, p[i] = max(B(s[1, i])) for 1 <= i <= n

// p[1] = 0 (the empty string is the only solution)

// For 1 <= i <= n, the following properties hold:
// 1. 0 <= p[i] < i
// 2. p[1] = 0
// 3. p[i] = k implies s[1, k] == s[i - k + 1, i]

// We define the function pi(s): [1, |s|] -> J
// 		pi(s)[j] = s[1, p(j)] for 1 <= j <= |s|
// for some string s, where p is the prefix function of s, and J is the set of all the
// strings over the alphabet the string s is made from

// --------------------------------------------------------------------------------------------------------

// The Border Structure Theorem


