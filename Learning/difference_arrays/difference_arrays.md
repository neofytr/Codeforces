# Difference Arrays: A Rigorous Treatment

## 1. Formal Definition and Duality

### 1.1 Definition

Let **a** = (a_0, a_1, ..., a_{n-1}) be a sequence of elements from an abelian group (G, +).
The **difference array** D = (D_0, D_1, ..., D_{n-1}) is defined by:

    D_0 = a_0
    D_i = a_i - a_{i-1}    for i = 1, 2, ..., n-1

The difference operator Delta acts on sequences:

    (Delta(a))_i = a_i - a_{i-1}     (with the convention a_{-1} = 0, so D_0 = a_0 - 0 = a_0)

### 1.2 The Fundamental Inversion Theorem

**Theorem 1.1 (Prefix Sum Recovers the Original).**
If D is the difference array of a, then:

          i
    a_i = sum  D_j     for all i = 0, 1, ..., n-1
          j=0

That is, prefix_sum(D) = a.

**Proof.** We compute directly:

    i               i
    sum D_j  =  D_0 + sum (a_j - a_{j-1})
    j=0             j=1

             =  a_0 + (a_1 - a_0) + (a_2 - a_1) + ... + (a_i - a_{i-1})

             =  a_0 + a_i - a_0        (telescoping: all intermediate terms cancel)

             =  a_i                                                                  QED

### 1.3 The Operator Algebra

Let Sigma denote the prefix sum operator and Delta the difference operator. We have
established:

    Sigma . Delta = id      (Theorem 1.1: prefix sum of differences recovers original)
    Delta . Sigma = id      (proved in prefix_sums.md, Theorem 6.1)

These operators are **mutual inverses** on the vector space of finite sequences. This is
the discrete analogue of the Fundamental Theorem of Calculus:

    Continuous:    integral (d/dx f) dx = f       and     d/dx (integral f dx) = f
    Discrete:      Sigma(Delta(a)) = a            and     Delta(Sigma(a)) = a

This analogy is not merely poetic. In the calculus of finite differences (a subject
dating back to Newton and Euler), Delta plays the role of differentiation, Sigma plays
the role of integration, and many classical identities carry over: summation by parts
(discrete integration by parts), the discrete Taylor expansion, and so on.

### 1.4 Linearity

Both Sigma and Delta are **linear operators**: for sequences a, b and scalar c,

    Delta(a + b) = Delta(a) + Delta(b)
    Delta(c * a) = c * Delta(a)

and similarly for Sigma. This linearity is what makes difference arrays composable:
multiple independent range updates can be applied to D, and a single application of
Sigma recovers the combined effect.


## 2. Range Updates in O(1)

This is the raison d'etre of difference arrays: transforming range updates on an array
into point updates on its difference array.

### 2.1 The Core Operation

**Theorem 2.1 (Range Update via Difference Array).**
To add a constant v to all elements a_l, a_{l+1}, ..., a_r (inclusive), it suffices to set:

    D[l]   += v
    D[r+1] -= v       (if r+1 < n; otherwise omit)

After applying prefix sums to the modified D, the resulting array equals the original a
with v added to positions [l, r].

