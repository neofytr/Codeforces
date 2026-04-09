# Binary Search: A Rigorous Treatment

---

## 1. The Mathematical Foundation

### 1.1 The Core Abstraction

Binary search is not about sorted arrays. It is about **monotone predicates**.

**Definition 1.1 (Monotone Predicate).** Let `D = {0, 1, ..., n-1}` be a finite totally ordered domain. A predicate `P: D -> {T, F}` is called *left-true monotone* if:

    P(k) = F  ==>  P(k') = F   for all k' >= k

Equivalently, there exists a *transition point* `t in {-1, 0, ..., n-1}` such that:

    P(i) = T   for all i <= t
    P(i) = F   for all i > t

where `t = -1` means P is everywhere false, and `t = n-1` means P is everywhere true.

Symmetrically, P is *left-false monotone* if P(k) = T implies P(k') = T for all k' >= k. Every result below applies with the obvious reversal.

The transition point t completely characterizes P. Binary search finds t.

### 1.2 Why O(log n)?

**Theorem 1.2 (Binary Search Correctness and Complexity).** Given a left-true monotone predicate P on a domain of size n, the transition point t can be determined with exactly ceil(log_2(n + 1)) evaluations of P.

**Proof.** We maintain an interval [lo, hi] such that:

- **Invariant I**: P(lo) = T (or lo is a sentinel below the domain) and P(hi) = F (or hi is a sentinel above the domain).

At each step, we evaluate P at the midpoint m = floor((lo + hi) / 2). By monotonicity:

- If P(m) = T, then the transition point satisfies t >= m. We set lo = m, preserving I.
- If P(m) = F, then t < m. We set hi = m, preserving I.

The interval length hi - lo starts at most n + 1 and strictly decreases by at least a factor of 2 each iteration (proof in Section 2). After k iterations, the interval has length at most (n + 1) / 2^k. When this length reaches 1 (i.e., hi = lo + 1), the transition point is exactly lo. This requires:

    (n + 1) / 2^k <= 1   <==>   k >= log_2(n + 1)   <==>   k = ceil(log_2(n + 1))

**QED.**

### 1.3 Information-Theoretic Optimality

There are n + 1 possible values for the transition point: t in {-1, 0, ..., n-1}. Each evaluation of P returns one bit of information. Therefore any algorithm requires at least ceil(log_2(n + 1)) evaluations. Binary search achieves this bound exactly. It is *information-theoretically optimal*.

---

## 2. The Canonical Template

### 2.1 The Code

The following template is both correct and immune to the off-by-one errors that plague other formulations. It uses two sentinels: `left = -1` (a virtual index where P is defined to be T) and `right = n` (a virtual index where P is defined to be F).

```cpp
// Precondition: P is left-true monotone on {0, ..., n-1}.
// P(-1) is "virtually" T; P(n) is "virtually" F.
// Postcondition: left = t (last T), right = t+1 (first F).
int left = -1, right = n;
while (right > left + 1) {
    int mid = left + (right - left) / 2;
    if (P(mid))
        left = mid;
    else
        right = mid;
}
// left is the last index where P holds (or -1 if P is everywhere false).
// right is the first index where P fails (or n if P is everywhere true).
```

### 2.2 Formal Verification

We prove four properties.

**Property 1: The invariant is maintained.**

*Loop invariant*: At the start of each iteration, P(left) = T (or left = -1) and P(right) = F (or right = n), and right > left + 1.

*Base case*: Initially left = -1 (sentinel T), right = n (sentinel F), and n >= 0 implies right > left + 1 when n >= 1. (When n = 0, right = 0 and left = -1, so right = left + 1 and the loop does not execute, which is correct: the search space is empty.)

*Inductive step*: Suppose the invariant holds at the start of an iteration. We compute mid and evaluate P(mid).
- If P(mid) = T: we set left = mid. Now P(left) = T. right is unchanged, so P(right) = F. We must verify right > left + 1 still holds for the *next* iteration's entry check -- but this is handled by the loop condition, not the invariant. The invariant on P-values is preserved.
- If P(mid) = F: we set right = mid. Now P(right) = F. left is unchanged, so P(left) = T. Same reasoning.

**Property 2: The loop terminates.**

Define the *gap* g = right - left. Initially g = n + 1. We claim g strictly decreases each iteration.

Before the iteration: g = right - left >= 2 (since we entered the loop).

After setting left = mid: new gap = right - mid. Since mid = left + floor((right - left)/2) and right - left >= 2, we have:

    right - mid = right - left - floor((right - left)/2) = ceil((right - left)/2)

Since right - left >= 2, ceil((right - left)/2) >= 1 and ceil((right - left)/2) <= right - left - 1 < right - left = g. So the gap strictly decreases.

After setting right = mid: new gap = mid - left = floor((right - left)/2). Since right - left >= 2, this is >= 1 and < right - left = g. So the gap strictly decreases.

Since g is a positive integer that strictly decreases, the loop terminates.

**Property 3: On exit, left and right are adjacent.**

The loop exits when right <= left + 1. Combined with the invariant that P(left) = T and P(right) = F (so right > left since T != F and P is monotone), we get right = left + 1 exactly.

**Property 4: mid never equals left or right (no infinite loop).**

Since right > left + 1 upon loop entry, we have right - left >= 2. Then:

    mid = left + floor((right - left) / 2)

Since right - left >= 2, floor((right - left) / 2) >= 1, so mid >= left + 1 > left.

Also, floor((right - left) / 2) < right - left (because for any integer k >= 2, floor(k/2) < k), so mid < left + (right - left) = right.

Therefore left < mid < right, and both branches (left = mid, right = mid) strictly shrink the interval. **QED.**

### 2.3 The Midpoint Formula

We use `mid = left + (right - left) / 2` instead of `mid = (left + right) / 2` to prevent integer overflow. When left and right are both large positive values (say, close to 2^62), their sum overflows a 64-bit integer. The subtraction form is always safe because right - left >= 0 and fits in the same integer type.

This is not pedantry. In the splitArray problem, right can be as large as LLONG_MAX. Overflow is real.

---

## 3. Integer Binary Search: The Four Variants

Every integer binary search problem reduces to finding the transition point of a monotone predicate. The four standard variants are obtained by choosing the predicate and reading off the answer from left or right.

### 3.1 Unified Framework

Given a sorted array `a[0..n-1]` and a target value x:

| Variant | Predicate P(i) | P is T when... | Answer | Equivalent STL |
|---|---|---|---|---|
| First element >= x | a[i] < x | element is too small | **right** | `lower_bound` |
| First element > x | a[i] <= x | element is not too big | **right** | `upper_bound` |
| Last element <= x | a[i] <= x | element fits | **left** | `upper_bound - 1` |
| Last element < x | a[i] < x | element strictly less | **left** | `lower_bound - 1` |

In every case, the predicate is left-true monotone on the sorted array. The template from Section 2 applies directly.

### 3.2 Derivation: First Element >= x (lower_bound)

Define P(i) = (a[i] < x). Since a is sorted, P is left-true monotone: if a[i] < x, then a[j] < x for all j <= i.

After binary search:
- left = last index where a[i] < x
- right = first index where a[i] >= x

So right is the answer. If right = n, no element >= x exists.

```cpp
int left = -1, right = n;
while (right > left + 1) {
    int mid = left + (right - left) / 2;
    if (a[mid] < x) left = mid;
    else right = mid;
}
// right = first index with a[right] >= x, or n if none exists.
// This is exactly what std::lower_bound returns (as an index).
```

### 3.3 Derivation: Last Element <= x (upper_bound - 1)

Define P(i) = (a[i] <= x). Left-true monotone on a sorted array.

After binary search:
- left = last index where a[i] <= x
- right = first index where a[i] > x

So left is the answer. If left = -1, no element <= x exists.

```cpp
int left = -1, right = n;
while (right > left + 1) {
    int mid = left + (right - left) / 2;
    if (a[mid] <= x) left = mid;
    else right = mid;
}
// left = last index with a[left] <= x, or -1 if none exists.
```

### 3.4 Derivation: Boolean Array Variants

For a boolean array b[0..n-1] that transitions from F to T (i.e., left-false monotone):

**First T**: Define P(i) = (b[i] == F), which is left-true. Answer = right.

**Last T** (in a T-then-F array): Define P(i) = (b[i] == T), which is left-true. Answer = left.

### 3.5 Relationship to C++ STL

`std::lower_bound(a, a+n, x)` returns an iterator to the first element >= x. This is exactly Variant 1.

`std::upper_bound(a, a+n, x)` returns an iterator to the first element > x. This is exactly Variant 2 (answer = right).

The key insight is that lower_bound and upper_bound are not two different algorithms. They are the *same* binary search with different predicates: `a[i] < x` vs. `a[i] <= x`.

---

## 4. Binary Search on the Answer Space

This is the most powerful application of binary search, and the one that appears most frequently in competitive programming. The idea is to transform an optimization problem into a sequence of decision problems.

### 4.1 The Reduction Theorem

**Theorem 4.1 (Optimization-Decision Reduction).** Let f: D -> R be an objective function over a discrete or continuous domain D, and let C(k) denote the decision problem "does there exist x in D with f(x) <= k?" (or >= k for maximization). If:

1. C(k) is monotone in k: C(k) = T implies C(k') = T for all k' >= k (for minimization), and
2. C(k) is computable in time T(n),

then the optimal value of f can be found in O(T(n) * log(|R|)) time, where |R| is the size of the range of possible answers.

**Proof.** The predicate P(k) = C(k) is left-false monotone (for minimization: once feasible, stays feasible as we relax the bound). The transition point is the minimum feasible k, which is the optimal value. Apply binary search. **QED.**

### 4.2 The Art of Predicate Design

The creative step is always the same: (1) identify that the answer space is monotone, (2) design the predicate, (3) implement it efficiently.

#### Example: Rope Cutting (ropes)

**Problem**: Given n ropes of lengths a_1, ..., a_n, cut exactly k pieces of equal length. Maximize the piece length.

**Predicate**: P(x) = "we can cut at least k pieces of length x."

**Monotonicity proof**: If P(x) = T, then for any y <= x, each rope yields at least as many pieces of length y as of length x (since floor(a_i / y) >= floor(a_i / x) when y <= x). So P(y) = T. Hence P is left-true monotone.

**Implementation**: P(x) evaluates in O(n) by summing floor(a_i / x) over all ropes.

**Answer**: left (the largest x where P holds).

```cpp
// From your ropes solution:
bool canCut(double x, int k, vector<double> &arr) {
    int count = 0;
    for (double &val : arr) {
        count += (int)(val / x);
        if (count >= k) return true;
    }
    return false;
}
```

#### Example: Cellular Network (cellularNetwork)

**Problem**: Given cities at positions a_1, ..., a_n and towers at positions b_1, ..., b_m, find the minimum radius r such that every city is within distance r of some tower.

**Predicate**: P(r) = "radius r covers all cities."

**Monotonicity proof**: If every city is within distance r of some tower, then certainly every city is within distance r' of some tower for any r' >= r. So P is left-false monotone (F then T).

**Implementation**: For each tower, the interval of cities it covers is [b_j - r, b_j + r]. Check that the union of all such intervals covers {a_1, ..., a_n}. This uses prefix sums on the sorted city array and binary search for interval endpoints, running in O(m log n).

**Answer**: right (the smallest r where P holds).

```cpp
// From your cellularNetwork solution:
// P(right) = T, P(left) = F, so right is the first feasible radius.
while (right != left + 1) {
    int mid = left + ((right - left) >> 1);
    if (can(mid)) right = mid;
    else left = mid;
}
cout << right << endl;
```

#### Example: Maximum Median (maxMedian)

**Problem**: Given array of n elements (n odd), perform at most k increments (+1 to any element) to maximize the median.

**Predicate**: P(x) = "we can make the median at least x using at most k operations."

**Monotonicity proof**: If we cannot achieve median >= x with k operations, we certainly cannot achieve median >= x+1 (since making the median at least x+1 is strictly harder -- every element that needed to reach x now needs to reach x+1, and possibly more elements need raising). So P is left-true monotone.

**Implementation**: Sort the array. The median is a[n/2]. To achieve median >= x, we must raise all elements from a[n/2] through some index to at least x. The cost is computed via prefix sums in O(log n) using binary search for the boundary.

**Answer**: left (the largest achievable median).

#### Example: Split Array (splitArray)

**Problem**: Divide array into k contiguous segments, minimizing the maximum segment sum.

**Predicate**: P(S) = "we can split into at most k segments each with sum <= S."

**Monotonicity proof**: If we can split such that every segment sum is <= S, then we can certainly split such that every segment sum is <= S' for S' >= S (the same partition works). P is left-false monotone.

**Implementation**: Greedy scan in O(n) -- accumulate elements into the current segment; when the sum exceeds S, start a new segment.

**Answer**: right (the minimum feasible maximum sum).

```cpp
// From your splitArray solution -- note the careful monotonicity argument:
// "if f(s) = 1, then f(s + 1) = 1 since if we can divide such that
//  sum <= s, we can divide in such a way that sum <= s + 1"
```

#### Example: Cow Stalls (cowStalls) -- "Maximize the Minimum"

**Problem**: Place k cows in n stalls (sorted positions). Maximize the minimum distance between any two cows.

**Predicate**: P(d) = "we can place k cows such that every pair is at least distance d apart."

**Monotonicity proof**: If we cannot place k cows with minimum distance d, we certainly cannot with minimum distance d' > d (fewer valid placements). P is left-true monotone.

**Implementation**: Greedy: place first cow at stall 0, then each subsequent cow at the first stall that is >= d from the previous. Uses lower_bound, O(k log n).

**Answer**: left (the largest feasible minimum distance).

```cpp
// From your cowStalls solution:
// "if we cannot make the minimum distance between the cows at least x,
//  then we cannot make the minimum distance at least y for any y >= x"
int left = 0;              // possible
int right = 2 * 1e9 + 1;   // impossible
while (right != left + 1) {
    int mid = left + (right - left) / 2;
    if (canMake(mid, k, stalls)) left = mid;
    else right = mid;
}
cout << left << endl;
```

### 4.3 Choosing Sentinels

The sentinels must satisfy the invariant. This means:

- `left` must be a value where P(left) = T (or the "good" side).
- `right` must be a value where P(right) = F (or the "bad" side).

Getting these wrong is a common source of bugs. In your cowStalls solution: left = 0 (trivially possible -- zero distance) and right = 2e9 + 1 (impossible since coordinates are in [0, 10^9]). In splitArray: left = 0 (impossible since elements >= 1, so this is F) and right = LLONG_MAX (trivially possible, so this is T). Note the roles are swapped here: P(left) = F and P(right) = T, which means the predicate is left-false monotone and the answer is right.

**General rule**: Think about which direction is "trivially feasible" and which is "trivially infeasible." Those are your sentinels.

---

## 5. Floating-Point Binary Search

### 5.1 The Problem

When the domain is the real numbers (or an interval of reals), the integer termination condition `right = left + 1` is meaningless. We need a different stopping criterion.

### 5.2 Fixed Iteration Count (The Robust Approach)

Run the binary search for exactly K iterations. After K iterations, the interval width is:

    w_K = (right_0 - left_0) / 2^K

**Theorem 5.1.** For an initial interval of width W and K = 100 iterations:

    w_100 = W / 2^100 = W / (1.267 * 10^30)

For typical contest constraints where W <= 10^9:

    w_100 <= 10^9 / 10^30 = 10^{-21}

This is far below any precision requirement (contest problems typically ask for 10^{-6} to 10^{-9}).

```cpp
// From your ropes solution:
double left = 0;
double right = maxi + 1;
for (int iter = 0; iter < 100; iter++) {
    double mid = left + (right - left) / 2;
    if (canCut(mid, k, arr))
        left = mid;
    else
        right = mid;
}
```

This is the recommended approach. It is simple, always terminates, and provides vastly more precision than needed.

### 5.3 Epsilon-Based Termination

Alternatively, loop while `right - left > eps`:

```cpp
double eps = 1e-9;
while (right - left > eps) {
    double mid = left + (right - left) / 2;
    if (P(mid)) left = mid;
    else right = mid;
}
```

**Danger**: If eps is too small relative to the magnitude of left and right, floating-point granularity may prevent `right - left` from ever dropping below eps. For values around 10^9, a `double` has resolution ~10^{-7} at best (since doubles have ~15-16 significant digits). Setting eps = 1e-9 when the answer is ~10^9 will loop forever.

**Mitigation**: Use *relative* epsilon: `while (right - left > eps * max(1.0, abs(left)))`.

But honestly, just use K = 100 iterations. It is strictly superior in contests.

### 5.4 Floating-Point Pitfalls

1. **Never compare floats with ==.** The expression `right == left + 1` is meaningless for doubles.

2. **Overflow in midpoint.** Use `left + (right - left) / 2`, not `(left + right) / 2`. If left = 10^300 and right = 10^300, their sum overflows to infinity.

3. **Precision loss in predicate evaluation.** If your predicate involves summing many terms, accumulated floating-point error can cause incorrect evaluations near the transition point. This is generally acceptable -- the answer will be within the accumulated error of the true transition point.

4. **Output precision.** Use `cout << fixed << setprecision(k)` where k >= the required number of decimal places. Setting k = 12 or higher is standard practice.

---

## 6. The "Iterative Problems Are Binary Search" Principle

### 6.1 The Observation

A large class of optimization problems in competitive programming have the form:

> Find the minimum (or maximum) value of X such that some condition C(X) holds.

Whenever C is monotone in X, this is binary search on the answer space. The key skill is recognizing monotonicity.

### 6.2 Trigger Phrases

The following problem phrasings almost always indicate binary search on the answer:

| Phrase | Structure | Answer |
|---|---|---|
| "minimum possible maximum" | Minimize k s.t. "all <= k" is feasible | right |
| "maximum possible minimum" | Maximize k s.t. "all >= k" is feasible | left |
| "at least k pieces/groups" | Maximize the threshold parameter | left |
| "at most k operations" | Find the extreme achievable value | left or right |
| "can you achieve X in at most k steps?" | Decision version suggests BS on X | depends |
| "minimum radius / distance / cost to cover" | Minimize feasibility threshold | right |

### 6.3 Why Monotonicity is "Usually" Present

The intuition is simple. Most constraints in optimization problems are **relaxable**: making the bound less restrictive cannot make a feasible solution infeasible.

Formally, if the feasibility set F(k) = {x in D : constraint(x, k) holds} satisfies:

    k_1 <= k_2  ==>  F(k_1) subset of F(k_2)

then feasibility is monotone in k: if F(k_1) is nonempty, so is F(k_2).

This nesting property holds whenever the constraint is of the form "some quantity <= k" or "some quantity >= k" and the quantity depends only on the solution x, not on k itself.

### 6.4 When Binary Search Fails

Binary search on the answer fails when monotonicity does not hold. Examples:

- **Non-monotone feasibility**: "Can we partition the array into k subarrays with equal sums?" Increasing k does not monotonically change feasibility.
- **Discrete, non-convex answer spaces**: "What values of k make the system solvable?" If the answer set is {2, 5, 7}, there is no monotone predicate to exploit.
- **Multi-objective constraints**: When the constraint involves a trade-off between two parameters, fixing one for binary search may not yield monotonicity in the other.

### 6.5 The Meta-Algorithm

When you encounter a min/max optimization problem:

1. **Identify the answer variable** X (what are you optimizing?).
2. **State the decision problem**: "Is it feasible to achieve X <= k?" (or >= k).
3. **Prove or disprove monotonicity**: Does relaxing k always preserve feasibility?
4. **Design the predicate**: Write a function that answers the decision problem.
5. **Choose sentinels**: Find trivially-feasible and trivially-infeasible values of k.
6. **Binary search**: Apply the canonical template.

Step 4 is where the algorithmic creativity lies. The predicate might require greedy algorithms, dynamic programming, graph traversal, or data structures. Binary search is just the outer loop; the predicate is the inner engine.

---

## 7. Formal Complexity Analysis

### 7.1 Time Complexity

**Theorem 7.1.** Let P be a monotone predicate on a domain of size n, computable in time T(P). Binary search finds the transition point in:

    O(log(n) * T(P))   for integer domains
    O(K * T(P))         for real domains with K iterations

**Proof.** The binary search performs ceil(log_2(n+1)) iterations (Theorem 1.2), each requiring one evaluation of P at cost T(P). For real domains, K iterations are performed by design. **QED.**

### 7.2 Concrete Complexities from Your Solutions

| Problem | Domain size | T(P) | Total |
|---|---|---|---|
| ropes | continuous, K=100 | O(n) | O(100n) |
| splitArray | ~10^{18} (LLONG_MAX) | O(n) | O(60n) |
| cowStalls | ~2 * 10^9 | O(k log n) | O(31 * k log n) |
| maxMedian | ~2 * 10^{14} (after doubling) | O(log n) | O(47 * log n) |
| cellularNetwork | ~10^{13} | O(m log n) | O(43 * m log n) |

Note: log_2(10^{18}) ~ 60, log_2(2 * 10^9) ~ 31, log_2(10^{13}) ~ 43.

### 7.3 Space Complexity

Binary search itself uses O(1) additional space. The total space is O(S(P)), where S(P) is the space required to evaluate the predicate. In most cases this is O(n) for storing the input.

### 7.4 Amortized Analysis for Nested Binary Search

When binary search appears inside the predicate (as in maxMedian, where the outer search calls a predicate that performs an inner binary search), the total complexity multiplies:

    O(log(outer_range) * log(inner_range) * T_inner)

In maxMedian: O(log(answer_range) * log(n)) where the inner binary search finds the boundary index in the sorted array.

---

## 8. Advanced Considerations

### 8.1 Handling Edge Cases in the Template

The sentinel-based template handles all edge cases gracefully:

- **Empty domain** (n = 0): left = -1, right = 0. Loop condition 0 > -1 + 1 = 0 is false. Loop does not execute. left = -1 (no valid index), right = 0 (no valid index). Both correctly indicate "not found."

- **All T** (P is true everywhere): Every evaluation sends left = mid. At termination, left = n-1, right = n. The answer (if looking for last T) is left = n-1. Correct.

- **All F** (P is false everywhere): Every evaluation sends right = mid. At termination, left = -1, right = 0. The answer (if looking for first F) is right = 0. Correct.

- **Single element** (n = 1): left = -1, right = 1. Loop runs once: mid = 0. If P(0) = T, left = 0, right = 1, loop ends with left = 0. If P(0) = F, left = -1, right = 0, loop ends.

### 8.2 Exponential Search for Unknown Bounds

When the answer space has no obvious upper bound, use exponential search (doubling) to find one, then binary search within:

```cpp
// From your maxMedian solution:
int x = left;
while (func(x, k, arr, prefix)) {
    if (x <= 0) x++;
    else x *= 2;
}
int right = x + 1;
```

This finds a right sentinel in O(log(answer)) steps, preserving the overall O(log(answer) * T(P)) complexity. The doubling loop performs at most log_2(answer) + 1 predicate evaluations, which is the same order as the subsequent binary search.

### 8.3 Discretization and the Transition to Continuous

Some problems naturally live on the integers but have such large ranges (10^{18}) that we must treat them carefully. The template handles this because:

- `int mid = left + (right - left) / 2` never overflows when left >= 0 and right fits in the integer type.
- The bit-shift variant `(right - left) >> 1` is equivalent for non-negative values and marginally faster.
- When left can be negative (as in the sentinel left = -1), ensure the subtraction right - left does not overflow. For `long long` with right up to ~10^{18} and left = -1, right - left ~ 10^{18} + 1, which fits in a `long long` (max ~9.2 * 10^{18}).

### 8.4 The Invariant as a Proof Technique

The loop invariant `P(left) = T, P(right) = F` is not just a correctness tool -- it is a *design* tool. When you write a binary search:

1. **State the invariant explicitly** (in comments or mentally).
2. **Verify the sentinels satisfy it** before the loop.
3. **Verify each branch preserves it** inside the loop.
4. **Read off the answer** from the invariant at loop exit.

If you cannot state the invariant, you do not understand your binary search. This discipline eliminates the class of bugs where you confuse < with <=, or return left when you should return right.

Your code consistently demonstrates this discipline. In splitArray:

```
int left = 0;          // this is impossible (F)
int right = LLONG_MAX; // this is possible (T)
```

And in cowStalls:

```
int left = 0;              // possible (T)
int right = 2 * 1e9 + 1;   // impossible (F)
```

The comments are the invariant. The code follows from them mechanically.

---

## 9. Summary of the Method

Binary search is a single idea expressed in many forms:

1. **Identify a monotone predicate** on an ordered domain.
2. **Establish sentinels** on opposite sides of the transition point.
3. **Maintain the invariant**: one sentinel in T-land, one in F-land.
4. **Halve the interval** until the sentinels are adjacent.
5. **Read off the answer**: left (last T) or right (first F), depending on what you seek.

The intellectual content is almost entirely in step 1: recognizing that a problem has monotone structure, and designing a predicate that captures it. Steps 2-5 are mechanical once step 1 is done correctly.

This is why binary search is both simple and deep. The template is 7 lines. The art is seeing where it applies.

---

## Appendix: Quick Reference

### Template (Integer)
```cpp
int left = -1, right = n;  // sentinels: P(left)=T, P(right)=F
while (right > left + 1) {
    int mid = left + (right - left) / 2;
    if (P(mid)) left = mid;
    else right = mid;
}
// left = last T, right = first F
```

### Template (Floating-Point)
```cpp
double left = LO, right = HI;  // P(left)=T, P(right)=F
for (int iter = 0; iter < 100; iter++) {
    double mid = left + (right - left) / 2;
    if (P(mid)) left = mid;
    else right = mid;
}
// left ~= right ~= transition point
```

### Complexity
```
Time:  O(log(range) * T(predicate))     [integer]
       O(K * T(predicate))               [floating-point, K iterations]
Space: O(S(predicate))
```

### Decision Checklist
1. Is there a monotone predicate? If yes -> binary search.
2. What is the predicate? State it precisely.
3. Prove monotonicity in one sentence.
4. What are the sentinels? (trivially T, trivially F)
5. Is the answer left (last T) or right (first F)?
