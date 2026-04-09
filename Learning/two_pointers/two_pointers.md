# Two Pointers: A Rigorous Treatment

---

## Section 1: The Monotonicity Principle

### Setting

Let $a[0], a[1], \ldots, a[n-1]$ be a sequence. A **segment** is a pair $[l, r]$ with
$0 \le l \le r \le n-1$, representing the contiguous subsequence $a[l], a[l+1], \ldots, a[r]$.

Let $f$ be a predicate on segments:

$$f : \{[l,r] : 0 \le l \le r \le n-1\} \to \{\text{good}, \text{bad}\}$$

Two pointers is applicable when $f$ exhibits one of two forms of monotonicity.

### Definition 1 (Subsegment Monotonicity)

$f$ satisfies **subsegment monotonicity** if whenever $[l, r]$ is good and
$l \le l' \le r$, then $[l', r]$ is also good.

Equivalently: shrinking a good segment from the left preserves goodness.

**Intuition.** The "harder" direction is expanding the segment. If a segment is good,
making it shorter (from the left) cannot break the property. This arises naturally when
the condition is "the sum/count/weight of the segment is at most $k$" --- removing
elements from the left can only decrease the sum.

### Definition 2 (Supersegment Monotonicity)

$f$ satisfies **supersegment monotonicity** if whenever $[l, r]$ is good and
$l \le r' \le r$, then $[l, r']$ is also good.

Equivalently: shrinking a good segment from the right preserves goodness.

**Note.** These two forms are symmetric. Every problem satisfying one can be rephrased
to satisfy the other by reversing the array or swapping the roles of $l$ and $r$.
In practice, subsegment monotonicity is the more common formulation.

### Theorem 1 (Monotonicity of the Boundary Function)

Suppose $f$ satisfies subsegment monotonicity. For each $l$, define:

$$R(l) = \max\{r : f([l, r]) = \text{good}\}$$

with the convention that $R(l) = l - 1$ if no segment starting at $l$ is good.
Assume that the empty/single-element segments are good (the typical case).

**Claim.** $R(l)$ is non-decreasing in $l$. That is, $l_1 < l_2 \implies R(l_1) \le R(l_2)$.

**Proof.**

Let $l_1 < l_2$ and let $r_1 = R(l_1)$. Then $[l_1, r_1]$ is good by definition.
Since $l_1 < l_2 \le r_1$ (assuming $l_2$ is a valid starting index within
$[l_1, r_1]$; if $l_2 > r_1$, then $R(l_2) \ge l_2 > r_1 = R(l_1)$ trivially
since single-element segments are good), subsegment monotonicity gives us that
$[l_2, r_1]$ is good. Therefore:

$$R(l_2) = \max\{r : [l_2, r] \text{ is good}\} \ge r_1 = R(l_1)$$

$\blacksquare$

### Corollary 1 (Linear Enumeration)

Since $R(l)$ is non-decreasing and takes values in $\{0, 1, \ldots, n-1\}$, we can
enumerate all pairs $(l, R(l))$ for $l = 0, 1, \ldots, n-1$ in $O(n)$ total time.

**Proof.** Maintain a pointer $r$ that starts at 0 and only moves forward.
When processing index $l$, advance $r$ from its current position (which is $R(l-1)$)
to $R(l)$. Each step increases $r$ by 1. Since $r$ starts at 0 and ends at most at
$n-1$, the total number of forward steps across all iterations of $l$ is at most $n$.
Combined with the $n$ iterations of the outer loop, the total work is $O(n)$.
$\blacksquare$

This corollary is the entire foundation of two pointers. Everything else is application.

---

## Section 2: The Two Canonical Patterns

Both patterns are direct implementations of Corollary 1. They differ in which quantity
is being optimized: the longest good segment starting at each $l$, or the shortest
good segment ending at each $r$.

### Pattern A: Enumerate Longest Good Segments Starting at Each $l$

```
r = 0
for l in 0 to n-1:
    while r < n and canExtend(l, r):   // test if [l, r] is still good after adding a[r]
        add(a[r])
        r += 1
    // Now [l, r-1] is the maximal good segment starting at l.
    // Process the answer for l here.
    remove(a[l])
```

