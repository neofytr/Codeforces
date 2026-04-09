# Data Structures for Competitive Programming: A Rigorous Treatment

---

## Table of Contents

1. Segment Trees -- Complete Theory
2. Advanced Segment Tree Queries -- Walking the Tree
3. Lazy Propagation -- Full Formal Treatment

---

## Section 1: Segment Trees -- Complete Theory

### 1.1 Definition

Let a[0..n-1] be an array of elements drawn from a set S, and let f: S x S -> S be an
associative binary operation with identity element e (i.e., (S, f, e) forms a monoid).

**Definition 1.1 (Segment Tree).** A segment tree T on array a[0..n-1] with respect to
operation f is a rooted binary tree where:

- Each node v is associated with a contiguous range [l_v, r_v] of array indices.
- The root is associated with [0, n-1].
- A leaf node with range [i, i] stores the value a[i].
- An internal node v with range [l, r] and midpoint m = floor((l+r)/2) has:
  - Left child with range [l, m]
  - Right child with range [m+1, r]
  - Stored value val(v) = f(val(left(v)), val(right(v)))

### 1.2 Space Complexity

**Theorem 1.1.** A segment tree on n elements uses at most 4n nodes.

**Proof.** We round up to n' = 2^(ceil(log2(n))). A complete binary tree on n' leaves has
2n' - 1 nodes. Since n' <= 2n (because 2^(ceil(log2(n))) <= 2n for all n >= 1), the total
node count is at most 2(2n) - 1 = 4n - 1 < 4n.

In practice, when using 1-indexed arrays with the root at index 1, the tree array has
size 4n. Node v has children at 2v and 2v+1. This implicit indexing avoids pointer overhead.

**Remark.** For n that is already a power of 2, the bound tightens to 2n - 1 internal nodes
plus n leaves = 2n - 1 total. The 4n bound handles the worst case of non-power-of-2 sizes.

### 1.3 Build Operation

**Algorithm (Build).** Recursively:
```
build(v, l, r):
    if l == r:
        tree[v] = a[l]
        return
    m = (l + r) / 2
    build(2*v, l, m)
    build(2*v+1, m+1, r)
    tree[v] = f(tree[2*v], tree[2*v+1])
```

**Theorem 1.2.** Build runs in O(n) time.

**Proof.** Each of the at most 4n nodes is visited exactly once, performing O(1) work.
More precisely, the recurrence T(n) = 2T(n/2) + O(1) solves to T(n) = O(n) by the
Master Theorem (case 1: a=2, b=2, d=0, so log_b(a) = 1 > 0 = d).

### 1.4 Point Update

**Algorithm (Point Update).** To set a[pos] = val:
```
update(v, l, r, pos, val):
    if l == r:
        tree[v] = val
        return
    m = (l + r) / 2
    if pos <= m:
        update(2*v, l, m, pos, val)
    else:
        update(2*v+1, m+1, r, pos, val)
    tree[v] = f(tree[2*v], tree[2*v+1])
```

**Theorem 1.3.** Point update runs in O(log n) time.

**Proof.** The algorithm follows a single root-to-leaf path. The tree has height
ceil(log2(n)) + 1 = O(log n). At each level, O(1) work is done.

### 1.5 Range Query

**Algorithm (Range Query).** To compute f(a[ql], a[ql+1], ..., a[qr]):
```
query(v, l, r, ql, qr):
    if ql > r or qr < l:
        return e                    // identity element
    if ql <= l and r <= qr:
        return tree[v]              // fully contained
    m = (l + r) / 2
    return f(query(2*v, l, m, ql, qr),
             query(2*v+1, m+1, r, ql, qr))
```

**Theorem 1.4.** Range query visits at most O(log n) nodes.

**Proof.** We prove a stronger claim: at each level of the tree, the query visits at
most 4 nodes, and at most 2 of them are "partially covered" (neither fully inside nor
fully outside the query range).

**Lemma 1.1.** At each level of the tree, the query visits at most 2 partial nodes.

*Proof of Lemma.* A partial node v with range [l_v, r_v] satisfies: ql <= r_v and
qr >= l_v (so it is not disjoint) but NOT (ql <= l_v and r_v <= qr) (so it is not
fully contained). The partial nodes at any level form a contiguous set of siblings.
Among these, only the leftmost and rightmost can be partial -- all nodes whose ranges
lie strictly between them are fully contained in [ql, qr].

More formally: if nodes v1, v2, v3 at the same level satisfy l_{v1} < l_{v2} < l_{v3}
and v1, v3 are both intersecting [ql, qr], then since the ranges partition the index
space at that level, we have l_{v1} <= ql (v1 is the leftmost partial), r_{v3} >= qr
(v3 is the rightmost partial), and [l_{v2}, r_{v2}] is entirely within [ql, qr]. Hence
v2 is fully contained, not partial.

