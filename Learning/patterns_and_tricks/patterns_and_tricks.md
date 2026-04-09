# Meta-Patterns in Competitive Programming

A taxonomy of deep structural patterns that recur across all problem domains.
These are not tricks — they are *principles* with formal justification.

---

## Pattern 1: Reduction to Known Problems

The single most powerful technique in competitive programming: transform an
unknown problem into a known one. Every solved problem in your repertoire
becomes a weapon if you can reduce to it.

### 1a. Optimization to Decision (Binary Search on the Answer)

**Theorem.** Let f: Z -> {true, false} be a predicate that is monotone
(i.e., f(k) = true implies f(k+1) = true, or vice versa). Then the optimal
threshold k* can be found in O(log(range)) evaluations of f.

**Why it works.** Monotonicity gives you the structure of a step function:
false, false, ..., false, true, true, ..., true. Binary search finds the
step boundary.

**Recipe:**
1. Identify the quantity you are optimizing (call it k).
2. Prove that "can we achieve answer <= k?" is monotone in k.
3. Binary search on k. For each candidate, solve the decision problem.

**Canonical examples:**
- "Minimize the maximum X" -> binary search on the maximum, check feasibility.
- "What is the latest time T such that P(T) holds?" -> binary search on T.
- Aggressive cows / painters partition / allocate minimum pages.

**Complexity:** O(log(range) * cost_of_decision). Often range ~ 10^9 so
log(range) ~ 30, which is essentially free.

### 1b. Algebraic Transformation

Change variables so the problem collapses to a standard form.

**Principle.** If you have a complex objective or constraint, define new
variables that absorb the complexity.

**Examples:**
- **Flipping game:** You want to maximize (ones after flipping [l,r]).
  Let del[i] = 2*P[i] - i where P[i] = prefix count of zeros. Then the
  answer reduces to max subarray sum of a derived array — Kadane's algorithm.
- **Target sum with +/- assignment:** Assign + or - to each element to hit
  target k. Let S = sum of positives. Then S - (total - S) = k, so
  S = (total + k)/2. This is subset sum — a standard DP.
- **Manhattan distance:** |x1-x2| + |y1-y2| can be transformed via
  u = x+y, v = x-y to max(|u1-u2|, |v1-v2|), which is Chebyshev distance.
  This decouples the coordinates.

### 1c. Graph Reduction

Model the problem as a graph problem. States become vertices, transitions
become edges. Then the entire machinery of graph theory applies.

**Recipe:**
1. Define the state space (what is a "configuration"?).
2. Define transitions (when can you move from one state to another?).
3. Define the objective (shortest path? reachability? cycle detection?).
4. Apply the appropriate algorithm (BFS, Dijkstra, DP on DAG, etc.).

**Examples:**
- Grid navigation -> BFS on grid graph.
- String transformation -> BFS on the space of strings.
- Game states -> DAG, topological order, DP for Grundy values.
- "Minimum cost to go from state A to state B with constraints" -> Dijkstra
  on an augmented state graph (see Pattern 3).

---

## Pattern 2: Counting via Prefix Sums and Maps

### The Fundamental Theorem of Prefix Sums

**Theorem.** Let a[0..n-1] be an array and P[i] = a[0] + a[1] + ... + a[i-1]
(with P[0] = 0). Then:

    sum(a[l..r]) = P[r+1] - P[l]

This is simply the telescoping property of partial sums.

### From Range Queries to Pair Counting

**Key insight.** "Count subarrays with sum = k" is equivalent to
"count pairs (l, r) with P[r] - P[l] = k," which is equivalent to
"for each r, count how many previous l have P[l] = P[r] - k."

This is a hashmap lookup. Total: O(n) time, O(n) space.

### Generalization: Any Decomposable Range Condition

**Principle.** A range condition on [l, r] is *prefix-decomposable* if it
can be written as a condition on (P[l], P[r]) alone. Whenever this holds,
you can use a hashmap to count in O(n).

**Examples where this works:**
- Subarrays with sum = k: P[r] - P[l] = k.
- Subarrays with equal 0s and 1s: treat 0 as -1, then P[r] = P[l].
- Subarrays divisible by k: P[r] mod k = P[l] mod k.
- Subarrays with XOR = k: prefix XOR, then X[r] ^ X[l] = k, so X[l] = X[r] ^ k.

**Examples where this fails:**
- Subarrays with min >= k: min is not prefix-decomposable. Use sliding window
  or segment tree instead.
- Subarrays with at most k distinct elements: not decomposable. Use sliding
  window.

### The Difference Array Dual

Prefix sums answer point queries after range updates. Difference arrays
answer range queries after point updates. They are *inverses*:

    D[i] = A[i] - A[i-1]    (difference)
    A[i] = D[0] + D[1] + ... + D[i]    (prefix sum)

