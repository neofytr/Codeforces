# Data Structures for Competitive Programming: A Rigorous Treatment

---

## Table of Contents

1. Segment Trees -- Complete Theory
2. Advanced Segment Tree Queries -- Walking the Tree
3. Lazy Propagation -- Full Formal Treatment
4. Sparse Tables -- Theory and Proof
5. Sqrt Decomposition
6. Convex Hull Trick (CHT)
7. Li Chao Tree
8. Monotonic Stack and Deque Patterns
9. Decision Tree -- Which Structure to Use

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

---

## Section 4: Sparse Tables -- Theory and Proof

### 4.1 Definition and Construction

**Definition 4.1 (Sparse Table).** Let a[0..n-1] be an array and f: S x S -> S be a
binary operation. The sparse table is a 2D array:

    sparse[k][i] = f(a[i], a[i+1], ..., a[i + 2^k - 1])

for k = 0, 1, ..., floor(log2(n)) and i = 0, 1, ..., n - 2^k.

**Construction (Dynamic Programming):**
- Base: sparse[0][i] = a[i] for all i.
- Transition: sparse[k][i] = f(sparse[k-1][i], sparse[k-1][i + 2^(k-1)])

**Proof of transition correctness.** By definition:
- sparse[k][i] = f(a[i], ..., a[i + 2^k - 1])
- The range [i, i + 2^k - 1] splits into [i, i + 2^(k-1) - 1] and [i + 2^(k-1), i + 2^k - 1].
- By associativity: f(a[i], ..., a[i+2^k-1]) = f(f(a[i], ..., a[i+2^(k-1)-1]),
  f(a[i+2^(k-1)], ..., a[i+2^k-1])) = f(sparse[k-1][i], sparse[k-1][i + 2^(k-1)]).

**Complexity.** There are O(log n) levels and n entries per level: O(n log n) time and space.

### 4.2 Query for Idempotent Operations

**Definition 4.2 (Idempotent).** An operation f is idempotent if f(a, a) = a for all a.
Examples: min, max, gcd, bitwise AND, bitwise OR.

**Query.** For range [l, r]:
```
k = floor(log2(r - l + 1))
answer = f(sparse[k][l], sparse[k][r - 2^k + 1])
```

**Theorem 4.1 (Correctness for Idempotent Operations).** The query correctly computes
f(a[l], a[l+1], ..., a[r]).

**Proof.** Let len = r - l + 1 and k = floor(log2(len)). Then:
- 2^k <= len < 2^(k+1), which implies 2^k > len/2.
- The interval [l, l + 2^k - 1] covers positions l through l + 2^k - 1.
- The interval [r - 2^k + 1, r] covers positions r - 2^k + 1 through r.
- Their union: since l + 2^k - 1 >= l + len/2 - 1 = l + (r-l+1)/2 - 1 = (l+r-1)/2,
  and r - 2^k + 1 <= r - len/2 + 1 = (l+r+1)/2 + 1, the two intervals overlap and their
  union is [l, r].
- For idempotent f: f(f(a[i1], ..., a[ij]), f(a[ik], ..., a[im])) where the union of
  {i1,...,ij} and {ik,...,im} equals {l,...,r} gives f(a[l], ..., a[r]). The overlapping
  elements are counted twice, but idempotency ensures f(a, a) = a, so this does not matter.

More rigorously: for idempotent, commutative, associative f, f applied to any multiset
containing each element at least once gives the same result as f applied to the set.

**Corollary 4.1.** Sparse table queries run in O(1) time with O(1) precomputed log values.

**Precomputing logs:**
```
lg[1] = 0
for i = 2 to n:
    lg[i] = lg[i/2] + 1
```

### 4.3 Why Sparse Tables Fail for Non-Idempotent Operations

**Claim.** Sparse tables with the overlap query method are INCORRECT for sum.