Therefore at most 2 partial nodes per level, and each partial node spawns at most 2
children (one of which may be fully contained and one partial). Across O(log n) levels,
the total nodes visited is at most 4 * O(log n) = O(log n).

**Corollary 1.1.** The range query makes at most 4 * ceil(log2(n)) recursive calls that
do actual work (i.e., are not immediately rejected by the disjointness check).

### 1.6 The Combine Function (Monoid Requirements)

**Definition 1.2 (Valid Combine).** The operation f must satisfy:

1. **Associativity**: f(f(a, b), c) = f(a, f(b, c)) for all a, b, c in S.
2. **Identity**: There exists e in S such that f(a, e) = f(e, a) = a for all a in S.

Common monoids for competitive programming:

| Operation       | Set S     | f(a,b)    | Identity e |
|----------------|-----------|-----------|------------|
| Sum            | Z         | a + b     | 0          |
| Product        | Z         | a * b     | 1          |
| Minimum        | Z u {+inf}| min(a,b)  | +inf       |
| Maximum        | Z u {-inf}| max(a,b)  | -inf       |
| GCD            | N u {0}   | gcd(a,b)  | 0          |
| Bitwise OR     | N         | a | b     | 0          |
| Bitwise AND    | N         | a & b     | all 1s     |
| Bitwise XOR    | N         | a ^ b     | 0          |

**Why associativity matters**: The query decomposes [ql, qr] into sub-ranges and combines
results. Without associativity, the order of combination could yield different results.
With associativity, any parenthesization of f(a[ql], ..., a[qr]) gives the same result,
so the tree's hierarchical decomposition is valid.

---

## Section 2: Advanced Segment Tree Queries -- Walking the Tree

### 2.1 Finding the k-th Element

**Problem.** Maintain a multiset of integers in [0, n-1]. Support:
- Insert(x): add x to the multiset.
- Delete(x): remove one copy of x.
- Kth(k): find the k-th smallest element (1-indexed).

**Solution.** Build a segment tree on [0, n-1] where each leaf i stores count[i] (the
number of copies of i in the multiset). Each internal node stores the sum of its children.

**Algorithm (Kth).** Walk from root to leaf:
```
kth(v, l, r, k):
    if l == r:
        return l
    m = (l + r) / 2
    left_count = tree[2*v]
    if k <= left_count:
        return kth(2*v, l, m, k)
    else:
        return kth(2*v+1, m+1, r, k - left_count)
```

**Theorem 2.1.** Kth runs in O(log n) time.

**Proof.** The algorithm descends from root to leaf, visiting exactly one node per level.
The tree has O(log n) levels. At each node, O(1) work (one comparison, one subtraction).

**Correctness.** By induction on the height h of the subtree rooted at v:
- Base (h=0): l = r, so the only element in range is l; return l. k must equal 1 here
  (or the query is invalid), and tree[v] = count[l] >= 1.
- Inductive step: The left child covers [l, m] and contains left_count elements. If
  k <= left_count, the k-th element lies in [l, m], so recurse left. Otherwise, the k-th
  element is the (k - left_count)-th element in [m+1, r], so recurse right with adjusted k.

### 2.2 First Element >= x from Position p

**Problem.** Given an array a[0..n-1], support:
- Update(i, val): set a[i] = val.
- FirstGE(p, x): find the smallest index i >= p such that a[i] >= x, or -1 if none.

**Solution.** Segment tree with max in each node. Query by walking the tree:

```
first_ge(v, l, r, p, x):
    if r < p or tree[v] < x:
        return -1              // no valid element in this subtree
    if l == r:
        return l               // found it
    m = (l + r) / 2
    res = first_ge(2*v, l, m, p, x)
    if res != -1:
        return res
    return first_ge(2*v+1, m+1, r, p, x)
```

**Theorem 2.2.** FirstGE runs in O(log^2 n) time in the worst case, but O(log n) amortized
for many practical query distributions.

**Proof sketch.** In the worst case, the query may explore O(log n) nodes at each level
where the left child has max >= x but no valid element >= p. However, once we find that
the left subtree fails (returns -1), we move to the right subtree, and this "false start"
can happen at most O(log n) times across the whole descent.

A tighter analysis: the query visits O(log n) nodes. At each level, after possibly
checking the left child and finding no answer, the algorithm moves right. The key insight
is that the "no answer" branch terminates quickly: if tree[2*v] < x, it returns in O(1).
The expensive case is when tree[2*v] >= x but no element in [l, m] is >= p. This can
happen at most once per level because the segments at each level partition the range. Thus
O(log n) total nodes visited.

