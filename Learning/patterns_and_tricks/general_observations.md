# General Observations and Techniques -- Personal CP Handbook

Hard-won observations distilled from contest practice. Each section is
self-contained: read it cold and you should be able to re-derive and apply the
idea.

---

## 1. Parity and Invariant Observations

### 1.1 Parity of counts under constant-total operations

**Observation.** When an operation changes individual counts but the *total*
number of objects stays the same, check how the **parity** of some count
changes per operation.

**Why it works.** If every legal operation flips the parity of some quantity Q,
then Q's parity is an invariant modulo 2. The target state must share that
parity with the initial state -- otherwise the answer is impossible.

**Mental checklist:**
1. What quantity is conserved? (total sum, total count, etc.)
2. Does each operation change some sub-quantity by an even or odd amount?
3. Does the target state match the parity of the initial state?

### 1.2 Optimal ordering of mixed operations

**Observation.** When you can perform any operation from a group (op1, op2, ...)
in any order, there is usually an optimal ordering: *all* op1 before any op2,
etc.

**Why.** Consider two adjacent operations of different types. If swapping them
never worsens the result, one type dominates and should come first. This is an
exchange argument -- compare any two items pairwise, derive who should come
first, and sort.

---

## 2. Counting and Combinatorial Tricks

### 2.1 Counting triplets in O(n^2): fix the middle

To count triplets (i, j, k) with i < j < k satisfying some condition:

**Fix the middle element j.** Then solve two independent sub-problems:
- Count valid i in [1, j-1].
- Count valid k in [j+1, n].
- Combine (often multiply) the two counts.

```cpp
for (int j = 2; j <= n - 1; j++) {
    int left_count = /* count valid i in [1, j-1] */;
    int right_count = /* count valid k in [j+1, n] */;
    answer += left_count * right_count;
}
```

**Why the middle?** Fixing an endpoint often couples the other two. Fixing the
middle decouples them into independent left/right problems.

### 2.2 Permutation invariance for pair counting

**Rule.** If you need to count pairs (i, j) with i < j satisfying a condition
that depends only on **values** (not positions), you can **sort** the array
first.

Formally: if the condition C(a[i], a[j]) is symmetric and position-independent,
then the set {(a[i], a[j]) : i < j, C holds} is invariant under permutation of
the array.

**CANNOT sort when:**
- Problem involves subarrays, prefixes, or suffixes (order matters).
- Distance/position constraints like |i - j| <= k are part of the condition.

### 2.3 Sum of products of all unordered pairs in O(n)

**Problem.** Compute S = sum of A[i]*A[j] for all i < j.

**Formula:**

    total = A[1] + A[2] + ... + A[n]
    S = (1/2) * sum_{i=1}^{n} A[i] * (total - A[i])

**Derivation.** For each i, A[i] is multiplied with every other element. The
sum of those other elements is (total - A[i]). Summing over all i counts each
pair twice (once as i,j and once as j,i), hence divide by 2.

### 2.4 Inversion counting via merge sort -- O(n log n)

An **inversion** is a pair (i, j) with i < j and a[i] > a[j].

During merge sort, when merging two sorted halves, every time an element from
the right half is placed before remaining elements of the left half, it forms
an inversion with each of those remaining left elements.

```cpp
long long cnt = 0;

void merge_sort(int l, int r, vector<int>& arr) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    merge_sort(l, mid, arr);
    merge_sort(mid + 1, r, arr);

    vector<int> tmp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) tmp.push_back(arr[i++]);
        else {
            cnt += (mid - i + 1);  // all remaining left elements form inversions
            tmp.push_back(arr[j++]);
        }
    }
    while (i <= mid) tmp.push_back(arr[i++]);
    while (j <= r) tmp.push_back(arr[j++]);
    for (int k = l; k <= r; k++) arr[k] = tmp[k - l];
}
```

---

## 3. Distance and Geometry

### 3.1 Distance between two points on a line

**Claim.** If P(x1, y1) and Q(x2, y2) lie on the line y = mx + c, then:

    distance(P, Q) = |x2 - x1| * sqrt(1 + m^2)

