// ============================================================================
// NOTATION
// ============================================================================
//
// Let s be a 1-indexed string of length n >= 0.
//   - s[1], s[2], ..., s[n] are the characters.
//   - s[i..j] denotes the substring from index i to j inclusive;
//     it is the empty string "" if i > j.
//   - |s| = n.
//   - "" denotes the empty string; |""| = 0.
//   - s . t denotes concatenation.
//
// Prefix:  for 0 <= i <= n, s[1..i] is a prefix of s; proper if i < n.
// Suffix:  for 0 <= i <= n, s[n-i+1..n] is a suffix of s; proper if i < n.
//
// Border of s: a string t that is both a proper prefix and a proper suffix
//              of s.
//
// We use the convention B("") = {""} and b("") = {0}.
//
// ============================================================================
// THEOREM 1.  If t is a border of s, then |t| < |s|.
// ============================================================================
//
// Proof.
// By definition a border is a proper prefix.  A proper prefix has length
// strictly less than the length of the whole string.  QED.
//
// ============================================================================
// DEFINITIONS.
//   B(s) = { t : t is a border of s }  ∪  {""}
//   b(s) = { |t| : t ∈ B(s) }
// ============================================================================
//
// ============================================================================
// THEOREM 2.  For every string t, "" ∈ B(t) and 0 ∈ b(t).
// ============================================================================
//
// Proof.
//   Case 1: t = "".  By convention B("") = {""}, so "" ∈ B("").
//   Case 2: t ≠ "".  The empty string equals t[1..0], which is a prefix of t
//           of length 0 < |t|, hence a proper prefix.  Likewise it equals
//           t[|t|+1..|t|] interpreted as empty, hence a proper suffix.  So
//           "" is a border of t, i.e., "" ∈ B(t).
//   In both cases 0 = |""| ∈ b(t).  QED.
//
// ============================================================================
// THEOREM 3 (NESTED BORDERS).  Let t be any string, a a non-empty border of
// t, and c a border of a.  Then c is a border of t.
// ============================================================================
//
// Proof.
// Let |t| = n, |a| = k, |c| = j with 0 <= j < k < n.
//
// (i)  c is a prefix of a, and a is a prefix of t, so c is a prefix of t.
//      Since j < n, c is a proper prefix of t.
// (ii) c is a suffix of a, and a is a suffix of t, so c is a suffix of t.
//      Since j < n, c is a proper suffix of t.
//
// Hence c is a border of t.  QED.
//
// ============================================================================
// THEOREM 4.  For every string t, the set b(t) has a maximum element.
// ============================================================================
//
// Proof.
// By Theorem 2, b(t) is non-empty (it contains 0).  By Theorem 1, every
// element of b(t) is at most |t| - 1 (or 0 when t = "").  So b(t) is a
// non-empty finite subset of N, which has a maximum.  QED.
//
// ============================================================================
// DEFINITIONS.
//   L(t) := max(b(t))                  -- length of the longest border
//   U(t) := t[1..L(t)]                 -- the longest border itself
// ============================================================================
// Note: L("") = 0, U("") = "".
//
// ============================================================================
// THEOREM 5 (BORDER RESTRICTION).
// (Forward)   If f is a border of t with |f| < L(t), then f is a border of
//             U(t).
// (Reverse)   If f is a border of U(t), then f is a border of t.
// ============================================================================
//
// Proof.  Let n = |t|, b = L(t), k = |f|.
//
// (Forward) Assume f is a border of t with k < b.
//
//   Since f is a border of t:    f = t[1..k] = t[n-k+1..n].          ...(A)
//   Since U(t) is a border of t: U(t) = t[1..b] = t[n-b+1..n].        ...(B)
//
//   From (B), for every index j ∈ [1, b]:   t[j] = t[n-b+j].
//   Restricting to j ∈ [b-k+1, b]:          t[b-k+1..b] = t[n-k+1..n].
//
//   Combining with (A):
//         t[1..k]  =  t[n-k+1..n]  =  t[b-k+1..b].
//
//   i.e., (U(t))[1..k] = (U(t))[b-k+1..b], so f is a border of U(t).
//
// (Reverse) Assume f is a border of U(t).
//   If U(t) = "", then B(U(t)) = {""}, so f = "", which is a border of t
//     by Theorem 2.
//   If U(t) ≠ "", apply Theorem 3 with a := U(t) (a non-empty border of t)
//     and c := f.  Conclude f is a border of t.
// QED.
//
// ============================================================================
// COROLLARY (of Theorem 5).  For every string t,
//
//     B(t)  =  { U(t) }  ∪  B(U(t)).
//
// (When t = "", U(t) = "" and B(U(t)) = {""}, so the RHS is {""} = B("").)
// ============================================================================
//
// Proof.
// (⊆)  Let f ∈ B(t).  Then |f| ∈ b(t), so |f| <= L(t).
//   - If |f| = L(t):   f = t[1..L(t)] = U(t), so f ∈ {U(t)}.
//   - If |f| <  L(t):  by Theorem 5 (forward), f ∈ B(U(t)).
// (⊇)  Let f ∈ {U(t)} ∪ B(U(t)).
//   - If f = U(t):     U(t) is the longest border of t, so f ∈ B(t).
//   - If f ∈ B(U(t)):  by Theorem 5 (reverse), f ∈ B(t).
// QED.
//
// ============================================================================
// RECURSIVE DEFINITION OF U^k.
//   U^1(t) = U(t)
//   U^k(t) = U(U^(k-1)(t))   for k >= 2.
// ============================================================================
//
// ============================================================================
// THEOREM 6.  For every string t, there exists a unique smallest k >= 1,
// denoted V(t), such that U^k(t) = "".  Equivalently:
//   1.  |U^i(t)| > 0  for all  1 <= i < V(t),
//   2.  U^i(t) = ""   for all  i >= V(t).
// ============================================================================
//
// Proof.
// Claim A: U("") = "".
//   B("") = {""} by convention, so L("") = 0 and U("") = ""[1..0] = "".
//
// Claim B: For any non-empty string s, |U(s)| < |s|.
//   U(s) is a border of s; by Theorem 1, |U(s)| < |s|.
//
// Consider the sequence |U^1(t)|, |U^2(t)|, .... While U^i(t) is non-empty,
// Claim B gives |U^(i+1)(t)| < |U^i(t)|.  Since these are non-negative
// integers, the sequence must reach 0 in finitely many steps.  Let V(t) be
// the smallest such index.  Then:
//   - For 1 <= i < V(t), U^i(t) is non-empty (by minimality of V(t)).
//   - U^(V(t))(t) = "".
//   - For i >= V(t), U^i(t) = U^(i - V(t))("") = "" by Claim A.
// V(t) is unique by being the smallest positive integer with U^k(t) = "".
// QED.
//
// ============================================================================
// THEOREM 7.  For every non-empty string t WITH L(t) > 0,
//
//     V(t)  =  1 + V(U(t)).
//
// (The hypothesis L(t) > 0 is essential.  When L(t) = 0, V(t) = 1 but
// V(U(t)) = V("") = 1, so the recurrence would give 2.)
// ============================================================================
//
// Proof.
// Define a(k) = U^k(t) and r(k) = U^k(U(t)) for k >= 1.
//
// Claim: a(k + 1) = r(k) for all k >= 1.
//   Induction on k.
//     Base k = 1:  a(2) = U(U^1(t)) = U(U(t)) = r(1).
//     Step:        a(k+2) = U(a(k+1)) = U(r(k)) = r(k+1).
//
// Now:
//   V(t)  = min { k >= 1 : a(k) = "" }.
//
// Since L(t) > 0, a(1) = U(t) ≠ "", so the minimizing k is >= 2.  Writing
// k = j + 1 with j >= 1:
//   V(t)  = 1 + min { j >= 1 : a(j+1) = "" }
//         = 1 + min { j >= 1 : r(j)   = "" }       (by the claim)
//         = 1 + V(U(t)).
// QED.
//
// ============================================================================
// THEOREM 8.  The sequence  |U^1(t)|, |U^2(t)|, ..., |U^(V(t))(t)|  is
// strictly decreasing, with last term equal to 0.
// ============================================================================
//
// Proof.
// For 1 <= i < V(t), U^i(t) is non-empty, so by Claim B in Theorem 6's proof,
// |U(U^i(t))| < |U^i(t)|, i.e., |U^(i+1)(t)| < |U^i(t)|.  This gives strict
// decrease.  Finally, |U^(V(t))(t)| = |""| = 0.  QED.
//
// ============================================================================
// THEOREM 9 (THE BORDER-CHAIN THEOREM).  For every string t,
//
//     B(t)  =  { U^1(t), U^2(t), ..., U^(V(t))(t) }.
// ============================================================================
//
// Proof.  Strong induction on n = |t|.
//
// Let P(n) be the proposition
//   "For every string t with |t| = n, B(t) = {U^1(t), ..., U^(V(t))(t)}."
//
// Base case (n = 0):
//   The only string is "".  V("") = 1, U^1("") = "".  So the RHS is {""}.
//   By convention B("") = {""}.  Equal.  ✓
//
// Inductive step:
//   Fix n >= 1.  Assume P(m) holds for all m < n.  Let t have |t| = n.
//
//   Case (a): L(t) = 0.
//     Then U(t) = "" and U^1(t) = "", so V(t) = 1 and the RHS is {""}.
//     Since L(t) = 0, t has no non-empty border; combined with Theorem 2,
//     B(t) = {""}.  Equal.  ✓
//
//   Case (b): L(t) > 0.
//     By the Corollary to Theorem 5:
//         B(t)  =  { U(t) }  ∪  B(U(t)).
//
//     Since |U(t)| < |t| = n, the inductive hypothesis gives:
//         B(U(t))  =  { U^1(U(t)), U^2(U(t)), ..., U^(V(U(t)))(U(t)) }.
//
//     By the identity U^k(U(t)) = U^(k+1)(t) (Claim in Theorem 7):
//         B(U(t))  =  { U^2(t), U^3(t), ..., U^(V(U(t)) + 1)(t) }
//                  =  { U^2(t), U^3(t), ..., U^(V(t))(t) }
//                                                 (Theorem 7: V(t) = V(U(t))+1)
//
//     Therefore
//         B(t)  =  { U(t) }  ∪  { U^2(t), ..., U^(V(t))(t) }
//               =  { U^1(t), U^2(t), ..., U^(V(t))(t) }.
//     ✓
// QED.
//
// ============================================================================
// THEOREM 10 (MONOTONICITY).  Let s have length n >= 2.  Define
//   pi[i] := L(s[1..i])    for 1 <= i <= n.
// Then for every i with 1 <= i < n,
//     pi[i+1]  <=  pi[i] + 1.
// ============================================================================
//
// Proof.
// Suppose, for contradiction, pi[i+1] = c with c > pi[i] + 1.
//
// Since pi[i+1] = c, the prefix s[1..c] is a border of s[1..i+1]:
//     s[1..c]  =  s[(i+1)-c+1 .. i+1]  =  s[i-c+2 .. i+1].
//
// Drop the last character from both sides:
//     s[1..c-1]  =  s[i-c+2 .. i].
//
// The right side is the suffix of s[1..i] of length c-1.  So s[1..c-1] is
// a proper border of s[1..i] of length c-1.  Hence c-1 ∈ b(s[1..i]), i.e.,
// c - 1 <= pi[i].  So c <= pi[i] + 1, contradicting c > pi[i] + 1.  QED.
//
// ============================================================================
// COROLLARY (used to argue O(n) linearity in the algorithm).
//   The total positive growth of pi over i = 1, 2, ..., n is at most n - 1.
// ============================================================================
//
// Proof.
// pi[1] = 0 and pi[i] <= i - 1 <= n - 1 for all i.  By Theorem 10,
// pi[i+1] - pi[i] <= 1.  The sum of (pi[i+1] - pi[i]) telescopes to
// pi[n] - pi[1] = pi[n] - 0 <= n - 1.  Hence the total positive growth
// (climbs of +1) is at most (n - 1) plus the total drops.  The amortized
// argument from Lesson 5 will use this telescoping to bound total work.  QED.