### 2.3 Max Subarray Sum (Kadane on Segment Tree)

**Problem.** Given array a[0..n-1], support:
- Update(i, val): set a[i] = val.
- MaxSubarraySum(l, r): find max sum of a contiguous non-empty subarray within [l, r].

**Definition 2.1.** Each segment tree node stores a tuple (pref, suff, total, ans) where:
- pref = max prefix sum of the range (max over all l <= j <= r of sum(a[l..j]))
- suff = max suffix sum of the range (max over all l <= j <= r of sum(a[j..r]))
- total = sum of all elements in the range
- ans = max subarray sum within the range

**Combine operation:**
```
combine(L, R):
    pref  = max(L.pref, L.total + R.pref)
    suff  = max(R.suff, R.total + L.suff)
    total = L.total + R.total
    ans   = max(L.ans, R.ans, L.suff + R.pref)
    return (pref, suff, total, ans)
```

**Theorem 2.3 (Correctness of Combine).** The combine operation correctly computes the
tuple for the concatenated range [l_L, r_R] from tuples for [l_L, m] and [m+1, r_R].

**Proof.** We verify each component:

1. **total**: Clearly sum(a[l_L..r_R]) = sum(a[l_L..m]) + sum(a[m+1..r_R]) = L.total + R.total.

2. **pref**: The max prefix sum of [l_L, r_R] is max over j in [l_L, r_R] of sum(a[l_L..j]).
   - If j <= m: this is at most L.pref (max prefix of left half).
   - If j > m: sum(a[l_L..j]) = sum(a[l_L..m]) + sum(a[m+1..j]) = L.total + (some prefix of R).
     The max over such j is L.total + R.pref.
   - These two cases are exhaustive, so pref = max(L.pref, L.total + R.pref).

3. **suff**: Symmetric argument. suff = max(R.suff, R.total + L.suff).

4. **ans**: The max subarray of [l_L, r_R] either:
   (a) lies entirely in [l_L, m]: contributes L.ans.
   (b) lies entirely in [m+1, r_R]: contributes R.ans.
   (c) crosses the boundary m: sum(a[i..j]) for some i <= m < j. This equals
       sum(a[i..m]) + sum(a[m+1..j]). The first part is maximized by L.suff, the second
       by R.pref. So this case contributes L.suff + R.pref.
   - These three cases are exhaustive (a subarray is either left-only, right-only, or
     crossing), so ans = max(L.ans, R.ans, L.suff + R.pref).

**Theorem 2.4 (Associativity).** The combine operation is associative.

**Proof sketch.** Each component of the tuple is defined as a max/sum over a contiguous
range. The combine operation corresponds to merging adjacent ranges. Since the underlying
definitions depend only on the array values (not on how the ranges are grouped), the
operation is associative. A formal proof verifies that combine(combine(A,B), C) and
combine(A, combine(B,C)) produce the same (pref, suff, total, ans) by expanding definitions.

**Leaf construction:** For leaf i: pref = suff = total = ans = a[i] (assuming we want
non-empty subarrays). If empty subarrays are allowed, ans = max(a[i], 0).

---

## Section 3: Lazy Propagation -- Full Formal Treatment

### 3.1 Motivation

Consider the problem: given array a[0..n-1], support:
- RangeUpdate(l, r, val): for all i in [l, r], set a[i] = a[i] + val.
- RangeQuery(l, r): compute sum(a[l..r]).

A naive approach updates each element individually: O(n) per range update. We want O(log n).

### 3.2 The Lazy Invariant

**Definition 3.1 (Lazy Tag).** Each node v has an additional field lazy[v] representing
a deferred operation that has been applied to v's range but NOT yet propagated to v's
children.

**Invariant 3.1 (Correctness Invariant).** At all times, the "true" aggregate for node v's
range equals the result of applying the composition of all lazy tags on the path from the
root to v, applied to the stored value tree[v].

More precisely, for the range-add, range-sum problem: if node v covers [l_v, r_v], then

    true_sum(l_v, r_v) = tree[v] + lazy[v] * (r_v - l_v + 1)

where lazy[v] is the total un-propagated additive update at v. But we maintain tree[v]
as the ALREADY UPDATED value for v's range. The lazy[v] is the PENDING update for v's
CHILDREN. This distinction is critical.

**Revised Invariant (Standard Convention).**
- tree[v] = correct aggregate for v's range, accounting for all updates affecting v.
- lazy[v] = pending update to be applied to v's CHILDREN (not to v itself).