To add v to A[l..r]: set D[l] += v, D[r+1] -= v. Then reconstruct A by
prefix sum. This gives O(1) per update, O(n) to reconstruct.

---

## Pattern 3: State Augmentation

When a standard algorithm does not capture enough information, add dimensions
to the state. The algorithm stays the same; only the state space changes.

### Formal Framework

**Standard problem:** Find shortest path from s to t in graph G = (V, E).
State: (vertex). Algorithm: Dijkstra. Complexity: O((V+E) log V).

**Augmented problem:** Find shortest path from s to t using at most K
resources. State: (vertex, resources_used). The graph becomes
G' = (V x {0,...,K}, E'), where each edge in E generates up to K+1 edges
in E' (one for each resource level).

Complexity: O(K * (V+E) * log(K*V)).

### Canonical Examples

| Original State | Augmented State | Why |
|---|---|---|
| (node) | (node, stops_used) | Flight routing with limited stops |
| (node) | (node, coupon_used) | One-time discount edge |
| (position) | (position, last_element) | DP where transitions depend on history |
| (position) | (position, bitmask) | TSP / bitmask DP |
| (cell) | (cell, keys_collected) | Grid with locked doors |

### The Cost of Augmentation

Every new dimension multiplies the state space. This is the fundamental
tradeoff:
- One boolean flag: 2x states.
- One counter 0..K: (K+1)x states.
- A bitmask of m items: 2^m x states.

**Rule of thumb:** Augmentation is viable when the product of all dimensions
fits in ~10^7 states.

---

## Pattern 4: Monotonicity Exploitation

**Principle.** Whenever a function is monotone (non-decreasing or
non-increasing), you can replace linear search with binary search or
two pointers, saving a factor of O(n) or more.

### Where Monotonicity Appears

1. **Sorted arrays.** By definition. Binary search gives O(log n) lookup.

2. **Prefix sums of non-negative arrays.** If a[i] >= 0 for all i, then
   P[i] is non-decreasing. This means:
   - "Find smallest r such that P[r] >= target" is a binary search.
   - Sliding window with sum constraint: both endpoints move right.

3. **Two pointers on sorted data.** If we need pairs (i, j) with
   a[i] + a[j] = target, sort the array. As i increases, j must decrease
   (monotonicity of the required complement).

4. **Decision problem monotonicity.** "Can we solve the problem with
   parameter k?" If this is monotone in k, binary search on k.

5. **DSU edge additions.** As edges are added, the number of components
   monotonically decreases. The size of the largest component monotonically
   increases.

### Two Pointers: The Formal Condition

**Theorem.** Let P(l, r) be a predicate on intervals. Two pointers works
(in O(n) total) if:
1. P(l, r) = true and r' >= r implies P(l, r') = true (or the symmetric version).
2. For each l, you want the extremal r satisfying P.

Equivalently: the set of valid (l, r) pairs forms a "staircase" shape.

### Sliding Window as Monotone Pointer Movement

A sliding window of size at most W:
- Right pointer r moves from 0 to n-1: n steps.
- Left pointer l only moves right: at most n steps total.
- Total work: O(n), not O(n*W).

This is *amortized* O(1) per element (see Pattern 7).

---

## Pattern 5: Complement Counting

**Principle.** To count objects satisfying property P, compute:

    |P| = |Universe| - |not P|

This is useful when "not P" is structurally simpler than P.

### When to Use Complement Counting

1. **"At least one" conditions.** P = "at least one success in k trials."
   Not P = "zero successes." Often: |not P| = (1 - p)^k, much simpler.

2. **Connectivity.** "Count cells in enclosed regions." Instead, BFS from
   the boundary to find all exterior cells. Interior = total - exterior.

3. **Counting valid pairs.** "Count pairs where a[i] and a[j] are coprime."
   If this is hard directly, count pairs that share a common factor and
   subtract (inclusion-exclusion).

4. **Derangements and forbidden positions.** Inclusion-exclusion is
   complement counting generalized to multiple forbidden conditions:
   |A1 union A2 union ... union Ak| = sum|Ai| - sum|Ai intersect Aj| + ...

### Inclusion-Exclusion: The General Form

**Theorem (Inclusion-Exclusion).** For events A1, ..., Ak:

    |A1 ∪ ... ∪ Ak| = Σ|Ai| - Σ|Ai ∩ Aj| + Σ|Ai ∩ Aj ∩ Ak| - ...

Complexity: 2^k terms. Viable when k is small (k <= 20).

**Application to counting with divisibility:**
Count integers in [1, n] divisible by at least one of p1, ..., pk:
- |div by pi| = floor(n/pi)
- |div by pi and pj| = floor(n / lcm(pi, pj))
- Apply inclusion-exclusion.

