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
