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
// Then, B(t) = {U[1](t), ..., U[V(t)](t)} and
// |U[1](t)| > |U[2](t)| > ... > |U[V(t)](t)|

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
// Dropping the last characters from both substrings (this is valid since c >= 1), we get
// s[i, i - c + 2] == s[1, c - 1]

// From this we conclude that s[1, c - 1] is a border of s[1, i] and thus c - 1 <= L(s[1, i]) = pi[i]
// and thus pi[i + 1] <= pi[i] + 1 which is a contradiction to our assumption
// -------------------------------------------------------------------------------------------------

// Computing the prefix array
vector<int> prefix(const string &s) {
	int n = s.length();
	vector<int> p(n + 1);

	p[1] = 0;
	int j = p[1];
	for (int i = 2; i <= n; i++) {
		// we want p[i], the length of the largest border of s[1, i]
		// every non-empty border of s[1, i] without the last character is a border
		// of s[1, i - 1]; and conversely, every border of s[1, i - 1] can be a border
		// of s[1, i] if s[i] and the next character of the border match

		// so, we iterate in decreasing order through all the borders of s[1, i - 1]
		// and try to find the first one whose next character matches with s[i]
		while (j > 0 && s[j + 1 - 1] != s[i - 1]) 
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}

	// Time Complexity Analysis:
    // j counts the current matched border length.
    // j >= 0 throughout (the while loop stops before j goes below 0).
    // j increases by at most 1 per outer iteration (the ++j step),
    // so total increases across all iterations <= n.
    // Each while-loop iteration strictly decreases j by at least 1
    // (since p[j] < j — a border is strictly shorter than the string),
    // so total decreases <= total increases <= n.
    // Hence the while loop runs O(n) times in total, not per iteration.
	return p;
}

// Counting occurrences of each prefix
vector<int> _cnt(const string &s) {
    int n = s.length();

    // cnt[i] = number of times s[1, i] occurs in s as a substring
    // initialized to 1 since s[1, i] always occurs as the prefix itself
    vector<int> cnt(n + 1, 1);

    // m[i] = number of times we still need to increment cnt[k] for all
    // borders k of s[1, i]; contributed to by all j > i that have i as
    // their longest border (since those j's border-increment obligations
    // for i and below fall on i to propagate further)
    vector<int> m(n + 1, 0);
    vector<int> p = prefix(s);

    // for each prefix s[1, i], s[1, i] occurs as a substring of s iff it
    // occurs as the prefix itself (counted in the initialization), or as a
    // border of some s[1, j] for j > i
    // so for each j, we want to increment cnt[k] for every k in b(s[1, j])
    //
    // the main idea is that incrementing cnt for all borders of s[1, i] = increment cnt[p[i]]
    // once, then do the same for all borders of s[1, p[i]] (by corollary of T5)
    // so we break the obligation: "increment borders of s[1, i] m[i] times"
    // into: add m[i] to cnt[p[i]], then pass m[i] down to p[i]
    //
    // iterating backwards ensures that when we process i, all j > i with
    // p[j] = i have already contributed their m[j] into m[i]
    for (int i = n; i >= 1; i--) {
        ++m[i];              // i itself needs its own borders incremented once
        cnt[p[i]] += m[i];  // fulfill m[i] increments to the longest border of s[1, i]
        m[p[i]] += m[i];    // pass the obligation down: borders of s[1, p[i]] also need m[i] increments
    }
    return cnt;
}

// KMP Pattern Matching
// Given a pattern p of length m (>= 1) and a text t of length n (>= 1), find 
// all the starting positions in t where p occurs as a substring

vector<int> kmp(const string &t, const string &p) {
    int n = t.length(), m = p.length();
    vector<int> pos;
    vector<int> pi = prefix(p);

    // j = length of the longest suffix of t[1..i] that equals a prefix of p.
    // Equivalently, we have matched p[1..j] against the last j characters of
    // t seen so far.  j == 0 means no prefix of p is currently matched.
    int j = 0;

    for (int i = 1; i <= n; i++) {
        // The while condition has two cases; both call for falling back via pi:
        //
        // Case 1 (j == m): we had a FULL match at the previous step.
        //   We must fall back before trying to extend, so that we can find
        //   overlapping occurrences.  pi[m] gives the longest PROPER border
        //   of p, which is already lined up as the next candidate prefix.
        //
        // Case 2 (j > 0 && p[j] != t[i-1]): PARTIAL match but mismatch at
        //   the next character.  By the pi-chain theorem, the next-longest
        //   border of p[1..j] has length pi[j], so we fall back to that and
        //   retry the same text character t[i].
        //
        // In both cases pi[j] is the right fall-back: it gives the longest
        // border of what we have matched so far, preserving as much progress
        // as possible before retrying.
        while (j == m || (j > 0 && p[j + 1 - 1] != t[i - 1]))
            j = pi[j];

        // After the while, either j == 0 or p[j+1] == t[i] (0-indexed: p[j] == t[i-1]).
        // If they match, extend the current border by one character.
        if (p[j + 1 - 1] == t[i - 1])
            ++j;

        // A full match of p ends at t[i].  The 0-indexed start position in t
        // is i - m  (since the match occupies t[i-m .. i-1] in 0-indexed).
        if (j == m)
            pos.push_back(i - m);
    }

    return pos;
}