**Proof.** 
    d = sqrt((x2-x1)^2 + (y2-y1)^2)
      = sqrt((x2-x1)^2 + (m(x2-x1))^2)
      = |x2-x1| * sqrt(1 + m^2)

**Corollary.** For any non-zero integer m, sqrt(1 + m^2) is irrational (since
1 + m^2 is not a perfect square for m != 0). Therefore the distance is always
irrational when m is a non-zero integer and x1 != x2.

### 3.2 Non-integral distance requires different row or column

Two distinct points P and Q have non-integral distance only if they differ in
at least one of row or column. (Points sharing both row and column are the same
point; points on the same row or same column have integer distance |x2-x1| or
|y2-y1|.)

---

## 4. Distance Minimization (1D) -- IMPORTANT

### 4.1 Sum of absolute distances -> MEDIAN

**Theorem.** Let a[1..n] be integers. Define

    f(x) = |a[1]-x| + |a[2]-x| + ... + |a[n]-x|.

Then f(x) is minimized when x = median(a).

**Proof intuition.** Consider moving x by 1 to the right. Each a[i] < x
contributes +1 to the change, each a[i] > x contributes -1. The change is zero
(or switches sign) exactly at the median, where half the points are on each
side.

**If n is even,** any value in [a[n/2], a[n/2+1]] (the median interval)
achieves the minimum.

### 4.2 Weighted version -> WEIGHTED MEDIAN

With weights w[i] > 0:

    f(x) = sum of w[i] * |a[i] - x|

The minimizer is the **weighted median**: the value y such that the cumulative
weight of points strictly less than y is at most W/2, and the cumulative weight
of points strictly greater than y is at most W/2, where W = sum of all weights.

### 4.3 Two-point absolute value identity

**Claim.** For a <= b:

    f(x) = |x-a| + |x-b|

achieves its minimum value of (b - a) for ALL x in [a, b].

**Proof by cases:**
- x < a: f(x) = (a-x) + (b-x) = a+b-2x > b-a.
- a <= x <= b: f(x) = (x-a) + (b-x) = b-a.
- x > b: f(x) = (x-a) + (x-b) = 2x-a-b > b-a.

### 4.4 Fast computation of shifted absolute sums

**Problem.** Given sorted v[1..n], compute:

    f(r) = |r - v[1]| + |r+1 - v[2]| + ... + |r+n-1 - v[n]|

in O(log n) per query after O(n) preprocessing.

**Transformation.** Let s[i] = v[i] - (i-1). Then:

    f(r) = sum_{i=1}^{n} |r - s[i]|

This is exactly the "sum of absolute distances from r" problem on array s.

**Algorithm:**
1. Build prefix sums p[0..n] of s (p[0] = 0, p[i] = p[i-1] + s[i]).
2. Binary search for k = first index where s[k] >= r.
3. Compute:
   - If no such k: f(r) = r*n - p[n].
   - If k = 1: f(r) = p[n] - r*n.
   - Otherwise: f(r) = r*(k-1) - p[k-1] + (p[n]-p[k-1]) - r*(n-k+1).

This splits the sum into elements below r (contribute r - s[i]) and elements
above r (contribute s[i] - r), each computable via prefix sums.

---

## 5. Constructive Problems

### 5.1 Constructing maximal sets

**Strategy:**
1. Prove an upper bound on the size of any valid set.
2. Explicitly construct a set achieving that bound.

If both steps succeed, the construction is optimal.

### 5.2 Subset sums from {1, 2, ..., n}

**Claim.** For S = {1, 2, ..., n}, every integer in [0, n(n+1)/2] is
achievable as a subset sum.

**Greedy construction** for target sum t:

```cpp
vector<int> subset;
int remaining = t;
for (int i = n; i >= 1; i--)
    if (remaining >= i) {
        remaining -= i;
        subset.push_back(i);
    }
```