---

## Pattern 6: The Components-Minus-One Principle

**Theorem.** A forest (acyclic graph) with n vertices and c connected
components has exactly n - c edges. Equivalently, connecting c components
into one requires exactly c - 1 additional edges.

### Why This Appears Everywhere

This is a consequence of the fundamental property of trees: a tree on k
vertices has exactly k - 1 edges. A forest with c components is c disjoint
trees, so total edges = (n1 - 1) + (n2 - 1) + ... + (nc - 1) = n - c.

### Applications

1. **"How many roads to build?"** Given n cities and some existing roads,
   answer = (number of connected components) - 1. Use BFS/DFS/DSU to count
   components.

2. **Ice skating problem.** Points on a grid; you can slide along a row or
   column. Two points are connected if they share a row or column. Answer =
   (number of connected components) - 1.

3. **Network repair.** Given a network with some links down, minimum links
   to restore full connectivity = components - 1.

4. **Minimum spanning tree edge count.** An MST of a connected graph with
   n vertices always has n - 1 edges. If the graph has c components, the
   minimum spanning forest has n - c edges.

---

## Pattern 7: Amortized Pointer Movement

**Principle.** If a pointer only moves in one direction and covers at most n
positions total (across ALL iterations of an outer loop), then the total work
from that pointer is O(n), regardless of how it moves within individual
iterations.

### Formal Statement (Aggregate Analysis)

Let r_0 = 0. In iteration i, the pointer moves from r_{i-1} to r_i, where
r_i >= r_{i-1} (non-decreasing). The work in iteration i is
O(r_i - r_{i-1}). Total work:

    Σ (r_i - r_{i-1}) = r_final - r_0 <= n

This is a telescoping sum. The O(n) bound follows immediately.

### Structures That Use This Principle

| Structure | Forward Pointer | Total Movement |
|---|---|---|
| Two pointers | right pointer r | O(n) |
| Sliding window | both l and r | O(n) each |
| Monotonic stack | push pointer | O(n) pushes, O(n) pops |
| KMP failure function | mismatch pointer | O(n) |
| Euler tour traversal | edge pointer | O(E) |

### Monotonic Stack: A Detailed Example

For each element, we push it onto the stack (O(1)) and potentially pop
several elements. Each element is pushed exactly once and popped at most
once. Total pushes: n. Total pops: at most n. Total work: O(n).

This gives O(n) algorithms for:
- Next greater element (left and right).
- Largest rectangle in histogram.
- Sum of subarray minimums.

---

## Pattern 8: Space-Time Tradeoffs in DP

### The Full Table

Standard DP: compute and store every state.
- Time: O(|states| * |transitions per state|)
- Space: O(|states|)

### Rolling Arrays

**When applicable:** The recurrence for layer i depends only on layer i-1
(or a constant number of previous layers).

**Technique:** Keep only the last 1 or 2 layers in memory.

**Examples:**
- Grid DP: dp[i][j] depends on dp[i-1][j] and dp[i][j-1]. Keep two rows.
- Knapsack: dp[i][w] depends on dp[i-1][w] and dp[i-1][w - wi]. Keep one
  row, iterate w backwards.
- Fibonacci: only need the last 2 values.

**Space reduction:** From O(n * m) to O(m), or from O(n) to O(1).

### Bitset Compression

For boolean DP (each state is 0 or 1), store the DP table as a bitset.

**Benefit:** Operations on 64 bits at once via bitwise operations.
Space: O(|states| / 64). Time: can also improve by factor of 64 for
certain transitions (e.g., subset sum: `bits |= bits << w`).

### Meet-in-the-Middle

Split the problem into two halves of size n/2. Solve each half exhaustively
(2^{n/2} states), then combine.

**Complexity:** O(2^{n/2} * n) instead of O(2^n). For n = 40, this reduces
from ~10^{12} to ~10^6.

---

## Pattern 9: Inverse Operations Enable Efficiency

### The Algebraic Principle

An operation * has an inverse if for every a, there exists a^{-1} such that
a * a^{-1} = identity.

**Why this matters for range queries:**

If * has an inverse, then:
    aggregate(l, r) = prefix(r) * prefix(l)^{-1}

This gives O(1) range queries after O(n) preprocessing (prefix computation).

### Classification of Common Operations

| Operation | Identity | Inverse | O(1) Range Query via Prefix? |
|---|---|---|---|
| Addition (+) | 0 | Subtraction (-) | Yes: P[r+1] - P[l] |
| XOR (^) | 0 | XOR (self-inverse) | Yes: X[r+1] ^ X[l] |
| Multiplication (*) | 1 | Division (/) | Yes (if no zeros; with mod, use modular inverse) |
| GCD | 0 | None | No. Use sparse table: O(1) query, O(n log n) build |
| Min / Max | +inf / -inf | None | No. Use sparse table or segment tree |
| String concat | "" | None | No. But prefix hashing gives O(1) substring hash |