// ============================================================================
// THE FAILURE TREE
// ============================================================================
// Given the prefix array pi[1..n] for a string s of length n >= 1, define a
// graph G as follows:
//
//   Vertices : { 0, 1, ..., n }                     (n + 1 vertices total)
//   Edges    : { {v, pi[v]} : 1 <= v <= n }         (one edge per non-root vertex)

// Since 1 <= pi[v] <= n for 1 <= v <= n, both the vertices in an element of the edge
// set are vertices of G itself
//
// We claim G is a tree (we generally root it at 0).  To prove this we show:
//   (1) G has no self-edges           (Lemma 1)
//   (2) G has exactly n edges         (Lemma 2)
//   (3) G is connected                (Lemma 3)
//
// A connected graph on n+1 vertices with exactly n = (n+1) - 1 edges is a tree,
// so (2) + (3) are sufficient.  (1) is a sanity check that edges are well-formed.
// ----------------------------------------------------------------------------
// Lemma 1 (No Self-Edges)
// No edge of G is a self-loop.
//
// Proof.
// An edge {v, pi[v]} is a self-loop iff pi[v] = v.
// But pi[v] < v for all 1 <= v <= n (a border is strictly shorter than the
// string), so pi[v] != v.  Hence no self-loops exist.  QED.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Lemma 2 (Edge Count)
// G has exactly n edges.
//
// Proof.
// The edge set is { {v, pi[v]} : 1 <= v <= n }. 
// Thus, the number of elements of this set is exactly equal to the number of distinct
// integral values in the range [1, n], which is trivially n.
// Therefore |E| = n.  QED.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Lemma 3 (Connectivity)
// For every vertex u in {0, 1, ..., n}, there is a path from u to 0 in G.
// Hence G is connected.
//
// Proof.
// The case u = 0 is trivial (zero-length path).
// For 1 <= u <= n, consider the sequence:
//
//     u,  pi[u],  pi^2[u],  pi^3[u],  ...
//
// By the pi-chain theorem, this is a strictly decreasing sequence of
// non-negative integers that terminates at 0 after finitely many steps.
// Every consecutive pair (a, b) in the sequence satisfies b = pi[a] with
// a >= 1, so the edge {a, b} exists in G.
// Therefore the sequence is a walk from u to 0 in G.  QED.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Conclusion
// G is a tree rooted at 0.
//
// Proof.
// By Lemma 2, |E| = n = (n + 1) - 1 = |V| - 1.
// By Lemma 3, G is connected.
// A connected graph satisfying |E| = |V| - 1 is a tree.  QED.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Interpretation
// The failure tree gives the border structure of s a geometric form:
//
//   - The path from vertex i to the root 0 spells out exactly the border
//     lengths of s[1..i] in strictly decreasing order (by the pi-chain theorem).
//
//   - The depth of vertex i equals the number of proper borders of s[1..i]
//     (including the empty one).
//
//   - The subtree rooted at vertex k contains exactly those indices i for
//     which s[1..k] is a border of s[1..i].
// ----------------------------------------------------------------------------

vector<vector<int>> failure_tree(const string &s) {
    int n = s.length();
    vector<vector<int>> tree(n + 1);
    vector<int> p(n + 1);

    p[1] = 0;
    int j = p[1];
    for (int i = 2; i <= n; i++) {
        while (j > 0 && s[j + 1 - 1] != s[i - 1])
            j = p[j];
        if (s[j + 1 - 1] == s[i - 1])
            ++j;
        p[i] = j;
    }

    for (int i = 1; i <= n; i++)
        tree[i].push_back(p[i]), tree[p[i]].push_back(i);
    return tree;
}

// Prefix Occurrence Counting
// For a string of length n (>= 1), compute for each 1 <= k <= n,
// cnt[k] = number of times the prefix s[1, k] occurs as a substring of s

// Now,
// cnt[k] = 1 + the number of prefixes of s which have s[1, k] as its border
//        = number of nodes in the subtree of vertex k in the failure tree of s
// for all 1 <= k <= n

int dfs(int node, int parent, vector<int> &sz, vector<vector<int>> &tree) {
    if (tree[node].size() == 1) 
        return sz[node] = 1;

    for (auto x : tree[node])
        if (x != parent)
            sz[node] += dfs(x, node, sz, tree);
    return sz[node];
}

vector<int> _cnt_two(const string &s) {
    int n = s.length();
    auto tree = failure_tree(s);

    vector<int> sz(n + 1, 0);
    dfs(0, -1, sz, tree);
    return sz;
}

// Let s is a string of length n (>= 1)
// A positive integer p is a period of string s iff s[i] = s[i + p] for 1 <= i <= n - p

// -------------------------------------------------------------------------------------------------
// Theorem 2.1

// -------------------------------------------------------------------------------------------------