# Dynamic Programming: A Rigorous Foundation

---

## Section 1: What IS Dynamic Programming?

### 1.1 Informal Motivation

Consider a problem where we must make a sequence of decisions d_1, d_2, ..., d_n, and the
total cost is some function of all decisions. Brute force enumerates all possible decision
sequences --- exponential in n. Dynamic programming exploits the fact that, in many problems,
the *effect* of past decisions on the future can be summarised by a small "state", and
identical states lead to identical optimal futures.

### 1.2 Formal Definitions

**Definition 1 (State Space).** A *state space* is a finite set S equipped with a function
f: S -> V, where V is a totally ordered set (for optimization) or a commutative ring
(for counting). We call f the *value function*.

**Definition 2 (Dependency DAG).** A *dependency structure* on S is a directed acyclic graph
G = (S, E) where (s, s') in E means the computation of f(s) requires f(s'). The acyclicity
is essential: it guarantees a topological ordering exists, so we can compute f bottom-up.

**Definition 3 (Dynamic Programming Problem).** A DP problem is a tuple (S, G, T, B, ans)
where:
  - S is a finite state space
  - G = (S, E) is the dependency DAG
  - T: S -> V is the transition function (the recurrence), defined for non-base states
  - B: S_0 -> V assigns values to base states S_0 (the minimal elements of G)
  - ans in S (or a subset of S) identifies which state(s) contain the final answer

The value function is defined by:

    f(s) = B(s)                        if s in S_0
    f(s) = T(s, {f(s') : (s,s') in E}) otherwise

### 1.3 The Two Pillars

**Optimal Substructure.** A problem has optimal substructure if an optimal solution to the
whole problem contains within it optimal solutions to subproblems.

More precisely: if f(s) = opt_{a in A(s)} [cost(s,a) + f(next(s,a))], and s* achieves the
optimum by choosing action a*, then f(next(s*, a*)) must itself be optimal for the subproblem
rooted at next(s*, a*).

*Proof.* Suppose not. Then there exists a value f'(next(s*, a*)) < f(next(s*, a*)) (for
minimization). But then cost(s*, a*) + f'(next(s*, a*)) < cost(s*, a*) + f(next(s*, a*))
= f(s*), contradicting the optimality of f(s*). QED.

**Overlapping Subproblems.** Different branches of the recursion tree encounter the same
state s in S. Without memoization, f(s) would be recomputed each time. With memoization
(or bottom-up computation), each state is computed exactly once.

**Complexity consequence.** If |S| = N and each transition examines at most k predecessors,
total work is O(Nk). This is typically polynomial, versus the exponential brute force.

### 1.4 Why Greedy Fails and DP Succeeds

A greedy algorithm commits to a locally optimal choice at each step and never reconsiders.
Formally, it computes f(s) = cost(s, a_greedy) + f(next(s, a_greedy)) where a_greedy =
argopt_{a in A(s)} cost(s, a), ignoring how the choice affects future states.

DP computes f(s) = opt_{a in A(s)} [cost(s, a) + f(next(s, a))], considering ALL choices
at each state. The DAG structure of states guarantees that we can evaluate this without
circular dependency.

Greedy is correct only when the locally optimal choice is always globally optimal (the
*greedy choice property*). DP requires no such property --- it works whenever optimal
substructure and overlapping subproblems hold.

### 1.5 Top-Down vs Bottom-Up

**Top-down (memoization):** Recursive computation of f(s), storing results in a hash map
or array. Only computes states reachable from the initial call. Natural when the state
space is sparse or the dependency structure is complex.

**Bottom-up (tabulation):** Iterate over states in topological order, computing f for each.
Requires knowing the full state space and a topological ordering. Eliminates recursion
overhead. Enables space optimization (next section).

**Theorem.** Both methods compute the same value function f and have the same asymptotic
time complexity (up to constant factors from hash map overhead in top-down).

*Proof sketch.* Both compute each reachable state exactly once. The topological ordering
guarantees that all predecessors are computed before any state that depends on them. QED.

---

## Section 2: The DP Framework --- A Formal Recipe

Every DP problem requires specifying five components. This is not a heuristic; it is a
checklist that, when completed correctly, constitutes a proof of correctness.

### 2.1 State

**Question:** What information from past decisions is needed to make optimal future decisions?

The state must be a *sufficient statistic* for the future. Formally, if two histories h_1 and
h_2 lead to the same state s, then the optimal cost-to-go from s must be the same regardless
of which history produced s.