**Why it works.** We greedily take the largest affordable element. Since
{1, ..., i-1} can sum to any value in [0, i(i-1)/2], any remaining shortfall
after taking i is still achievable.

### 5.3 Fixed-size subset sums

**Claim.** For fixed size k (1 <= k <= n), the achievable subset sums from
{1, ..., n} using exactly k elements form the contiguous range:

    [k(k+1)/2, k(2n-k+1)/2]

The lower bound is 1+2+...+k. The upper bound is (n-k+1)+...+n.

**Greedy construction for target sum t:**

1. Start with the minimum subset A = {1, 2, ..., k}, sum = k(k+1)/2.
2. Compute deficit d = t - k(k+1)/2.
3. For i = k, k-1, ..., 1 (right to left):
   - Increase a[i] by min(d, n-k+i - a[i]).
   - Subtract the increase from d.
   - Stop when d = 0.

This "shifts" elements rightward one at a time, preserving distinctness.

---

## 6. Bracket Sequences

### 6.1 Validity condition

A string s of '(' and ')' is a valid bracket sequence iff:
1. Assign +1 to '(' and -1 to ')'.
2. **Total sum = 0** (equal opens and closes).
3. **All prefix sums >= 0** (never more closes than opens at any point).

### 6.2 Minimum removals to make valid

Let r(n) = final prefix sum (excess opens). Let g = min prefix sum (most
negative dip).

**Removals needed:** r(n) + 2*|g|.

**Strategy:**
- Remove |g| close brackets ')' (from anywhere -- the first |g| are simplest).
  This lifts the minimum prefix sum to 0.
- Remove r(n) + |g| open brackets '(' from the end of the string.
  This brings the total sum to 0.

**Why.** Each ')' we remove fixes one unit of the negative dip (+1 to all
subsequent prefix sums) and reduces the total by 1 (so we need one more '(' to
remove). The |g| close removals fix the prefix condition; the remaining r(n)
open removals fix the sum condition.

---

## 7. Technique: Coordinate Compression

**What it does.** Maps large/negative/sparse values to small contiguous indices
[1, 2, ..., k] preserving relative order.

**When to use:**
- Values up to 1e18 but you need them as array indices.
- Only ordering matters, not actual distances.
- Number of distinct values is manageable (< ~10^6).

**Implementation:**

```cpp
// Step 1: Collect unique values
set<long long> st;
for (auto x : values) st.insert(x);

// Step 2: Convert to vector
vector<long long> coords(st.begin(), st.end());

// Step 3: Map via binary search (1-based)
auto compress = [&](long long x) -> int {
    return lower_bound(coords.begin(), coords.end(), x)
           - coords.begin() + 1;
};
```

**Memory constraint.** A segment tree over k values needs ~4k nodes. At k =
10^6, this is safe. At k > 10^7, you risk MLE. In that case, use treaps,
ordered maps, or policy-based trees.

**Critical rules:**
- Collect ALL values before compressing.
- Use lower_bound, not upper_bound.
- Be consistent with 0-based vs 1-based indexing.

---

## 8. Technique: Delting (Global Offset)

**Problem.** Queries that add the same value to ALL elements in a data
structure are O(n) naively.

**Solution.** Maintain a global offset `aux = 0`. Store adjusted values.

**Invariant:** `real_value = stored_value + aux`.

| Operation              | Action                     | Cost |
|------------------------|----------------------------|------|
| Add x to all elements  | `aux += x`                 | O(1) |
| Insert value v         | Store `v - aux`            | O(1) |
| Query a value          | Return `stored + aux`      | O(1) |
| Update one element by x| `stored += x` (aux unchanged)| O(1)|

**Why it works.** All elements share the same offset. Global shifts become O(1).
Comparisons between stored values are preserved (the offset cancels).

---

## 9. Technique: 2D to 1D Reduction

**Core idea.** Fix one dimension (e.g., column pair [L, R]) and compress the
other dimension into a 1D array.

**Steps:**
1. For every column pair [L, R], compute row_cost[i] = contribution of row i
   across columns L..R.