**Proof by counterexample.** Array a = [1, 2, 3, 4]. Query [0, 3]:
k = floor(log2(4)) = 2. sparse[2][0] = 1+2+3+4 = 10. sparse[2][1] would need index 1
with block size 4, but n=4 so that works: sparse[2][1] doesn't exist (out of bounds).
Actually for [0,2]: k = floor(log2(3)) = 1. sparse[1][0] = 1+2 = 3. sparse[1][1] = 2+3 = 5.
f(3, 5) = 8, but the correct answer is 1+2+3 = 6. The element a[1]=2 was counted twice.

For non-idempotent operations, use a segment tree or prefix sums (for the specific case
of sum, prefix sums give O(1) range queries with O(n) preprocessing).

### 4.4 Disjoint Sparse Table (for Non-Idempotent Operations)

For completeness: a **disjoint sparse table** achieves O(n log n) preprocessing and O(1)
range queries even for non-idempotent associative operations. The idea is to precompute
prefix/suffix aggregates within each block at each level, ensuring no overlap. The
details are more complex but the query uses the highest bit where l and r differ to select
the appropriate level.

---

## Section 5: Sqrt Decomposition

### 5.1 Core Idea

**Definition 5.1.** Given an array a[0..n-1] and block size B, divide the array into
ceil(n/B) blocks. Block j covers indices [j*B, min((j+1)*B - 1, n-1)].

Precompute an aggregate for each complete block (e.g., block_sum[j] for range-sum queries).

### 5.2 Range Query

To answer a range query [l, r]:
1. **Left partial block**: indices from l to the end of l's block (at most B elements).
2. **Complete blocks**: all blocks fully contained in [l, r] (at most ceil(n/B) blocks).
3. **Right partial block**: indices from the start of r's block to r (at most B elements).

**Theorem 5.1.** Range query time is O(n/B + B).

**Proof.** Partial blocks contribute at most 2B element accesses total (left partial + right
partial). Complete blocks contribute at most ceil(n/B) block accesses, each O(1).
Total: O(B + n/B).

**Optimization.** Minimize B + n/B. By AM-GM: B + n/B >= 2*sqrt(n), with equality when
B = sqrt(n). Therefore B = floor(sqrt(n)) or ceil(sqrt(n)) gives O(sqrt(n)) per query.

### 5.3 Point Update

Update a[i] = val: update the element and recompute block aggregate for block i/B. O(1)
for the element update, O(B) = O(sqrt(n)) for recomputing the block aggregate (or O(1)
if the update is incremental: block_sum[i/B] += val - a[i]).

### 5.4 Range Update

To add val to all elements in [l, r]:
- Partial blocks: update elements individually, recompute block aggregates. O(B) each.
- Complete blocks: store a block-level lazy value. block_lazy[j] += val. O(1) per block.
- Total: O(B + n/B) = O(sqrt(n)).

Point query after range updates: a[i] + block_lazy[i/B].

### 5.5 Mo's Algorithm (Offline Sqrt Decomposition)

**Problem.** Answer Q offline range queries on an array, where we can maintain a data
structure that supports:
- Insert(x): add element x to the current window.
- Delete(x): remove element x from the current window.
- Answer(): return the current answer.

All three operations in O(T) time.

**Algorithm.** Sort queries by (block of l, r). Process queries in this order, maintaining
the current window [cur_l, cur_r] and extending/shrinking it to match each query.

**Theorem 5.2.** Mo's algorithm processes Q queries in O((n + Q) * sqrt(n) * T) time.

**Proof.** Partition queries into groups by block(l).

**Right pointer movement:** Within a group (same block of l), queries are sorted by r.
So r moves monotonically from left to right across all queries in the group, covering at
most n positions. There are n/B groups, so total right pointer movement is O(n * n/B) = O(n^2/B).

**Left pointer movement:** Within a group, l stays within one block of size B. Between
consecutive queries in the same group, l moves at most 2B. With Q queries total (and at
most Q per group across all groups), total left movement is O(Q * B).