**Proof.** Let D' be the modified difference array. We must show that Sigma(D') equals
a with v added on [l, r]. Since Sigma is linear:

    Sigma(D') = Sigma(D + delta) = Sigma(D) + Sigma(delta) = a + Sigma(delta)

where delta is the "update sequence" defined by delta[l] = v, delta[r+1] = -v, and
delta[i] = 0 otherwise. We compute Sigma(delta):

    (Sigma(delta))_i = sum_{j=0}^{i} delta[j]

    - If i < l: no nonzero terms have appeared. Sum = 0.
    - If l <= i <= r: only delta[l] = v has appeared. Sum = v.
    - If i > r: both delta[l] = v and delta[r+1] = -v have appeared. Sum = v + (-v) = 0.

Therefore Sigma(delta) adds v exactly on [l, r] and 0 elsewhere.                    QED

### 2.2 The Batch Update Pattern

Given q range update operations (l_k, r_k, v_k) for k = 1, ..., q, we can process
all of them in O(q) time (O(1) per update on D), then recover the final array in O(n)
via one prefix sum pass.

**Total complexity: O(q + n).**

Compare with the naive approach of O(q * n) (applying each update element-by-element).
For q and n both on the order of 10^5, this is the difference between 10^5 and 10^10
operations -- the difference between passing and not passing.

### 2.3 Formal Statement of the Batch Algorithm

    Input:  array a[0..n-1], list of updates (l_k, r_k, v_k) for k = 1..q
    Output: array a' where a'[i] = a[i] + sum_{k: l_k <= i <= r_k} v_k

    Algorithm:
    1. Compute D[0..n-1] = Delta(a).                                     // O(n)
       (Or start with D = 0 if a is initially all zeros.)
    2. For each update (l, r, v):                                        // O(q)
           D[l] += v
           if r + 1 < n: D[r+1] -= v
    3. Compute a' = Sigma(D).                                            // O(n)

**Remark.** In many problems, the initial array is all zeros. Then step 1 is trivial
(D is also all zeros), and the algorithm simplifies to: apply point updates to D, then
take prefix sums once. This is the most common usage pattern.


## 3. Two-Dimensional Difference Arrays

### 3.1 Setup

Let a be an m x n matrix. We wish to support rectangle updates: add v to all entries
a[r][c] with r1 <= r <= r2, c1 <= c <= c2.

Define the 2D difference array D of size m x n. The 2D prefix sum of D should equal a.

### 3.2 The Update Rule

**Theorem 3.1 (2D Range Update via Difference Array).**
To add v to the rectangle [r1, r2] x [c1, c2], set:

    D[r1][c1]     += v
    D[r1][c2+1]   -= v      (if c2+1 < n)
    D[r2+1][c1]   -= v      (if r2+1 < m)
    D[r2+1][c2+1] += v      (if r2+1 < m and c2+1 < n)

**Proof.** This is the 2D analogue of the 1D case, derived via inclusion-exclusion.

Consider the effect of each point update after taking 2D prefix sums. A point update
D[i][j] += v contributes v to all positions (r, c) with r >= i and c >= j (since the
2D prefix sum accumulates downward and rightward).

    D[r1][c1] += v       adds v to the entire quadrant [r1, inf) x [c1, inf)
    D[r1][c2+1] -= v     subtracts v from [r1, inf) x [c2+1, inf), removing excess columns
    D[r2+1][c1] -= v     subtracts v from [r2+1, inf) x [c1, inf), removing excess rows
    D[r2+1][c2+1] += v   adds back v to [r2+1, inf) x [c2+1, inf), correcting double removal

By inclusion-exclusion, the net effect is +v on exactly [r1, r2] x [c1, c2].        QED

### 3.3 Recovery

After all updates, the final matrix is recovered by a 2D prefix sum pass:

    for i = 0 to m-1:
        for j = 0 to n-1:
            if i > 0: D[i][j] += D[i-1][j]
            if j > 0: D[i][j] += D[i][j-1]
            if i > 0 and j > 0: D[i][j] -= D[i-1][j-1]

After this pass, D[i][j] = a[i][j] (the intended final value).

**Complexity.** O(q) for q rectangle updates, O(mn) for recovery.

### 3.4 Intuition via Convolution

Another way to view the 2D difference array: the difference operator Delta_2D is
convolution with the kernel:

    K = [ +1  -1 ]
        [ -1  +1 ]

And the 2D prefix sum is convolution with the "all-ones lower-triangular" kernel.
These are inverses in the convolution algebra. This perspective generalizes naturally
to higher dimensions.


## 4. The Counting Overlaps Pattern

### 4.1 Problem Statement

Given q intervals [l_1, r_1], [l_2, r_2], ..., [l_q, r_q] on the integer line [0, N),
compute for each point x in [0, N) the number of intervals that contain x.

### 4.2 Solution

Initialize D[0..N] = 0. For each interval [l_i, r_i]:

    D[l_i]     += 1
    D[r_i + 1] -= 1

Then compute the prefix sum of D. The value at position x is the number of intervals
covering x.

### 4.3 Proof of Correctness

**Theorem 4.1.** After the prefix sum, D[x] = |{i : l_i <= x <= r_i}|.

**Proof.** By linearity and Theorem 2.1, the prefix sum at position x equals:

    sum_{i=1}^{q} [l_i <= x <= r_i]

where [.] is the Iverson bracket. This is because each interval [l_i, r_i] contributes
+1 to the prefix sum at x if and only if x is in [l_i, r_i]: the +1 at D[l_i] has been
accumulated (since x >= l_i), but the -1 at D[r_i + 1] has NOT been accumulated
(since x <= r_i < r_i + 1).                                                         QED

### 4.4 Application: Karen and Coffee

**Problem (karenCoffee).** Given q recipes, each specifying a temperature range [l_i, r_i],
and threshold k, determine for each query temperature t whether at least k recipes include t
in their range.

**Solution.** Apply the counting overlaps pattern: use a difference array to compute, for
each temperature, the number of recipes covering it. Then answer each query by checking
whether the count meets the threshold.

**Complexity.** O(q + T) where T is the temperature range, plus O(1) per query.

### 4.5 Variations

**Weighted overlaps.** Each interval has a weight w_i. Set D[l_i] += w_i, D[r_i+1] -= w_i.
The prefix sum gives the total weight covering each point.

**2D overlaps.** Given rectangles, count how many cover each cell. Use the 2D difference
array from Section 3.

**Circular overlaps.** If the domain is circular (e.g., hours of the day mod 24), split
each wrapping interval into two non-wrapping intervals.


## 5. Higher-Order Difference Arrays

### 5.1 Motivation

What if we want to add not a constant, but an **arithmetic progression** to a range?
That is, add (v, v+d, v+2d, ...) to positions l, l+1, ..., r.

A single difference array handles constant range updates. For linear (arithmetic
progression) updates, we need a **second-order difference array**.

### 5.2 Definition

The **k-th order difference array** is obtained by applying the difference operator k times:

    Delta^0(a) = a
    Delta^1(a) = Delta(a)           (standard difference array)
    Delta^2(a) = Delta(Delta(a))    (second-order)
    ...
    Delta^k(a) = Delta(Delta^{k-1}(a))

To recover a from Delta^k(a), apply the prefix sum operator k times:

    a = Sigma^k(Delta^k(a))

### 5.3 Adding an Arithmetic Progression

**Theorem 5.1.** To add the arithmetic progression (v, v+d, v+2d, ..., v+(r-l)d) to
positions l, l+1, ..., r:

On the first-order difference array D^(1):
    D^(1)[l]   += v
    D^(1)[r+1] -= v + (r-l)d

On the second-order difference array D^(2) = Delta(D^(1)):
    D^(2)[l]     += v
    D^(2)[l+1]   += d - v          (the common difference starts after position l)
    D^(2)[r+1]   -= v + (r-l)d + d (cancel the progression and the ongoing difference)
    D^(2)[r+2]   += v + (r-l)d     (cancel the subtraction's ripple effect)

Wait -- let us be more careful. The cleanest formulation uses two arrays.

**Clean formulation.** Maintain two arrays B_1[0..n] and B_2[0..n], both initialized to 0.
To add (v + id) at position (l + i) for i = 0, 1, ..., r-l:

    // First, decompose: value at position x (for l <= x <= r) is:
    //   v + (x - l) * d  =  (v - l*d) + x*d
    //
    // Let c0 = v - l*d, c1 = d. Then value at position x = c0 + c1*x.

    // Range update "add c0" to [l, r]:
    B_1[l]   += c0
    B_1[r+1] -= c0

    // Range update "add c1*x" to [l, r]:
    B_2[l]   += c1
    B_2[r+1] -= c1

Recovery: take prefix sums of both B_1 and B_2. Then a[x] += B_1[x] + B_2[x] * x.

**Proof.** After prefix sums, B_1[x] = c0 for x in [l, r] and 0 otherwise; B_2[x] = c1
for x in [l, r] and 0 otherwise. So the contribution at position x in [l, r] is
c0 + c1*x = (v - l*d) + d*x = v + d*(x - l), which is exactly the arithmetic
progression.                                                                         QED

### 5.4 General Polynomial Updates

For adding a degree-k polynomial to a range, use k+1 difference arrays. The value at
position x is sum_{j=0}^{k} B_j[x] * x^j, where each B_j is maintained as a standard
difference array.

### 5.5 Application: Iterated Prefix Sums

Applying the prefix sum operator k times to a sequence is equivalent to:

    (Sigma^k(a))_n = sum_{i=0}^{n} C(n - i + k - 1, k - 1) * a_i

This is the discrete analogue of the k-fold integral. The binomial coefficient
C(n - i + k - 1, k - 1) acts as a "kernel" -- the discrete Green's function.

In problems like karenCoffee, one applies difference array updates (Delta), then recovers
via prefix sum (Sigma), then may need another prefix sum pass to compute cumulative counts
or answer range queries. Understanding that Sigma^2 is not merely "two passes of prefix
sum" but a well-defined operator with known combinatorial properties can illuminate the
structure of such problems.

### 5.6 The Newton Forward Difference Formula

The discrete Taylor expansion (Newton's forward difference formula) states:

                  k
    a_n = sum    C(n, j) * (Delta^j(a))_0
                 j=0

for any polynomial sequence of degree k. This connects higher-order differences to
polynomial interpolation: the values (Delta^0(a))_0, (Delta^1(a))_0, ..., (Delta^k(a))_0
uniquely determine a degree-k polynomial sequence.

**Application in competitive programming.** If you know a sequence is polynomial of degree
k, you can reconstruct it from its first k+1 values using this formula. This is faster
than Lagrange interpolation and numerically more stable for integer sequences.


## 6. Summary of Complexity

| Operation                      | Naive       | Difference Array  |
|-------------------------------|-------------|-------------------|
| Single range update [l,r]     | O(r - l)    | O(1)              |
| q range updates               | O(q * n)    | O(q + n)          |
| 2D rectangle update           | O(area)     | O(1)              |
| q 2D rectangle updates        | O(q * area) | O(q + m*n)        |
| Arithmetic progression update | O(r - l)    | O(1) (two arrays) |

The pattern is always the same: trade deferred computation for constant-time updates.
The prefix sum pass is the "bill" that comes due at the end -- but you pay it only once.


## 7. The Duality Principle

Every prefix sum technique has a difference array dual, and vice versa:

| Prefix Sum World                     | Difference Array World                  |
|--------------------------------------|-----------------------------------------|
| Range query in O(1)                  | Range update in O(1)                    |
| Build P in O(n)                      | Build D in O(n)                         |
| 2D: inclusion-exclusion for query    | 2D: inclusion-exclusion for update      |
| Prefix sum + binary search           | Difference array + sweep line           |
| Static array, many queries           | Many updates, then read once            |

If a problem involves many updates followed by reading the array, think difference arrays.
If a problem involves many range queries on a static array, think prefix sums.
If a problem involves both interleaved updates and queries, you need a data structure
(Fenwick tree, segment tree) that maintains the prefix sums dynamically.

Understanding this duality deeply means you never have to memorize which technique to use.
You simply ask: am I inverting, or am I accumulating? The operator algebra tells you
the rest.