2. Solve a 1D problem on row_cost[]: e.g., longest subarray with sum <= S.
3. If feasibility is **monotonic** in vertical expansion (adding a row can only
   worsen/improve feasibility), use **two pointers** on rows for O(rows) per
   column pair.

**Overall complexity:** O(cols^2 * rows) -- often acceptable for n <= 500.

**When two pointers apply:**
- Subsegment monotonic: if [l, r] is feasible, so is any [l', r'] inside it.
  Typical for "cost <= limit" where cost increases with more rows.

**When two pointers FAIL:**
- Non-monotonic constraints (XOR, exact equality).
- Non-contiguous interactions.

**Mental checklist:**
1. Can I fix two sides of the rectangle?
2. Can I compress the rest into 1D?
3. Does feasibility change monotonically when extending?
4. If yes to all -> two pointers.

---

## 10. Technique: Top-K Online Maintenance (Two-Set)

**Problem.** Dynamically maintain the K best elements from a changing
collection, supporting insertions and deletions.

**Data structure.** Two multisets:
- `S_best`: the current K best elements.
- `S_rest`: everything else.

**Invariant:** Every element in S_best is "better" than every element in S_rest.

**Insert x:**
```
if |S_best| < K:
    insert x into S_best
else:
    let y = worst element in S_best
    if x better than y:
        move y from S_best to S_rest
        insert x into S_best
    else:
        insert x into S_rest
```

**Delete x:**
```
if x in S_best:
    remove x from S_best
    promote best element from S_rest into S_best
else:
    remove x from S_rest
```

**Correctness.** Exchange argument: if any element in S_rest were better than
one in S_best, swapping them strictly improves the solution. The invariant
prevents this.

**Time:** O(log N) per operation using multisets.

**Mental model:** "K privileged slots, always occupied by the best available."

---

## 11. Technique: Pitcher Pouring

**What it is.** An invariant-driven technique for maintaining optimal values
dynamically using local rebalancing between a small number of containers.

**Core structure.** Two containers (LEFT pitcher, RIGHT pitcher) partitioning
elements by their relationship to the current optimum (e.g., elements below vs
above the median).

**The invariant** (most important part):
- All elements in LEFT <= all elements in RIGHT.
- Size or weight constraints are satisfied.
- One pitcher determines the "current optimal value."

**Rebalancing ("pouring"):** After each insert/delete, move O(1) boundary
elements between pitchers to restore the invariant.

**Why it works.** Between consecutive states, the optimum shifts by at most a
small amount. So only a small number of elements need to move.

**When to use:**
- Dynamic set with insert/delete.
- Need to maintain an optimal value (median, pivot, balance point).
- Updates are incremental (one element at a time).
- Recomputing from scratch is too slow.

**Key test:** "If I knew the answer for the previous state, could I fix it
quickly for the next state?" If yes -> pitcher pouring.

**When it fails:** Optimal solution jumps wildly between updates, or many
elements need to move per update (pouring cost becomes O(n)).

---

## 12. Technique: Maximum Marginal Gain (Discrete)

**Problem type.** Minimize a sum of independent convex terms:

    S = sum of f_i(x_i)

subject to a fixed budget of unit operations (+/- 1) on the variables.

**Key insight.** At each step, spend the operation where the **marginal gain**
(decrease in S) is largest.

**Application to squared error.** Let d_i = A[i] - B[i], and the cost per
element is d_i^2.

Change from reducing |d_i| by 1:

    (|d_i| - 1)^2 - d_i^2 = -2|d_i| + 1

The larger |d_i| is, the more we save. So: **always reduce the largest |d_i|
first.**

**Implementation:**

```cpp
priority_queue<int> pq;  // max-heap of |d_i|
for (int i = 0; i < n; i++) pq.push(abs(A[i] - B[i]));

while (operations > 0 && !pq.empty()) {
    int top = pq.top(); pq.pop();
    if (top == 0) break;
    pq.push(top - 1);
    operations--;
}
```

