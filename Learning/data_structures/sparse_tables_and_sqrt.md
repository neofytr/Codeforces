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