**Precondition.** $f$ satisfies subsegment monotonicity. The functions `add`, `remove`,
and `canExtend` maintain state such that `canExtend(l, r)` returns true iff
$f([l, r]) = \text{good}$.

**Loop invariant.** At the start of iteration $l$, the internal state reflects the
segment $[l, r-1]$ (or the empty state if $r = l$), and $r = R(l-1) + 1$ (i.e.,
$r$ is positioned one past the previous answer).

**Why `remove(a[l])` works.** After processing $l$, we need the state to reflect
$[l+1, r-1]$. Since the state currently reflects $[l, r-1]$, removing $a[l]$
transitions to $[l+1, r-1]$. Subsegment monotonicity guarantees this segment is
good (it is a subsegment of $[l, r-1]$), so the invariant holds.

### Pattern B: Enumerate Shortest Good Segments Ending at Each $r$

```
l = 0
for r in 0 to n-1:
    add(a[r])
    while not isGood(l, r):
        remove(a[l])
        l += 1
    // Now [l, r] is the minimal good segment ending at r.
    // Process the answer for r here.
```

**Precondition.** Here the monotonicity is reversed: if $[l, r]$ is good, then
$[l, r']$ is good for all $r' \ge r$ (supersegment monotonicity on "good",
or equivalently: if the segment is bad, shrinking from the left can only help).

This pattern is natural when the condition is "at least $k$" --- expanding can only
help, so we find the tightest (shortest) good segment.

### Theorem 2 (Both Patterns are $O(n)$)

**Proof.** In Pattern A, the pointer $l$ advances from 0 to $n-1$ (exactly $n$ steps).
The pointer $r$ only moves forward and traverses from 0 to at most $n$ (at most $n$
steps total). Each step performs one `add` or one `remove`. Total operations: at most
$2n$.

The identical argument applies to Pattern B with the roles exchanged. $\blacksquare$

---

## Section 3: Reduction from Binary Search --- A Deep Connection

### The Binary Search Version

Consider a problem where, for each $l$, we want $R(l)$. If we know nothing about the
relationship between $R(l)$ and $R(l+1)$, we can compute $R(l)$ via binary search
over $r$, assuming we have an $O(1)$ or $O(\log n)$ oracle for $f([l, r])$.

This gives $O(n \log n)$ overall.

### The Two-Pointer Improvement

Theorem 1 tells us $R(l) \le R(l+1)$. Binary search ignores this: it resets the
search range $[l, n-1]$ at each step. Two pointers exploits it: the search for
$R(l+1)$ begins at $R(l)$, not at $l+1$.

**The two-pointer technique is amortized binary search where the search pointer
carries state forward between iterations.**

Formally, binary search solves $n$ independent search problems in $O(\log n)$ each.
Two pointers solves $n$ dependent search problems in amortized $O(1)$ each by
exploiting the monotone dependency $R(l) \le R(l+1)$.

### When to Use Which

- **Binary search**: when $f$ is easy to evaluate for arbitrary $[l, r]$ (e.g., using
  prefix sums) but the window state is hard to maintain incrementally.
- **Two pointers**: when the window state can be maintained incrementally with $O(1)$
  `add`/`remove`, and $R(l)$ is monotone.
- **Two pointers + data structure**: when the state requires a nontrivial structure
  (see the sliding window guide).

In all cases, the underlying principle is the same: monotonicity of $R(l)$.

---

## Section 4: The add/remove/isGood Framework

### Abstract Interface

The two-pointer technique maintains a **window state** $S$ representing the current
segment $[l, r]$. The interface consists of three operations:

- **add(x)**: transition $S$ from representing $[l, r]$ to representing $[l, r+1]$
  (or $[l-1, r]$, depending on which end is growing).
- **remove(x)**: the inverse --- transition $S$ from representing $[l, r]$ to
  representing $[l+1, r]$ (or $[l, r-1]$).
- **isGood()**: query $S$ to determine whether the current segment satisfies $f$.

### The Invertibility Requirement

**The critical constraint: `remove` must be the exact inverse of `add`.**

This seems obvious but has deep consequences. It limits two pointers to maintaining
aggregates under **invertible operations**:

| Aggregate | add | remove | Invertible? |
|-----------|-----|--------|-------------|
| Sum | $S \mathrel{+}= x$ | $S \mathrel{-}= x$ | Yes |
| Product | $S \mathrel{*}= x$ | $S \mathrel{/}= x$ | Yes (if no zeros) |
| XOR | $S \mathrel{\oplus}= x$ | $S \mathrel{\oplus}= x$ | Yes (self-inverse) |
| Count | $c[x]\mathrel{+}{+}$ | $c[x]\mathrel{-}{-}$ | Yes |
| Frequency map | insert $x$ | erase one copy of $x$ | Yes (use multiset or freq array) |
| Minimum | $\min(S, x)$ | ??? | **No** |
| Maximum | $\max(S, x)$ | ??? | **No** |
| GCD | $\gcd(S, x)$ | ??? | **No** |

When the operation is **not invertible**, you cannot use plain two pointers for the
aggregate. You still use two pointers for the window management (moving $l$ and $r$),
but you need a **sliding window data structure** to maintain the aggregate. This is
the subject of the sliding window guide.

### A Subtle Point: Composition of Invertible Operations

Often the predicate $f$ involves multiple aggregates. For example: "the sum is at most
$k$ AND the number of distinct elements is at most $d$." Each individual aggregate
must be independently invertible. The conjunction (or disjunction) of monotone
predicates is monotone, so two pointers still applies to the combined predicate as
long as each component can be maintained.

---

## Section 5: Classic Two-Pointer Configurations

The phrase "two pointers" encompasses several geometric configurations. They all share
the principle that two indices traverse the array with bounded total movement, but
they differ in how the indices move.

### Configuration 1: Sliding Window (Co-directional)

Both $l$ and $r$ move left-to-right, with $l \le r$.

This is the canonical configuration from Sections 1--4. It applies to subarray
problems where the predicate has segment monotonicity.

**Total pointer movement:** $l$ moves at most $n$ steps, $r$ moves at most $n$ steps.
Total: $O(n)$.

### Configuration 2: Converging Pointers (Bi-directional)

$l$ starts at 0, $r$ starts at $n-1$. They move inward: $l$ can only increase,
$r$ can only decrease. They meet when $l \ge r$.

**The paradigmatic problem: Two Sum on a sorted array.**

Given sorted $a[0] \le a[1] \le \ldots \le a[n-1]$ and target $T$, find $l < r$
with $a[l] + a[r] = T$.

**Algorithm:**
```
l = 0, r = n - 1
while l < r:
    s = a[l] + a[r]
    if s == T: return (l, r)
    if s < T: l += 1
    if s > T: r -= 1
return NOT_FOUND
```

**Theorem 3.** If a solution $(l^*, r^*)$ exists, the above algorithm finds a solution.

**Proof.**

Define the **search space** at any point as $\{(i, j) : l \le i < j \le r\}$.
We show the following invariant: if a solution exists, at least one solution is
always in the current search space.

*Base case:* initially $l = 0, r = n-1$, so all pairs are in the search space.

*Inductive step:* Suppose the invariant holds, i.e., there exists a solution
$(l^*, r^*)$ with $l \le l^* < r^* \le r$. Consider the current sum
$s = a[l] + a[r]$.

- Case $s < T$: we set $l \leftarrow l + 1$. We must show $l^* \ne l$.
  If $l^* = l$, then $a[l^*] + a[r^*] = T$, but $r^* \le r$, so
  $a[l] + a[r^*] = T$. Since $a$ is sorted and $r^* \le r$, we have
  $a[r^*] \le a[r]$, hence $a[l] + a[r] \le a[l] + a[r^*] + (a[r] - a[r^*])$.
  But wait --- more directly: $a[l] + a[r] \ge a[l] + a[r^*] = T$ (since
  $a[r] \ge a[r^*]$), contradicting $s < T$. Hence $l^* > l$, so $l^* \ge l + 1$,
  and the solution remains in the search space.

- Case $s > T$: symmetric argument shows $r^* < r$, so setting $r \leftarrow r - 1$
  preserves the invariant.

- Case $s = T$: we found a solution.

Since each step reduces $r - l$ by 1, the algorithm terminates in at most $n$
steps. $\blacksquare$

**Key insight.** At each step, we eliminate the current $l$ or $r$ from consideration.
The proof shows this is safe: if $s < T$, then $a[l]$ is too small to pair with
*anything* remaining (since $a[r]$ is the largest remaining element and even
$a[l] + a[r] < T$). Dually for $s > T$.

### Configuration 3: Parallel Pointers (Merge-style)

Two pointers $i$ and $j$ traverse two different arrays $a[0..n-1]$ and $b[0..m-1]$,
both moving forward.

**The paradigmatic problem: Merging two sorted arrays.**

```
i = 0, j = 0
while i < n and j < m:
    if a[i] <= b[j]: output a[i]; i++
    else: output b[j]; j++
// flush remaining elements
```

**Complexity:** $O(n + m)$. Each step advances at least one pointer, and neither
pointer exceeds its array length.

This configuration also applies to:
- Set intersection/union of sorted lists
- Comparing two sorted sequences
- The merge step of merge sort (which is, in a sense, the origin of the name
  "two pointers")

---

## Section 6: Applications Matrix

Rather than cataloging specific problems, we classify the **problem types** where
two pointers is the natural approach. The classification is by the form of the
predicate $f$ and the configuration used.

### Sliding Window Applications (Configuration 1)

| Problem Type | Predicate $f([l,r])$ | Monotonicity | Pattern |
|---|---|---|---|
| Longest subarray with sum $\le k$ | $\text{sum}(l,r) \le k$ | Subsegment | A |
| Shortest subarray with sum $\ge k$ (positive elements) | $\text{sum}(l,r) \ge k$ | Supersegment | B |
| Subarray with exact sum $k$ (positive elements) | $\text{sum}(l,r) \le k$ | Subsegment | A (check equality at boundary) |
| At most $d$ distinct elements | $|\text{distinct}(l,r)| \le d$ | Subsegment | A |
| Longest substring without repeats | all chars distinct | Subsegment | A |
| Minimum window containing all target chars | contains all targets | Supersegment | B |

**Counting trick.** To count the number of subarrays with sum exactly $k$ (positive
elements): count subarrays with sum $\le k$ minus count with sum $\le k-1$. Each
count is computable via two pointers. Alternatively, for each $l$, if $R(l)$ is the
maximal $r$ with sum $\le k$, then the number of good subarrays starting at $l$ is
$R(l) - l + 1$ (all subsegments of a good segment are good, by monotonicity).

### Converging Pointer Applications (Configuration 2)

| Problem Type | Sorted? | Notes |
|---|---|---|
| Two sum (find pair with target sum) | Yes | Theorem 3 |
| Three sum | Sort first | Fix one element, two-pointer on remainder |
| Container with most water | N/A | Width decreases, need height increase |
| Trapping rain water | N/A | Process from both ends inward |

### Parallel Pointer Applications (Configuration 3)

| Problem Type | Notes |
|---|---|
| Merge sorted arrays | Foundation of merge sort |
| Sorted list intersection | Advance the smaller pointer |
| Sorted list symmetric difference | Output when pointers disagree |

### A Note on Three Sum

Three sum (find $a[i] + a[j] + a[k] = T$ in sorted array) is solved by fixing $i$
and applying two-pointer (converging) on the subarray $a[i+1 \ldots n-1]$. The outer
loop is $O(n)$, and each inner two-pointer pass is $O(n)$, giving $O(n^2)$ total.
This is a clean example of how two pointers composes with an outer enumeration.

---

## Appendix: Common Pitfalls

1. **Forgetting to check monotonicity.** Two pointers is wrong if the predicate is
   not monotone. Example: "subarray with sum exactly $k$" when elements can be
   negative --- $R(l)$ is not monotone, so two pointers does not apply. (Use
   prefix sums + hash map instead.)

2. **Off-by-one in the window.** In Pattern A, after the inner while loop, the good
   segment is $[l, r-1]$, not $[l, r]$. In Pattern B, the good segment is $[l, r]$.
   Be precise about whether $r$ points to the last included element or one past it.

3. **Non-invertible remove.** If your `remove` operation is not a true inverse of
   `add` (e.g., maintaining max via a single variable), the state becomes
   inconsistent when the left pointer advances. Use a sliding window structure.

4. **Empty segments.** Ensure your initial state and loop handle the case $l = r$
   (single element) and $l > r$ (empty segment, which can occur in Pattern A when
   even a single element violates $f$).