**Why greedy is correct:**
1. Each term is independent and convex.
2. Marginal gain strictly decreases as |d_i| decreases.
3. Exchange argument: any optimal solution can be rearranged to reduce larger
   |d_i| first without increasing cost.

---

## 13. Logarithm Trick for Products

**Problem.** Products overflow; comparing products is hard.

**Solution.** Store log(value) instead of value.

| Original operation | Log domain        |
|--------------------|-------------------|
| Product a*b        | log(a) + log(b)   |
| Ratio a/b          | log(a) - log(b)   |
| Compare a*b vs c*d | log(a)+log(b) vs log(c)+log(d) |
| Range product       | Prefix sum of logs |

**Recovering the value:** exp(sum_of_logs). Only do this when actually needed --
often comparison is sufficient.

**Constraint:** All values must be > 0 (log is undefined for 0).

---

## 14. Counting Occurrences in Subarrays

### 14.1 Static (no updates): Hash map + binary search

**Preprocessing:** For each value x, store its sorted list of positions.

```cpp
unordered_map<int, vector<int>> pos;
for (int i = 1; i <= n; i++) pos[a[i]].push_back(i);
```

**Query (count of x in [l, r]):**

```cpp
auto& v = pos[x];
int ans = upper_bound(v.begin(), v.end(), r)
        - lower_bound(v.begin(), v.end(), l);
```

**Complexity:** O(n) preprocessing, O(log n) per query.

### 14.2 Dynamic (with updates): Hash map + ordered set

Replace vectors with sets to support insert/erase:

```cpp
unordered_map<int, set<int>> pos;
```

**Update A[i] from old_val to new_val:**

```cpp
pos[old_val].erase(i);
pos[new_val].insert(i);
```

**Query:** Use lower_bound/upper_bound on the set. Note: `distance(L, R)` on
set iterators is O(k), not O(log n). For guaranteed O(log n), use an
order-statistics tree (policy-based).

### 14.3 General: Merge sort tree

Each segment tree node stores a **sorted vector** of the values in its segment.

- **Build:** Merge children's sorted vectors. O(n log n) total.
- **Query [l, r] for count of x:** Visit O(log n) nodes, binary search each.
  O(log^2 n) per query.
- **Update:** Replace old value in each ancestor's sorted vector. O(log^2 n).
- **Memory:** O(n log n).

---

## 15. Sliding Window Counting of Intersecting Segments

**Setup.** Given segments [l_i, r_i] and a sliding window of fixed size d.

**Key observation.** A segment [l, r] intersects window [x, x+d-1] iff
l <= x+d-1 AND r >= x.

**Event-based approach:**
- Precompute: left[i] = number of segments starting at i.
  right[i] = number of segments ending at i.
- Initial count: sum of segments with l <= d.
- Slide from x to x+1:
  - New intersections: segments starting at x+d (they now overlap).
  - Lost intersections: segments ending at x (they no longer overlap).

```cpp
cnt += left[x + d];
cnt -= right[x];
```

**Complexity:** O(n + k) total, O(1) per window shift.

**Pattern to remember:** "Convert interval intersection into +1/-1 events at
boundaries, maintain running count."

---

## 16. Skipping Multiples with Memoization (Dynamic MEX-like)

**Problem.** Maintain a set S supporting:
- `+ x`: insert x into S.
- `? k`: find smallest multiple of k NOT in S.

**Key idea.** Maintain `f[k]` = last confirmed multiplier for k. All multiples
0*k, 1*k, ..., f[k]*k are known to be in S. Start the next search from f[k].

```cpp
set<int> s;
unordered_map<int, int> f;

int query(int k) {
    for (int i = f[k]; ; i++) {
        if (s.find(i * k) == s.end()) {
            f[k] = i;
            return i * k;
        }
    }
}
```

**Why it is fast (amortized).** Each loop iteration "consumes" a multiple of k
that exists in S, advancing f[k]. Each element x in S can be consumed only for
divisors of x. Since d(x) is small (~100 for x <= 10^9), total work across all
queries is O(N * avg_divisors) ~ O(N log N).