When we apply a range update that fully covers v's range:
1. Update tree[v] immediately (e.g., tree[v] += val * (r_v - l_v + 1) for range-add).
2. Store the update in lazy[v] (e.g., lazy[v] += val) for later propagation to children.

### 3.3 Push Down

**Algorithm (push_down):** Before accessing children of v, propagate v's lazy tag:
```
push_down(v, l, r):
    if lazy[v] != 0:           // 0 is the identity for addition
        m = (l + r) / 2
        // Apply to left child
        tree[2*v] += lazy[v] * (m - l + 1)
        lazy[2*v] += lazy[v]
        // Apply to right child
        tree[2*v+1] += lazy[v] * (r - m)
        lazy[2*v+1] += lazy[v]
        // Clear
        lazy[v] = 0
```

**Lemma 3.1.** push_down preserves Invariant 3.1.

**Proof.** Before push_down: tree[v] is correct, lazy[v] = d (pending for children).
Children's stored values do not reflect d.

After push_down: tree[2*v] += d * |left range|, which adds the pending contribution.
lazy[2*v] += d, deferring the same update to grandchildren. lazy[v] = 0. Now:
- tree[2*v] is correct for its range (it incorporated d).
- lazy[2*v] holds any pending updates for 2*v's children (including d).
- tree[v] is unchanged (still correct, since its value already accounted for d).

### 3.4 Range Update with Lazy

```
range_update(v, l, r, ql, qr, val):
    if ql > r or qr < l:
        return
    if ql <= l and r <= qr:
        tree[v] += val * (r - l + 1)
        lazy[v] += val
        return
    push_down(v, l, r)
    m = (l + r) / 2
    range_update(2*v, l, m, ql, qr, val)
    range_update(2*v+1, m+1, r, ql, qr, val)
    tree[v] = tree[2*v] + tree[2*v+1]
```

### 3.5 Range Query with Lazy

```
range_query(v, l, r, ql, qr):
    if ql > r or qr < l:
        return 0
    if ql <= l and r <= qr:
        return tree[v]
    push_down(v, l, r)
    m = (l + r) / 2
    return range_query(2*v, l, m, ql, qr) + range_query(2*v+1, m+1, r, ql, qr)
```

**Theorem 3.1.** Both range_update and range_query run in O(log n) time.

**Proof.** Identical decomposition argument to Theorem 1.4. The query/update visits at most
O(log n) nodes (at most 2 partial nodes per level, O(log n) levels). Each node does O(1)
work including the push_down. Therefore total work is O(log n).

### 3.6 PURQ, RUPQ, RURQ Classification

**PURQ (Point Update, Range Query):**
- The basic segment tree from Section 1.
- No lazy propagation needed.
- Point update: O(log n). Range query: O(log n).

**RUPQ (Range Update, Point Query):**
- Store only lazy tags; no need for aggregate values.
- Range update: mark complete nodes with lazy tag. O(log n).
- Point query: walk from root to leaf, accumulating lazy values. O(log n).
- This is simpler than full RURQ because we never need to combine aggregates.

**RURQ (Range Update, Range Query):**
- Full lazy propagation as described above.
- Both operations O(log n).

**Theorem 3.2 (Composition of Lazy Tags).** For the lazy propagation to be correct, the
set of possible updates must form a semigroup under composition, and the "apply" function
must distribute over the combine function.

Formally, let U be the set of updates and S the set of node values. We need:
1. compose: U x U -> U such that applying u1 then u2 equals applying compose(u2, u1).
2. apply: U x S x N -> S (where N is the range length) such that applying update u to
   a node with value s covering n elements gives apply(u, s, n).
3. Distribution: apply(u, f(s1, s2), n1+n2) = f(apply(u, s1, n1), apply(u, s2, n2)).

**Example 1 (Range Add, Range Sum):**
- U = (Z, +), compose(u1, u2) = u1 + u2
- apply(u, s, n) = s + u*n
- Verify: (s1 + u*n1) + (s2 + u*n2) = (s1+s2) + u*(n1+n2). Correct.

**Example 2 (Range Set, Range Min):**
- U = Z u {null}, compose(u1, u2) = u2 (latest set wins)
- apply(u, s, n) = u (ignores previous value and range size)
- Verify: min(u, u) = u = apply(u, min(s1,s2), n1+n2). Correct.

**Example 3 (Range Add + Range Set, Range Sum):**
- U = (type, val) where type is "add" or "set".
- compose: set after anything = set. add after add = add(sum). add after set = set(old+add).
- This requires careful case analysis but is a common competitive programming pattern.