### Consequences for Sliding Window

- **Invertible operation (sum, XOR):** Maintain a running aggregate.
  When the window slides, subtract the outgoing element, add the incoming.
  O(1) per step.

- **Non-invertible operation (min, max, GCD):**
  - **Monotonic deque:** O(1) amortized per step for min/max.
  - **Two-stack trick:** Maintain two stacks, each with running aggregates.
    When one empties, pour the other into it with recomputed aggregates.
    O(1) amortized for any associative operation.
  - **Sparse table:** O(1) per query but requires static data.

---

## Pattern 10: Symmetry Breaking and Canonical Forms

**Principle.** When a problem has symmetry (multiple equivalent
representations of the same object), fix a canonical form to avoid
counting duplicates or exploring redundant states.

### Examples

1. **Permutation generation.** To avoid generating the same set in multiple
   orders, always generate elements in non-decreasing order.

2. **Graph isomorphism.** To compare graphs, compute a canonical labeling
   (e.g., sort adjacency lists, use degree sequences as fingerprints).

3. **Cycle detection in permutations.** Instead of checking all starting
   points, start from the smallest unvisited element.

4. **Coordinate normalization.** When only relative order matters (not
   absolute values), compress coordinates to {0, 1, ..., n-1}.

5. **Modular arithmetic.** When working modulo m, always keep values in
   [0, m-1] to ensure a unique representative.

---

## Pattern 11: Greedy Validation via Exchange Argument

**Principle.** To prove a greedy algorithm is correct, show that any optimal
solution that differs from the greedy solution can be modified (by swapping
or exchanging elements) to become at least as good AND closer to the greedy
solution.

### Formal Template

1. Let G = greedy solution, O = any optimal solution.
2. Find the first point where G and O differ.
3. Show that modifying O to agree with G at this point does not worsen
   the objective.
4. By induction, O can be transformed into G without worsening, so G is
   optimal.

### Classic Applications

- **Activity selection.** Sort by finish time. Exchange argument: if the
  optimal solution picks a later-finishing activity, swapping in the
  earlier-finishing one cannot conflict with fewer future activities.

- **Huffman coding.** Exchange argument: if two least-frequent symbols are
  not at maximum depth, swapping them there does not increase total cost.

- **Fractional knapsack.** Sort by value/weight ratio. Exchange argument:
  replacing a lower-ratio item with a higher-ratio item improves the
  objective.

---

## Pattern 12: The Small-to-Large Merging Principle

**Principle.** When merging two sets, always merge the smaller into the
larger. This guarantees O(n log n) total work.

### Why O(n log n)

Each element, when merged, moves into a set at least twice as large.
Therefore, each element can be merged at most log n times before it is in a
set of size n. Total work: O(n log n).

### Applications

- **DSU (Union by Size/Rank).** This is exactly small-to-large merging of
  component member lists. It guarantees O(n log n) total for all unions
  (and O(alpha(n)) amortized per operation with path compression).

- **Heavy-light decomposition.** Conceptually similar: each node's data is
  merged into its heavy child's chain, and light edges cause at most O(log n)
  chain switches per root-to-leaf path.

- **Merging frequency maps.** When combining subtree information in tree DP,
  merge the smaller child's map into the larger child's map. O(n log n) total
  across all merges.

---

## Summary: The Pattern Selection Heuristic

When facing a new problem, ask these questions in order:

1. **Can I reduce this to a known problem?** (Pattern 1)
   - Is there a monotone structure? -> Binary search on answer.
   - Can I change variables to get a standard form?
   - Can I model this as a graph?

2. **Does the problem involve ranges or subarrays?** (Patterns 2, 9)
   - Is the condition prefix-decomposable? -> Prefix sums + hashmap.
   - Is the operation invertible? -> Prefix aggregates for O(1) queries.
   - Not invertible? -> Segment tree, sparse table, or monotonic deque.

3. **Does a standard algorithm almost work but lack information?** (Pattern 3)
   - Add a dimension to the state.

4. **Is there a monotone function I can exploit?** (Pattern 4)
   - Binary search, two pointers, sliding window.

5. **Is counting directly hard?** (Pattern 5)
   - Try complement counting or inclusion-exclusion.

6. **Is the answer related to connected components?** (Pattern 6)
   - Answer is probably (components - 1) or similar.

7. **Can I prove a greedy approach?** (Pattern 11)
   - Try the exchange argument.

8. **Is the state space too large?** (Pattern 8)
   - Rolling arrays, bitset compression, meet-in-the-middle.
