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

// -------------------------------------------------------------------------------------------------
// Theorem 5
// Let f and t are strings such that |f| >= 0 and |t| >= 1
//
// (5.1) If f is a border of t such that |f| < L(t), then f is a border of U(t) 
// (5.2) If f is a border of U(t), then f is a border of t

// These follow directly from 3.1 and 3.2 respectively
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Corollary of Theorem 5 (C5.1)
// Let t is a non-empty string
// Then, B(t) = U(t) union B(U(t))

// Rough Proof
// Let A = U(t) union B(U(t))
// We then claim that B(t) = A
// We show that A is a subset of B(t) and vice versa. 
// The claim then follows immediately

// 1. We first show that A is a subset of B(t)
// Let f belongs to A
// Then, f is either U(t), or belongs to B(U(t))
// We show that f belongs to B(t) in either cases to establish the claim
// If f is U(t), then f is trivially a border of t and thus t belongs to B(t)
// Otherwise, if f belongs to B(U(t)), then f is a border of U(t)
// Thus 0 <= |f| < |U(t)| < |t| and since U(t) is a border t, it follows from Theorem 3.1
// that f is a border of t. Thus, t belongs to B(t)

// 2. We now show that B(t) is a subset of A
// Let f belongs to B(t) and thus is a border of t
// Then, the length of f is either L(t) or is less than L(t)
// We show that f belongs to A in either cases to establish the claim
// If |f| = L(t), then f = U(t) and thus belongs to A trivially
// Otherwise, if |f| < L(t) and f is a border of t, it follows from Theorem 5.1 that
// f is a border of U(t)
// Thus f belongs to B(U(t))
// -------------------------------------------------------------------------------------------------

// We define U("") to be "" and L("") to be 0

// For any non-empty string t, we define U[k] recursively as
// U[1](t) = U(t)
// U[k](t) = U(U[k - 1](t)) for k >= 2

// -------------------------------------------------------------------------------------------------
// Theorem 6
// Let t is a non-empty string
// Then, there exists unique k >= 1, denoted V(t), such that
// |U[i](t)| > 0 for 1 <= i < V(t) and U[V(t)](t) = ""

// Proof
// We consider two cases and show that the claim holds in both of them
// 1. Assume L(t) = 0
// Then, the claim is trivially true with k = 1

// 2. Assume L(t) != 0
// Consider the sequence |U[1](t)|, |U[2](t)|, ... 

// If U[j](t) is non-empty (for some j >= 1)
// It follows from Theorem 1 that |U[j + 1](t)| < |U[j](t)| since U[j + 1](t)
// is the longest border of the non-empty string U[j](t),
// Also, since U[j](t) is a string, it follows that |U[j](t)| >= 0
// Also, by our assumption, U[1](t) is non-empty

// It then follows that the sequence is a strictly decreasing non-negative sequence
// starting from a positive number, and thus reaches 0 in finitely many steps
// Let V(t) be the smallest such index in the sequence 
// Then, |U[1](t)| > |U[2](t)| ... > |U[V(t)](t)| = 0
// Thus, |U[i](t)| > 0 for all 1 <= i < V(t) and |U[V(t)](t)| = 0
// V(t) is unique due to it's minimality
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 7 
// Let t is a non-empty string
// Then, the sequence
// |U[1](t)|, ..., |U[V(t)](t)|
// is a strictly decreasing non-negative integral sequence
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 8
// Let t is a non-empty string
// Then, U[j](t) = U[j - 1](U(t)) for any j >= 2
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 9
// Let t is a non-empty string with L(t) > 0
// Then, V(t) = V(U(t)) + 1

// Rough Proof
// Let s = U(t)
// Now, |U[i](t)| > 0 for 1 <= i < V(t) and |U[V(t)](t)| = 0
// Since U[j](t) = U[j - 1](U(t)) = U[j - 1](s) for j >= 2, we have
// |U[i](s)| > 0 for 1 <= i < V(t) - 1 and |U[V(t) - 1](s)| = 0
// It then follows that V(s) = V(t) - 1, and thus, 
// V(t) = V(U(t)) + 1
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// Theorem 10
// Let t is a non-empty string
// Then, B(t) = {U[1](t), ..., U[V(t)](t)}

// Proof
// Let P(n) be the predicate that "for every string t of length n, the claim is true"
// for n >= 1

// We show that P(n) holds for all n >= 1 using strong induction
// The claim then follows

// Base Step (n = 1)
// Let f is any string of length n = 1
// Then the only border of f is the empty string
// Thus, U(f) = "" and hence B(f) = {""} = {U[1](f)}
// The base step is thus established

// Inductive Step 
// Let k >= 1
// Suppose that P(n) is true for 1 <= n <= k
// We show that P(k + 1) is true to establish the inductive step

// Let f is a string of length k + 1
// We show that B(f) = {U[1](f), ..., U[V(f)](f)} to prove P(k + 1)
// We consider two cases and show that it holds in both

// 1. Assume that L(f) = 0
// In this case V(f) = 1 and, the only border f has is the empty one
// Thus, B(f) = {U[V(f)](f) = ""}

// 2. Assume that L(f) != 0
// By C5.1, it follows that B(f) = U(f) union B(U(f))
// Since |U(f)| < k + 1, it follows from our assumption that P(|U(f)|) is true
// Thus, B(U(f)) = {U[1](U(f)), ..., U[V(U(f))](U(f))}
//				 = {U[2](f), ..., U[V(f)](f)}
// Thus, B(f) = {U[1](f), ..., U[V(f)](f)}

// Since both the base and inductive steps are established, it follows from the axiom
// of strong induction that P(n) is true for all n >= 1
// -------------------------------------------------------------------------------------------------

// Let s is a string of length n >= 1
// We define pi[i] = L[s[1, i]] for 1 <= i <= n

// -------------------------------------------------------------------------------------------------
// Theorem 9
// pi[i + 1] <= p[i] + 1 for 1 <= i < n

// Proof
// The theorem is trivially true for n = 1

// We prove the theorem for n >= 2 by contradiction
// Assume that p[i + 1] = c > p[i] + 1 for some 1 <= i < n
// Since p[i] = L[s[1, i]] >= 0, it follows that c >= 1

// Also, it follows that s[i + 1, i - c + 2] == s[1, c]
// -------------------------------------------------------------------------------------------------