**Total:** O(n^2/B + Q*B). Setting B = n/sqrt(Q) minimizes this to O(n * sqrt(Q)).
For Q = O(n), this is O(n * sqrt(n)).

Each movement costs O(T), giving O((n * sqrt(Q)) * T).

**Remark.** If T = O(1) (e.g., maintaining frequency counts with a hash map or array),
the total complexity is O(n * sqrt(Q)), which is typically O(n * sqrt(n)).

### 5.6 When to Prefer Sqrt Decomposition

Sqrt decomposition is preferred over segment trees when:
1. The aggregate is hard to compose hierarchically (e.g., count of distinct elements).
2. The problem requires offline processing (Mo's algorithm).
3. Implementation simplicity is critical under time pressure.
4. The constant factor matters less than the ease of debugging.

The disadvantage is the worse asymptotic bound: O(sqrt(n)) vs O(log n) per operation.

---

## Section 6: Convex Hull Trick (CHT)

### 6.1 Problem Statement

**Problem.** Maintain a dynamic set of linear functions F = {f_j(x) = m_j * x + b_j}.
Support:
- Insert(m, b): add the function f(x) = m*x + b to F.
- Query(x): compute min_{f in F} f(x).

### 6.2 Geometric Interpretation

Each function f_j(x) = m_j * x + b_j is a line in the (x, y)-plane. The minimum over all
functions at a given x is the **lower envelope** of the set of lines.

**Definition 6.1 (Lower Envelope).** The lower envelope of a set of lines L is the function
    E(x) = min_{l in L} l(x).

The lower envelope is a convex piecewise-linear function (it is the pointwise minimum of
linear functions, hence concave-down... actually, the min of linear functions is concave.
Wait -- let us be precise.)

**Theorem 6.1.** The lower envelope of a finite set of lines is a piecewise-linear concave
function. The "active" lines, ordered by the x-coordinate where they become optimal, have
decreasing slopes.

**Proof.** At each point x, the minimum is achieved by some line. As x increases from -inf
to +inf, the optimal line changes at intersection points. Between consecutive intersection
points, the envelope is linear (following a single line). At an intersection point, the
envelope switches from one line to another. Since we're taking the minimum, the line with
smaller slope eventually dominates for larger x (it decreases faster or increases slower).
So the sequence of slopes of active lines is decreasing.

**Remark.** For maximum queries (upper envelope), the active slopes are increasing.

### 6.3 The Monotone Case (Sorted Slopes)

When lines are inserted in order of decreasing slope (for lower envelope), we can maintain
the hull as a stack.

**Redundancy check.** When inserting line l3, check if the previous line l2 is still
needed. Line l2 is redundant if the intersection of l1 and l3 lies below (or at) l2.

Let l1: y = m1*x + b1, l2: y = m2*x + b2, l3: y = m3*x + b3, with m1 > m2 > m3.

Intersection of l1 and l3: x_{13} = (b3 - b1) / (m1 - m3).
At x_{13}: l2(x_{13}) = m2 * (b3 - b1)/(m1 - m3) + b2.
l1(x_{13}) = l3(x_{13}) = m1 * (b3 - b1)/(m1 - m3) + b1.

l2 is redundant iff l2(x_{13}) >= l1(x_{13}) (since l1 = l3 at this point, and we want min).

Simplifying: l2 is redundant iff
    (b3 - b1) / (m1 - m3) <= (b2 - b1) / (m1 - m2)

(assuming m1 > m3, m1 > m2; cross-multiply carefully with sign considerations).

**In practice (to avoid floating point):** Use cross-multiplication:
    (b3 - b1) * (m1 - m2) <= (b2 - b1) * (m1 - m3)

This is the standard "bad" check: pop l2 while this holds.

**Insert algorithm:**
```
insert(m, b):
    new_line = (m, b)
    while |hull| >= 2 and is_redundant(hull[-2], hull[-1], new_line):
        hull.pop()
    hull.push(new_line)
```

**Theorem 6.2.** Amortized O(1) per insertion (each line is pushed and popped at most once).

### 6.4 Query

**Case 1: Queries in sorted order of x.** Maintain a pointer into the hull. For each query
x, advance the pointer while the next line gives a smaller value. O(1) amortized per query
(the pointer only moves forward).

**Case 2: Arbitrary query order.** Binary search on the hull for the line minimizing f(x).
Since the active lines have decreasing slopes, the intersection points are sorted. The
optimal line for query x is found by binary searching for the intersection point closest
to x. O(log n) per query.

### 6.5 Application: DP Optimization

Many DP recurrences have the form:

    dp[i] = min_{j < i} (dp[j] + cost(j, i))

where cost(j, i) = a[i] * b[j] + c[j] + d[i] (i.e., separable into a product of an
i-term and j-term, plus j-only and i-only terms).

Rewrite: dp[i] = d[i] + a[i] * b[j] + (dp[j] + c[j]) = d[i] + min_j(b[j] * a[i] + (dp[j] + c[j])).

This is min over lines f_j(x) = b[j] * x + (dp[j] + c[j]) evaluated at x = a[i].

If b[j] is monotone in j (slopes sorted) and a[i] is monotone in i (queries sorted),
the entire DP runs in O(n) using the monotone CHT.

---

## Section 7: Li Chao Tree

### 7.1 Motivation

The Convex Hull Trick requires slopes to be monotone (or uses binary search for O(log n)).
The Li Chao tree handles arbitrary insertion order with O(log C) per operation, where C
is the range of x-coordinates.

### 7.2 Structure

**Definition 7.1 (Li Chao Tree).** A Li Chao tree is a segment tree over the x-domain
[x_lo, x_hi]. Each node v with range [l, r] stores at most one line, called the
"dominant" line at v. The tree satisfies:

**Invariant 7.1.** For any x in [x_lo, x_hi], the minimum over all stored lines at x
equals the minimum over all lines encountered on the path from the root to the leaf
containing x.

### 7.3 Insert

To insert line g into node v with range [l, r] that currently stores line f:

```
insert(v, l, r, g):
    if l == r:
        if g(l) < f(l):
            swap(f, g)    // f is now the better line at this point
        return            // discard g

    m = (l + r) / 2
    left_better = g(l) < f(l)
    mid_better  = g(m) < f(m)

    if mid_better:
        swap(f, g)        // f is now the one winning at midpoint

    if l == r:
        return

    if left_better != mid_better:
        // g was better on the left before the swap at midpoint
        // After swap, the "loser" (now g) is better on the left half
        insert(left_child(v), l, m, g)
    else:
        // The loser (g) might be better on the right half
        insert(right_child(v), m+1, r, g)
```

**Theorem 7.1.** Insert runs in O(log C) time, where C = x_hi - x_lo + 1.

**Proof.** At each node, we do O(1) work (evaluate lines at 2 points, compare, possibly
swap) and recurse into at most ONE child. The tree has depth O(log C). Hence O(log C).

**Theorem 7.2 (Correctness).** After insertion, Invariant 7.1 is preserved.

**Proof.** Two distinct lines intersect at most once. At each node, we keep the line
winning at the midpoint as the stored line. The losing line can only be better than the
winning line on one side of the midpoint (since they cross at most once). We recurse into
that side with the losing line. On the other side, the winning line dominates everywhere,
so no action is needed.

By induction on depth: at each level, the node stores the line that is best at the
midpoint. Any query point x is the midpoint of exactly one node at each level on the
root-to-leaf path. Thus, the true minimum at x is the minimum over all lines stored on
the path from root to the leaf containing x.

More formally: suppose we have correctly maintained the invariant for all nodes before
inserting g. After insertion, g is pushed down into exactly one subtree, and at each node
on its path, the stored line wins at the midpoint against g. For any query point x:
- If x is on the side where the stored line beats g at every point: the stored line
  at that node correctly represents the better option. g is not needed here.
- If x is on the side where g might win: g has been recursively inserted into that
  subtree, so it will be found on the path from that child to the leaf.

### 7.4 Query

```
query(v, l, r, x):
    if l == r:
        return f_v(x)       // f_v is the line stored at v
    m = (l + r) / 2
    val = f_v(x)             // contribution from this node's line
    if x <= m:
        return min(val, query(left_child(v), l, m, x))
    else:
        return min(val, query(right_child(v), m+1, r, x))
```

**Theorem 7.3.** Query runs in O(log C) time.

**Proof.** Single root-to-leaf traversal, O(1) per node, O(log C) nodes.

### 7.5 Comparison with CHT

| Property              | CHT (monotone)   | CHT (general)    | Li Chao Tree     |
|-----------------------|------------------|------------------|------------------|
| Insert                | O(1) amortized   | O(n) worst case  | O(log C)         |
| Query                 | O(1) amortized   | O(log n)         | O(log C)         |
| Requires sorted slopes| Yes              | No (but slower)  | No               |
| Space                 | O(n)             | O(n)             | O(C) or dynamic  |

When C is large, use dynamic node creation (only create nodes when accessed) or coordinate
compression if query points are known in advance.

---

## Section 8: Monotonic Stack and Deque Patterns

### 8.1 Next Greater Element

**Problem.** Given array a[0..n-1], for each i, find nge[i] = min{j > i : a[j] > a[i]},
or -1 if no such j exists.

**Algorithm.** Process elements left to right, maintaining a stack S of indices whose NGE
has not yet been found.

```
stack S = empty
for i = 0 to n-1:
    while S is not empty and a[S.top()] < a[i]:
        nge[S.pop()] = i
    S.push(i)
while S is not empty:
    nge[S.pop()] = -1
```

**Invariant 8.1.** At all times, the stack contains indices in increasing order, and
their corresponding values a[S[0]] >= a[S[1]] >= ... >= a[S.top()] are in non-increasing
order (the stack is "monotonically decreasing" in values from bottom to top).

**Proof of invariant.** By induction on the number of push operations:
- Initially, the stack is empty (vacuously true).
- When pushing index i: we pop all indices j with a[j] < a[i]. After popping, either
  the stack is empty, or S.top() has a[S.top()] >= a[i]. Then we push i, maintaining
  the non-increasing order.

**Theorem 8.1 (Correctness).** nge[j] = i is set only when a[i] > a[j] and i is the
smallest such index greater than j.

**Proof.** When we pop j at step i, we know:
1. a[i] > a[j] (the while condition).
2. i > j (we process left to right, and j was pushed before i).
3. i is the FIRST index > j with a[i] > a[j]: Suppose there exists k with j < k < i
   and a[k] > a[j]. Then when we processed k, we would have popped j (since a[k] > a[j]
   and j was on the stack). But j is still on the stack at step i, contradiction. So no
   such k exists, and i is indeed the first.

**Theorem 8.2.** The algorithm runs in O(n) time.

**Proof.** Each index is pushed onto the stack exactly once and popped at most once.
Total push operations: n. Total pop operations: at most n. Each operation is O(1).
Total: O(n).

### 8.2 Largest Rectangle in Histogram

**Problem.** Given histogram bar heights h[0..n-1], find the largest rectangle that fits
under the histogram.

**Key insight.** For each bar i, find the maximal range [l_i, r_i] such that h[j] >= h[i]
for all j in [l_i, r_i]. Then the rectangle with height h[i] and width (r_i - l_i + 1)
is a candidate answer.

l_i is determined by the "previous smaller element" of i.
r_i is determined by the "next smaller element" of i.

Both are computed in O(n) using monotonic stacks (analogous to NGE).

**Theorem 8.3.** The largest rectangle equals max_i h[i] * (r_i - l_i + 1), and this
can be computed in O(n) total.

**Proof of optimality.** Any rectangle under the histogram has some height h. The shortest
bar within the rectangle's span limits the height. Thus the rectangle of height h is
determined by some bar i with h[i] = h, extended as far left and right as possible while
all bars are >= h. This is exactly the rectangle h[i] * (r_i - l_i + 1). Since we
consider all bars i, we consider all possible maximal rectangles.

### 8.3 Sliding Window Minimum/Maximum

**Problem.** Given array a[0..n-1] and window size k, compute for each i in [k-1, n-1]:
    win_min[i] = min(a[i-k+1], ..., a[i])

**Algorithm.** Maintain a monotonic deque (double-ended queue) of indices:

```
deque D = empty
for i = 0 to n-1:
    // Remove elements outside the window
    while D is not empty and D.front() <= i - k:
        D.pop_front()
    // Maintain monotonicity: remove elements >= a[i] from back
    while D is not empty and a[D.back()] >= a[i]:
        D.pop_back()
    D.push_back(i)
    // D.front() is the index of the minimum in window [i-k+1, i]
    if i >= k-1:
        win_min[i] = a[D.front()]
```

**Invariant 8.2.** At all times:
1. Indices in D are in strictly increasing order.
2. Values a[D[0]] < a[D[1]] < ... < a[D.back()] are in strictly increasing order.
3. All indices in D are within the current window [i-k+1, i].

**Proof of correctness.** The front of the deque is always the minimum of the current
window because:
- All elements in the window that are >= some later element have been removed (they can
  never be the minimum while the later, smaller element is in the window).
- Elements outside the window are removed from the front.
- What remains is a subsequence of the window's elements in increasing order, with the
  front being the smallest.

**Theorem 8.4.** The algorithm runs in O(n) time.

**Proof.** Each element is pushed to the back exactly once and popped (from front or back)
at most once. Total operations: O(n).

### 8.4 Sum of Subarray Minimums

**Problem.** Given a[0..n-1], compute the sum over all subarrays of the minimum element:
    SUM_{0 <= l <= r <= n-1} min(a[l..r])

**Solution.** For each a[i], determine how many subarrays have a[i] as their minimum.

Let left[i] = number of consecutive elements to the left of i (including i) that are >= a[i].
Let right[i] = number of consecutive elements to the right of i (including i) that are > a[i].
(The asymmetry >= vs > handles duplicates: each subarray's minimum is attributed to
exactly one position.)

Then a[i] is the minimum of left[i] * right[i] subarrays.

**Answer = SUM_i a[i] * left[i] * right[i].**

Both left[] and right[] are computed in O(n) using monotonic stacks (previous smaller
or equal, next strictly smaller).

**Proof of the counting formula.** A subarray [l, r] containing position i has min = a[i]
iff a[j] >= a[i] for all j in [l, r], and i is the leftmost position achieving the
minimum (by our convention with the asymmetric comparison). The number of valid l values
is left[i] (ranging from i - left[i] + 1 to i). The number of valid r values is right[i]
(ranging from i to i + right[i] - 1). These choices are independent, giving
left[i] * right[i] subarrays.

---

## Section 9: Decision Tree -- Which Structure to Use

### 9.1 Quick Reference Table

| Need                                  | Structure            | Build       | Query      | Update     |
|---------------------------------------|----------------------|-------------|------------|------------|
| Range sum, point update               | BIT / Fenwick Tree   | O(n)        | O(log n)   | O(log n)   |
| Range aggregate, point update         | Segment Tree (PURQ)  | O(n)        | O(log n)   | O(log n)   |
| Range aggregate, range update         | Segment Tree + Lazy  | O(n)        | O(log n)   | O(log n)   |
| Static range min/max/gcd              | Sparse Table         | O(n log n)  | O(1)       | N/A        |
| Offline range queries, hard aggregate | Mo's Algorithm       | O(n)        | O(sqrt(n)) | N/A        |
| Online, hard aggregate, range queries | Sqrt Decomposition   | O(n)        | O(sqrt(n)) | O(sqrt(n)) |
| Min/max of linear functions           | CHT / Li Chao Tree   | O(n log n)  | O(log n)   | O(log n)   |
| k-th element, order statistics        | Segment Tree (walk)  | O(n)        | O(log n)   | O(log n)   |
| First element satisfying predicate    | Segment Tree (walk)  | O(n)        | O(log n)   | O(log n)   |
| Max subarray sum with updates         | Segment Tree (tuple) | O(n)        | O(log n)   | O(log n)   |

### 9.2 Decision Flowchart (Textual)

```
Is the data static (no updates)?
|
+-- YES --> Is the operation idempotent (min/max/gcd/AND/OR)?
|           |
|           +-- YES --> Sparse Table: O(n log n) build, O(1) query.
|           |
|           +-- NO --> Is it sum? Use prefix sums: O(n) build, O(1) query.
|                       Otherwise: precompute with segment tree or sparse table variant.
|
+-- NO --> What type of updates?
           |
           +-- Point updates only:
           |   |
           |   +-- Need range sum? BIT/Fenwick (simplest, smallest constant).
           |   +-- Need range min/max/other? Segment tree (PURQ).
           |   +-- Need k-th element or search? Segment tree with walking.
           |
           +-- Range updates:
               |
               +-- Only need point queries? RUPQ segment tree (lazy only, no merge).
               +-- Need range queries too? RURQ segment tree (full lazy propagation).
               +-- Operation hard to compose? Sqrt decomposition.
```

### 9.3 Complexity vs. Constant Factor Considerations

In competitive programming, asymptotic complexity is not everything:

- **BIT vs Segment Tree for range sum + point update**: Both O(log n), but BIT has a
  constant factor roughly 2-3x smaller due to simpler operations and better cache behavior.
  Prefer BIT when it suffices.

- **Sparse Table vs Segment Tree for static range min**: Sparse table is O(1) query vs
  O(log n), but uses O(n log n) memory. For n up to ~10^7, the memory may be a concern.

- **Sqrt decomposition vs Segment Tree**: Sqrt decomposition is O(sqrt(n)) vs O(log n),
  but for n = 10^5, sqrt(n) ~ 316 while log2(n) ~ 17. The difference is about 18x.
  For n = 10^6, it's sqrt(n) ~ 1000 vs log2(n) ~ 20, a 50x difference. Segment trees
  are strongly preferred when they apply.

- **CHT vs Li Chao**: When slopes are monotone and queries are monotone, CHT gives O(1)
  amortized -- unbeatable. Li Chao is more general but has O(log C) overhead.

### 9.4 Common Pitfalls

1. **Forgetting the identity element**: A query on an empty range must return the identity.
   For sum it's 0, for min it's +INF, for max it's -INF, for gcd it's 0.

2. **Lazy propagation with wrong composition**: When combining "range set" and "range add"
   operations, the order of composition matters. Setting a range and then adding is
   different from adding and then setting. The lazy tag must encode both operations.

3. **Segment tree size**: Using 2*n instead of 4*n for the tree array causes buffer
   overflow when n is not a power of 2. Always allocate 4*n.

4. **Sparse table with sum**: Double-counting due to overlap. Use prefix sums instead.

5. **Monotonic stack: handling equal elements**: When finding "previous smaller" and
   "next smaller" for counting subarrays, use strict inequality on one side and
   non-strict on the other to avoid double-counting.

6. **Integer overflow in CHT**: The redundancy check involves products of differences.
   If slopes and intercepts are up to 10^9, the products can reach 10^18, requiring
   64-bit integers. If they're up to 10^18, use __int128 or careful rewriting.

---

## Appendix A: Template Code Patterns (Pseudocode)

### A.1 Iterative Segment Tree (Efficient Implementation)

For the special case of commutative operations, an iterative "bottom-up" segment tree
is both simpler and faster:

```
// Build: 0-indexed array a[0..n-1], tree[0..2n-1]
// tree[n+i] = a[i] for leaves
// tree[i] = f(tree[2i], tree[2i+1]) for internal nodes

build():
    for i = 0 to n-1: tree[n+i] = a[i]
    for i = n-1 down to 1: tree[i] = f(tree[2i], tree[2i+1])

update(pos, val):  // 0-indexed
    pos += n
    tree[pos] = val
    while pos > 1:
        pos /= 2
        tree[pos] = f(tree[2*pos], tree[2*pos+1])

query(l, r):  // [l, r) half-open
    res = e  // identity
    l += n; r += n
    while l < r:
        if l is odd:  res = f(res, tree[l]); l++
        if r is odd:  r--; res = f(res, tree[r])
        l /= 2; r /= 2
    return res
```

This uses exactly 2n space and has excellent cache performance.

**Theorem A.1.** The iterative query is correct for commutative, associative operations.

**Proof sketch.** The two pointers l and r climb the tree from leaves to root. At each
level, if l is a right child, its parent also covers elements outside [l, r), so we
include tree[l] directly and advance l. Symmetrically for r. The commutativity requirement
arises because elements may be combined out of order (left pointer contributes from the
left side, right pointer from the right side, and they meet in the middle).

For non-commutative operations, accumulate separately from left and right, then combine.

### A.2 BIT / Fenwick Tree

A Fenwick tree supports prefix-sum queries and point updates in O(log n) with minimal code:

```
bit[0..n] = {0}  // 1-indexed

update(i, delta):   // add delta to a[i]
    while i <= n:
        bit[i] += delta
        i += i & (-i)

prefix_sum(i):      // sum of a[1..i]
    s = 0
    while i > 0:
        s += bit[i]
        i -= i & (-i)
    return s

range_sum(l, r):    // sum of a[l..r]
    return prefix_sum(r) - prefix_sum(l-1)
```

**Why i & (-i) works**: In two's complement, -i = ~i + 1. The expression i & (-i)
isolates the lowest set bit of i. This bit determines the range of indices that bit[i]
is responsible for: bit[i] covers a[i - (i & (-i)) + 1 .. i].

**Theorem A.2.** Both update and prefix_sum run in O(log n) time.

**Proof.** Update increments i by its lowest set bit, so i strictly increases and reaches
n in at most log2(n) steps. Query decrements i by its lowest set bit, so i strictly
decreases and reaches 0 in at most log2(n) steps.

---

## Appendix B: Formal Proofs of Key Lemmas

### B.1 Proof that the Lower Envelope Has O(n) Segments

**Theorem B.1.** The lower envelope of n lines has at most n-1 breakpoints (points where
the optimal line changes) and at most n segments.

**Proof.** Two distinct lines intersect at most once (unless parallel). The lower envelope
visits each line at most once as a segment (a line that leaves the envelope cannot return
to it -- if line l is dominated by line l' at some point to the right of l's segment,
then l stays dominated for all further-right points, since l and l' cross at most once).

Order the segments of the envelope from left to right. Each segment corresponds to a
distinct line (since a line appears as one contiguous segment). Hence at most n segments
and n-1 transitions between them.

### B.2 Proof that Monotonic Stack Gives Correct Histogram Answer

**Theorem B.2.** In the largest rectangle in histogram problem, the optimal rectangle's
height equals h[i] for some bar i, and it extends from the previous smaller element of i
to the next smaller element of i.

**Proof.** Let R be an optimal rectangle with height H and span [l, r]. Then:
- H <= h[j] for all j in [l, r] (the rectangle fits under the histogram).
- There exists some i in [l, r] with h[i] = H (otherwise we could increase H).
- l cannot be decreased: h[l-1] < H (otherwise [l-1, r] with height H is a larger rectangle).
- r cannot be increased: h[r+1] < H (similarly).

So l-1 is the previous element smaller than h[i] = H, and r+1 is the next element smaller
than h[i]. This is exactly the maximal extension of bar i.

---

*End of guide. All complexities assume the word RAM model with O(1) arithmetic on
O(log n)-bit words. All proofs assume exact arithmetic (no floating point errors).*