**State design principle:** The state must capture EXACTLY the information needed. If it
captures too little, the recurrence is incorrect (different histories that should yield
different futures are conflated). If it captures too much, the state space |S| becomes
intractably large --- TLE or MLE.

*Example.* Coin change (minimum coins to make value v): state = remaining value. We do not
need to know which coins were already used, because any coin can be used at any time
(unbounded). If coins were limited to one use each (0/1 knapsack), the state would need
to additionally track which coins remain available.

### 2.2 Transition (Recurrence)

The recurrence defines f(s) in terms of f at "smaller" states. "Smaller" means strictly
closer to a base case in the dependency DAG.

**Requirement:** The recurrence must be *complete* (it considers all possible decisions at
state s) and *sound* (it only combines values that correspond to valid subproblems).

### 2.3 Base Cases

The base cases are the states with no outgoing edges in the dependency DAG (the sources,
in the transposed graph). These must have known values.

Common patterns:
  - f(0) = 0 (empty problem has zero cost)
  - f(0) = 1 (there is exactly one way to do nothing)
  - f(empty set) = 0

A subtle point: if the base case is wrong, the entire computation is wrong. Always verify
base cases by checking small examples by hand.

### 2.4 Answer Extraction

The final answer may be:
  - A single state: f(s_final), e.g., dp[n][W] in knapsack
  - An optimum over states: max_{s in S'} f(s), e.g., LIS = max_i dp[i]
  - A sum over states: sum_{s in S'} f(s), e.g., counting paths ending anywhere in last row

### 2.5 Order of Computation

For bottom-up: process states in an order such that all dependencies of s are computed before
s. This is a topological sort of the dependency DAG.

Common orderings:
  - Linear: i = 0, 1, ..., n
  - Grid: row by row, left to right
  - Subset (bitmask): masks in increasing order (since mask' subset mask implies mask' < mask)
  - Interval: by length of interval (short before long)
  - Tree: post-order traversal (children before parent)

---

## Section 3: Counting DP vs Optimization DP

### 3.1 The Algebraic Distinction

Both counting and optimization DP share the same structural framework. The difference lies
in the algebraic operation used to combine values:

  - **Counting DP:** f(s) = SUM_{transitions t from s} f(next(s,t)). The value set V is
    (Z/mZ, +, *) --- integers modulo some prime, with addition.
  - **Optimization DP:** f(s) = min/max_{transitions t from s} [cost(s,t) + f(next(s,t))].
    The value set V is (Z, min, +) or (Z, max, +) --- a tropical semiring.

This algebraic viewpoint clarifies why the same DP skeleton solves both: only the
"aggregation operator" changes.

### 3.2 The Permutation-Combination Dichotomy

This is among the subtlest points in counting DP. Consider counting the number of ways to
make change for a target sum using coins c_1, c_2, ..., c_k.

**Counting ORDERED sequences (permutations):**

```
dp[0] = 1
for s = 1 to target:
    for each coin c in {c_1, ..., c_k}:
        if s >= c: dp[s] += dp[s - c]
```

Here dp[s] counts the number of SEQUENCES of coins summing to s. The sequence (1, 2) and
(2, 1) are counted separately.

**Counting UNORDERED multisets (combinations):**

```
dp[0] = 1
for each coin c in {c_1, ..., c_k}:         // outer loop over items
    for s = c to target:                      // inner loop over sums
        dp[s] += dp[s - c]
```

Here dp[s] counts the number of MULTISETS of coins summing to s. The multiset {1, 2} is
counted once regardless of order.

### 3.3 Why Does This Work? (Formal Proof)

**Theorem.** The unordered algorithm computes, for each s, the number of multisets of coins
from {c_1, ..., c_k} that sum to s.

*Proof.* Define dp_j[s] = the number of multisets of coins drawn from {c_1, ..., c_j} that
sum to s. We prove by induction on j that after the j-th iteration of the outer loop, the
1D array dp[] contains dp_j[s] for all s.

**Base case (j=0):** Before any iteration, dp[0] = 1 (empty multiset), dp[s] = 0 for s > 0.
This is correct: from zero coins, only sum 0 is achievable.

**Inductive step:** Assume after iteration j-1, dp[s] = dp_{j-1}[s] for all s. In iteration
j (processing coin c_j), we compute for s = c_j, c_j+1, ..., target:

    dp[s] += dp[s - c_j]

After this update, dp[s] = dp_{j-1}[s] + dp[s - c_j]. We claim this equals dp_j[s].

Indeed, multisets from {c_1,...,c_j} summing to s are of two types:
  (a) those not using c_j at all: counted by dp_{j-1}[s]
  (b) those using c_j at least once: in bijection with multisets from {c_1,...,c_j}
      summing to s - c_j (remove one copy of c_j), counted by dp_j[s - c_j]

Since we iterate s forward, dp[s - c_j] has already been updated to dp_j[s - c_j] when
we reach s. (This is exactly why forward iteration allows repeated use of c_j!) Thus:

    dp_j[s] = dp_{j-1}[s] + dp_j[s - c_j]

which is precisely what the code computes. QED.

**Remark.** The ordered version does not process coins one at a time. Instead, at each sum s,
it considers ALL coins. This means a sequence built by adding coin c_1 first, then c_2, is
counted separately from c_2 first, then c_1. No ordering on coins is imposed, hence all
orderings are counted.

---

## Section 4: Space Optimization --- The Mathematical Justification

### 4.1 The Rolling Array Principle

**Theorem.** If f(s) depends only on values from the immediately preceding "layer" L_{i-1}
(and possibly the current layer L_i), then we can discard all layers before L_{i-1} and
reduce space from O(|S|) to O(|L|).

*Proof.* After computing all states in layer L_i, no future computation references any layer
L_j with j < i-1. Hence those values can be overwritten. QED.

**Application (Grid DP).** For an m x n grid where dp[i][j] depends on dp[i-1][j] and
dp[i][j-1], maintain two rows of size n: prev_row and curr_row. Space: O(n) instead of
O(mn). If dp[i][j] depends only on dp[i-1][j] and dp[i][j-1] (and we process left to
right), a single row suffices: dp[j] on the left has already been updated to row i, while
dp[j] on the right still holds the row i-1 value.

### 4.2 The Direction Lemma for 1D Knapsack

This is one of the most important and frequently misunderstood optimizations in all of DP.

**Lemma (Backward iteration for 0/1 knapsack).** When each item can be used at most once,
iterating the capacity w from W down to w_i ensures correctness.

*Proof.* Let dp_old[w] denote the array values before processing item i. When we compute:

    dp[w] = max(dp[w], dp[w - w_i] + v_i)     for w = W, W-1, ..., w_i

At the moment we access dp[w - w_i], we have w - w_i < w, and since we iterate w downward,
dp[w - w_i] has NOT yet been updated in this iteration. Therefore:

    dp[w - w_i] = dp_old[w - w_i]

which represents the optimal value using items {1, ..., i-1} with capacity w - w_i. This is
exactly what we need: the value WITHOUT item i, to which we add v_i if we choose to include
item i. QED.

**Lemma (Forward iteration for unbounded knapsack).** When each item can be used unlimited
times, iterating w from w_i up to W ensures correctness.

*Proof.* Now dp[w - w_i] may have already been updated in this iteration --- it may already
reflect the inclusion of item i (possibly multiple times). This is exactly what we want:
dp[w - w_i] represents the best value achievable with capacity w - w_i using item i an
unlimited number of times, so adding one more copy of item i is valid. QED.

### 4.3 Summary Table

| Knapsack Type | Item Usage    | Iteration Direction | Reason                          |
|---------------|---------------|--------------------|---------------------------------|
| 0/1           | At most once  | w = W down to w_i  | dp[w-w_i] must be "old" (no i)  |
| Unbounded     | Unlimited     | w = w_i up to W    | dp[w-w_i] may include i again   |
| Bounded (k_i) | At most k_i   | Binary lifting     | Decompose k_i into powers of 2  |

---

## Section 5: Transition Optimization

When the state space has N states and each transition naively examines O(N) candidates,
the total complexity is O(N^2) or worse. Several techniques reduce this.

### 5.1 Prefix Sum Optimization

**Setup.** The transition has the form:

    dp[i] = g(i) + SUM_{j in [l(i), r(i)]} dp[j]

or involves a range aggregate.

**Technique.** Precompute prefix sums P[i] = dp[0] + dp[1] + ... + dp[i]. Then
SUM_{j=l}^{r} dp[j] = P[r] - P[l-1] in O(1).

**Complexity reduction.** O(N) per state -> O(1) per state. Total: O(N^2) -> O(N).

*Example.* The user's prefix sum work directly applies: given dp values on a range, prefix
sums allow O(1) range queries, turning an O(N) transition into O(1).

### 5.2 Divide-and-Conquer Optimization

**Setup.** dp[i][j] = min_{k < j} (dp[i-1][k] + C(k,j)) where the optimal split point
opt(i,j) is monotone in j: opt(i, j) <= opt(i, j+1).

**Technique.** Use divide and conquer on j. For the midpoint j_mid, find opt(i, j_mid) by
brute force. Then recurse on the left half with opt range [lo, opt(i, j_mid)] and right
half with [opt(i, j_mid), hi].

**Complexity.** Each level of recursion does O(N) work total. There are O(log N) levels.
Total: O(N log N) per layer, O(KN log N) overall.

### 5.3 Convex Hull Trick

**Setup.** dp[i] = min_{j < i} (dp[j] + b[j] * a[i] + c[j]) where we can separate
terms depending on i and j.

Rewrite as: dp[i] = min_j (b[j] * a[i] + (dp[j] + c[j])). This is the minimum over a
set of linear functions y = b[j] * x + (dp[j] + c[j]) evaluated at x = a[i].

**Technique.** Maintain the lower envelope (convex hull) of the set of lines. If a[i] is
monotone, we can use a deque and process queries in amortized O(1). Otherwise, use a
Li Chao tree for O(log N) per query.

**Complexity.** O(N) with monotone queries, O(N log N) otherwise. Reduces from O(N^2).

### 5.4 Knuth's Optimization

**Setup.** dp[i][j] = min_{i <= k < j} (dp[i][k] + dp[k+1][j] + C(i,j)) where the cost
function C satisfies the *quadrangle inequality*:

    C(a, c) + C(b, d) <= C(a, d) + C(b, c)   for a <= b <= c <= d

**Result.** opt(i,j-1) <= opt(i,j) <= opt(i+1,j). This monotonicity reduces interval DP
from O(N^3) to O(N^2).

---

## Section 6: Bitmask DP

### 6.1 Representation

A subset of {0, 1, ..., n-1} is represented as an n-bit integer mask in {0, 1, ..., 2^n - 1}.
Element i is in the subset iff bit i is set: (mask >> i) & 1 == 1.

**State space size:** |S| = 2^n. This is feasible for n <= 20 (2^20 ~ 10^6) and sometimes
n <= 25 with careful optimization.

### 6.2 Ordering

**Lemma.** If mask' is a proper subset of mask, then mask' < mask (as integers).

*Proof.* mask' is obtained from mask by clearing one or more bits, which strictly decreases
the integer value. QED.

**Consequence.** Iterating masks from 0 to 2^n - 1 is a valid topological ordering for
any DP where f(mask) depends on f(mask') for mask' subset mask.

### 6.3 The Vitamins Pattern

A canonical bitmask DP: given items, each contributing a subset of "properties" (vitamins,
skills, etc.), find the minimum cost to acquire ALL properties.

**State:** mask in {0,1}^n where bit i indicates property i has been acquired.
**Transition:** For each item with cost c and property set p:

    dp[mask | p] = min(dp[mask | p], dp[mask] + c)

**Base case:** dp[0] = 0 (no properties, no cost). dp[mask] = infinity for mask != 0.
**Answer:** dp[(1 << n) - 1] (all properties acquired).

**Correctness.** Each state mask records which properties we have. The transition tries adding
each item; the | operation ensures properties accumulate monotonically. Since mask | p >= mask,
the dependency DAG is acyclic. The minimum over all ways to reach the full mask is optimal by
exhaustive enumeration of item orderings.

### 6.4 Subset Enumeration

**Problem:** Given a mask m, enumerate all submasks of m.

```cpp
for (int s = m; s > 0; s = (s - 1) & m) {
    // process submask s
}
// don't forget to process s = 0 separately
```

**Correctness.** s - 1 flips the lowest set bit of s and sets all lower bits. The & m
operation restricts back to bits within m, producing the next smaller submask.

**Complexity.** This generates exactly 2^{popcount(m)} submasks of m.

**Total over all masks:** SUM_{m=0}^{2^n - 1} 2^{popcount(m)} = 3^n.

*Proof.* Each element of {0,1,...,n-1} has three "roles" relative to (m, s): not in m,
in m but not in s, or in both m and s. So the total is 3^n by the multiplication principle.

### 6.5 SOS (Sum over Subsets) DP

**Problem:** Given f(mask) for all masks, compute g(mask) = SUM_{s subset mask} f(s).

**Naive approach:** For each mask, enumerate submasks. Total: O(3^n).

**SOS DP (Zeta transform):**

```cpp
for (int i = 0; i < n; i++)
    for (int mask = 0; mask < (1 << n); mask++)
        if (mask & (1 << i))
            dp[mask] += dp[mask ^ (1 << i)];
```

**Complexity:** O(n * 2^n), a dramatic improvement over O(3^n) for large n.

**Correctness.** After processing dimension i, dp[mask] contains the sum over all submasks
that agree with mask on bits {i+1, ..., n-1} but may differ on bits {0, ..., i}. After
all n dimensions, dp[mask] = sum over ALL submasks. This is the inclusion-exclusion /
Mobius inversion on the Boolean lattice.

---

## Section 7: Tree DP

### 7.1 The Post-Order Principle

**Theorem.** If f(v) depends on f(children(v)), then processing nodes in post-order
(children before parent) is a valid computation order.

*Proof.* In a rooted tree, the subtree of v contains all descendants. Post-order visits
all nodes in the subtree of v before visiting v. Hence all children (and their subtrees)
are processed before v. QED.

### 7.2 The General Pattern

```
function dfs(v, parent):
    dp[v] = base_value
    for each child u of v (u != parent):
        dfs(u, v)
        dp[v] = combine(dp[v], dp[u])
```

### 7.3 Rerooting Technique

**Problem:** Compute f(v) = the answer when v is the root, for ALL v simultaneously.

**Naive approach:** Root at each v, run tree DP. O(n^2).

**Rerooting (two-pass):**

**Pass 1 (root at node 1):** Compute dp_down[v] = answer considering only the subtree of v.

**Pass 2 (DFS from root):** For each node v with parent p, compute dp_up[v] = the answer
from "the rest of the tree" (everything outside v's subtree). Then:

    f(v) = combine(dp_down[v], dp_up[v])

**Key identity:** dp_up[v] depends on dp_up[p] and dp_down[siblings of v]. To combine
siblings efficiently, precompute prefix and suffix aggregates of children values.

**Complexity:** O(n) total --- two DFS passes, each O(n).

### 7.4 Subtree Merging and the "Small-to-Large" Trick

When merging information from children into a parent (e.g., maintaining a set of values in
each subtree), always merge the smaller child's set INTO the larger one. By a standard
amortised argument, each element is moved O(log n) times, giving O(n log n) total.

---

## Section 8: The Kadane Transformation

### 8.1 The Principle

Many problems are not obviously DP problems until an algebraic transformation reveals a
known DP structure. The key idea: rewrite the objective function to expose a standard
recurrence.

### 8.2 Max Subarray Sum (Kadane's Algorithm)

**Problem.** Given a[1..n], find max_{1<=l<=r<=n} SUM_{i=l}^{r} a[i].

**Transformation.** Let S[i] = a[1] + ... + a[i] (prefix sum). Then:

    SUM_{i=l}^{r} a[i] = S[r] - S[l-1]

So we seek max_{0<=l<r<=n} (S[r] - S[l]).

**DP formulation.** For each r, the best l is the one minimizing S[l] for l < r. Maintain
min_prefix = min_{0<=l<r} S[l] as we scan r from left to right.

    answer = max_{r} (S[r] - min_prefix)

This is O(n) time, O(1) space (excluding input).

### 8.3 The Flipping Game Transformation

**Problem.** Given a binary string, flip all bits in exactly one contiguous subarray. Maximize
the number of 1s.

**Transformation.** Let a[i] = +1 if bit i is 0, and a[i] = -1 if bit i is 1. Flipping
subarray [l,r] changes the count of 1s by SUM_{i=l}^{r} a[i]. We want to maximize this sum,
which is exactly the max subarray sum problem!

**Formally:** Let ones = count of 1s in original. After flipping [l,r]:
  - Gain one 1 for each 0 in [l,r]: contributes +1 per zero
  - Lose one 1 for each 1 in [l,r]: contributes -1 per one

Total change = (zeros in [l,r]) - (ones in [l,r]) = SUM a[i] over [l,r].

Answer = ones + max_subarray_sum(a).

Alternatively, using the prefix sum approach: define prefix[r] = number of 0s in a[1..r].
Then del[r] = 2*prefix[r] - r gives the "gain minus loss" up to position r. The problem
reduces to max(del[r] - del[l]) for l < r.

### 8.4 The Target Sum Transformation

**Problem.** Given array a[1..n] and target T, assign +/- to each element. Count assignments
where the signed sum equals T.

**Transformation.** Let P = set of elements assigned +, N = set assigned -. Then:
  - sum(P) - sum(N) = T
  - sum(P) + sum(N) = total (the sum of all elements)

Adding: 2*sum(P) = total + T, so sum(P) = (total + T) / 2.

**Reduction.** The problem reduces to counting subsets of {a[1], ..., a[n]} with sum equal
to (total + T) / 2. This is exactly the 0/1 subset-sum counting problem!

**Necessary condition:** (total + T) must be even and non-negative and T <= total.

**Complexity.** O(n * target) where target = (total + T) / 2, using 1D DP with backward
iteration.

### 8.5 General Principle

The Kadane transformation is an instance of a broader strategy: **reformulate the objective
algebraically until it matches a known DP recurrence**. Common reformulations include:
  - Prefix sum decomposition: SUM_{l..r} = S[r] - S[l-1]
  - Variable substitution: rewrite in terms of new variables that decouple decisions
  - Complement counting: count(bad) = count(all) - count(good)
  - Symmetry breaking: fix one aspect of the solution to reduce the search space

---

## Section 9: Correctness Proofs for DP

### 9.1 The Proof Template

Every DP correctness proof follows the same structure:

**Step 1.** Define f(s) precisely (what it represents).

**Step 2.** Prove the recurrence is correct:
  - **Completeness:** The recurrence considers all possible transitions from s
  - **Soundness:** Each transition produces a valid subproblem
  - **Optimality/Counting:** Taking opt/sum over all transitions gives the correct value

**Step 3.** Prove the base cases are correct.

**Step 4.** Argue by strong induction on the topological order: if all predecessors are
correct, the recurrence gives the correct value for s.

### 9.2 Common Pitfalls

**Off-by-one errors in base cases.** The most frequent DP bug. Always verify: does dp[0]
represent "zero items" or "item 0"? Does dp[n] represent "all items processed" or "item n
processed"?

**Incorrect state definition.** If the state conflates distinct situations, the recurrence
silently produces wrong answers. Test on small cases where you can verify by brute force.

**Missing transitions.** If the recurrence omits a valid transition, it may still produce a
valid but suboptimal answer (for optimization) or an undercount (for counting). Check that
all cases at each state are covered.

**Wrong iteration direction.** As proven in Section 4.2, forward vs backward iteration has
semantic consequences for which items are "available" in the transition.

---

## Section 10: From Problem to DP --- A Methodology

### 10.1 Recognizing DP

A problem likely admits DP if:
  - It asks for an OPTIMUM (min/max) or a COUNT (number of ways)
  - It has a sequential or hierarchical structure (process items one by one, subtree structure)
  - The space of possible solutions is exponential, but the space of "distinct states" is
    polynomial (or at most exponential in a small parameter)

### 10.2 The State Design Process

1. **Identify what changes between subproblems.** This is the state.
2. **Identify what stays the same.** This can be baked into the transition, not the state.
3. **Verify sufficiency:** Given only the state, can you determine the optimal action? If not,
   add more information to the state.
4. **Verify necessity:** Can you remove any component of the state without losing correctness?
   If so, remove it (smaller state space = better complexity).

### 10.3 The Verification Protocol

For any DP solution, before submitting:
  1. Check base cases by hand on trivial inputs
  2. Trace the recurrence on a small non-trivial input
  3. Verify that the iteration order respects the dependency DAG
  4. Confirm the answer is extracted from the correct state(s)
  5. Check for integer overflow (use long long or modular arithmetic as needed)
  6. Verify the complexity fits within the time limit

---

## Appendix: Notation and Conventions

| Symbol        | Meaning                                               |
|---------------|-------------------------------------------------------|
| S             | State space                                           |
| f(s), dp[s]  | Value function at state s                             |
| V             | Value set (integers, integers mod p, reals, etc.)     |
| opt           | min or max, depending on the problem                  |
| A(s)          | Set of valid actions/transitions at state s           |
| next(s, a)    | State reached from s by taking action a               |
| cost(s, a)    | Immediate cost of action a at state s                 |
| S_0           | Set of base states                                    |
| G = (S, E)    | Dependency DAG on the state space                     |
| [n]           | The set {1, 2, ..., n}                                |
| popcount(m)   | Number of set bits in integer m                       |
| mask | p      | Bitwise OR of mask and p                              |
| mask ^ (1<<i) | Toggle bit i in mask                                  |
