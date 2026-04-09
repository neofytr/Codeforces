# Advanced DP Techniques: A Personal Handbook

---

This file is a self-contained reference for advanced DP patterns. Every technique here was
learned the hard way. Each section covers: (1) the problem pattern it solves, (2) the key
insight, (3) a formal proof or justification, and (4) code where it helps. Read slowly.
Re-derive everything.

---

## Technique 1: Push DP / Forward DP

### Problem Pattern

You are computing dp[r], but the transition naturally depends on dp[r + l] --- that is,
future states. In pull-DP (the standard style), you compute dp[r] from already-computed
predecessors. When the recurrence "reaches forward", pull-DP becomes awkward or impossible.

### Key Insight

Instead of asking "where does dp[r] get its value FROM?", ask "where does dp[r] SEND its
value TO?". This is push-DP: iterate states in topological order, and for each computed
dp[r], update all states that depend on it.

### When to Use

- The transition for dp[r] involves dp[r + l] for some offset l > 0.
- The set of predecessors for a state is hard to enumerate, but the set of successors is easy.
- Recursive (top-down) DP naturally handles forward dependencies via memoization, so
  recursion is an alternative to explicit push-DP.

### Formal Justification

Push-DP and pull-DP compute exactly the same values. The dependency DAG is the same; only
the traversal direction differs. In pull-DP, when you visit state s, all predecessors are
already computed and you read from them. In push-DP, when you visit state s (already
computed), you write into each successor s'. By the time you later visit s' (in topological
order), all its predecessors have already pushed their contributions.

Proof: Let s_1, s_2, ..., s_n be a topological ordering. In push-DP, when we process s_i,
we add s_i's contribution to every s_j with (s_i, s_j) in E. When we reach s_j, every s_i
with i < j and (s_i, s_j) in E has already been processed (since i < j in topological
order). Since ALL predecessors of s_j have index < j (by definition of topological order),
s_j has received all its contributions. QED.

### Code Template

```cpp
// Push DP skeleton
// dp[start] = base_value;
for (int r = 0; r < n; r++) {
    if (dp[r] == UNSET) continue;  // unreachable state
    for (auto [next, cost] : transitions(r)) {
        dp[next] = combine(dp[next], dp[r] + cost);  // push contribution forward
    }
}
// answer = dp[target];
```

---

## Technique 2: String DP Patterns (Edit Distance as Canonical Example)

### Problem Pattern

Given two strings A[1..m] and B[1..n], compute some optimal alignment: edit distance,
longest common subsequence, sequence alignment, etc.

### The Four Rules

**Rule 1: Compare prefixes.** Define dp[i][j] to relate A[1..i] to B[1..j]. This gives
(m+1)(n+1) states, and the answer is dp[m][n].

**Rule 2: Match vs operate.** When A[i] == B[j], the characters "match for free" --- no
operation is needed, and we inherit from dp[i-1][j-1].

**Rule 3: Three choices become one min.** When characters do not match, we have (typically)
three operations: replace (dp[i-1][j-1] + 1), delete from A (dp[i-1][j] + 1), insert into
A (dp[i][j-1] + 1). Take the minimum.

**Rule 4: Base cases are edge strings.** dp[0][j] = cost of transforming empty string to
B[1..j]. dp[i][0] = cost of transforming A[1..i] to empty string.

### Edit Distance Recurrence

```
dp[0][j] = j                          (insert j characters)
dp[i][0] = i                          (delete i characters)

dp[i][j] = dp[i-1][j-1]              if A[i] == B[j]   (match: no cost)
dp[i][j] = 1 + min(
    dp[i-1][j-1],                     (replace A[i] with B[j])
    dp[i-1][j],                        (delete A[i])
    dp[i][j-1]                         (insert B[j] into A)
)                                      if A[i] != B[j]
```

### Proof of Correctness

By induction on i + j. Base cases are trivially correct. For the inductive step, consider
the last operation in an optimal edit sequence transforming A[1..i] to B[1..j]. It must be
one of: (a) A[i] matches B[j] and we align them (cost = dp[i-1][j-1] if they are equal),
(b) we replace A[i] to become B[j] (cost = 1 + dp[i-1][j-1]), (c) we delete A[i] (cost =
1 + dp[i-1][j]), or (d) we insert B[j] at the end (cost = 1 + dp[i][j-1]). The recurrence
takes the minimum over all applicable cases, which by inductive hypothesis are all optimal.

---

## Technique 3: Ordered Inclusion-Exclusion DP (First-Violation DP)

### Problem Pattern

You are counting objects built step-by-step (placing items into positions, filling slots,
constructing sequences), where certain states are forbidden. Direct inclusion-exclusion over
all subsets of forbidden states is exponential (2^k terms). You need a polynomial method.

### Key Insight

Every invalid object has a UNIQUE earliest violation. Partition all objects by the index of
their first bad state. This converts exponential IE into a DP.

### The Formula

Let dp[i] = number of VALID objects that pass through state i (where "valid" means valid
at ALL states up to and including i). Then:

```
dp[i] = total(i) - sum_{j < i} dp[j] * ways(j -> i)
```

Where:
- total(i) = total objects reaching state i with NO constraints at all.
- dp[j] * ways(j -> i) = objects that are valid through state j, then violate at some point
  between j and i. But since j < i and dp[j] counts objects valid through j, and ways(j -> i)
  counts unconstrained completions from j to i, this product counts objects whose first
  violation is at j (or between j and i).

### Why This Works: Full Derivation

**Claim:** The subtracted terms partition all invalid objects by their first violation, with
no double-counting.

**Proof:**

(1) **Monotone state order.** States are ordered: 1, 2, ..., n. An object visits states in
    this fixed order.

(2) **Irrevocability.** Once you pass state j, you cannot return to modify the choices made
    at or before state j.

(3) **Disjoint partition.** Consider any invalid object X. Let j be its EARLIEST violated
    state. Then X is valid at all states before j. This means X is counted in dp[j'] for all
    j' < j (since it is valid through those states). But X is subtracted exactly once: in the
    term dp[j] * ways(j -> i) for the appropriate i. Why exactly once? Because the first
    violation is unique --- X is valid through state j-1 but invalid at state j. It appears
    in the dp[j-1] * ways(j-1 -> i) term but NOT as a valid-through-j object.

More precisely: dp[i] starts with total(i), which counts all objects (valid and invalid)
reaching state i. We subtract dp[j] * ways(j -> i) for each j < i. The term dp[j] counts
objects genuinely valid through state j. Multiplying by ways(j -> i) extends them to state i
without constraints. The objects that remain (dp[i]) are those valid through all states up
to i.

This is essentially inclusion-exclusion, but organized by first violation rather than by
subset of violations. The "ordered" structure makes each object appear in exactly one
correction term, avoiding the exponential blowup.

### When It Applies

- Objects are built sequentially (positions 1, 2, ..., n).
- "Validity" at each position can be checked independently given the object so far.
- Counting unconstrained extensions (ways(j -> i)) is efficient.
- The number of "checkpoint" states is polynomial.

---

## Technique 4: Reverse Inner Loop for 0/1 Knapsack (1D Compression)

### Problem Pattern

Standard knapsack: dp[i][s] depends only on dp[i-1][s] (do not take item i) and
dp[i-1][s - w_i] (take item i). Since row i depends only on row i-1, we can compress
to a single 1D array. But the iteration order of the inner loop matters critically.

### Key Insight

For 0/1 knapsack (each item used at most once): iterate the capacity **backward**.
For unbounded knapsack (each item used any number of times): iterate **forward**.

### Full Proof: Why Backward Works for 0/1

Consider the 1D update: dp[s] = max(dp[s], dp[s - w_i] + v_i).

**Backward iteration (s = W, W-1, ..., w_i):**

When we compute dp[s], the value dp[s - w_i] has NOT yet been updated in this iteration
(because s - w_i < s, and we are going from high to low). So dp[s - w_i] still holds its
value from the PREVIOUS item (row i-1). This is exactly dp[i-1][s - w_i], which is what
the 0/1 recurrence requires.

**Why forward breaks for 0/1:**

If we iterate s = w_i, w_i+1, ..., W, then when we compute dp[s], dp[s - w_i] has ALREADY
been updated in the current iteration. So dp[s - w_i] = dp[i][s - w_i], which may already
include item i. This means item i can be "used again" --- we get the unbounded knapsack.

**Why forward is correct for unbounded:**

In unbounded knapsack, reusing item i is legal. The recurrence is dp[i][s] = max(dp[i-1][s],
dp[i][s - w_i] + v_i). Note the second term uses dp[i][...] (same row), not dp[i-1][...].
Forward iteration gives exactly this: dp[s - w_i] is already updated to dp[i][s - w_i].

### Multidimensional Extension

If there are multiple resource dimensions (weight, volume, etc.), ALL dimensions must be
iterated backward for 0/1 knapsack. If any dimension is iterated forward, items can be
reused along that dimension.

### Code

```cpp
// 0/1 Knapsack, 1D compression
int dp[W + 1] = {};  // dp[s] = max value with capacity s
for (int i = 0; i < n; i++) {
    for (int s = W; s >= w[i]; s--) {       // BACKWARD
        dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
    }
}

// Unbounded Knapsack, 1D compression
int dp[W + 1] = {};
for (int i = 0; i < n; i++) {
    for (int s = w[i]; s <= W; s++) {        // FORWARD
        dp[s] = max(dp[s], dp[s - w[i]] + v[i]);
    }
}
```

---

## Technique 5: Value-Based Knapsack (Swapping Roles)

### Problem Pattern

Knapsack where the capacity W is enormous (say 10^9) but the total value sum is small
(say sum of all values <= 10^5). Indexing by capacity is infeasible.

### Key Insight

Swap roles: instead of "for each capacity, maximize value", do "for each value, minimize
weight". Then filter by capacity at the end.

### Recurrence

Let dp[v] = minimum total weight to achieve exactly value v.

```
dp[0] = 0
dp[v] = infinity   for v > 0 (initially)

For each item i with weight w_i and value v_i:
    for v = V_max down to v_i:             // backward for 0/1
        dp[v] = min(dp[v], dp[v - v_i] + w_i)

Answer = max { v : dp[v] <= W }
```

### Correctness

This is a standard knapsack where "weight" and "value" swap their roles in the DP indexing.
The constraint (capacity W) is checked after the DP completes, rather than being the DP
index. The DP ensures minimum weight for each achievable value, so if dp[v] <= W, value v
is achievable within capacity.

### Complexity

O(n * V_total) where V_total = sum of all item values. This is efficient when V_total is
small even if W is huge.

---

## Technique 6: DP with Greedy Ordering (Exchange Argument + DP)

### Problem Pattern

You have n items with multiple attributes, and you need to select/schedule a subset
optimally. The DP transition assumes items are processed in some order, but the problem
does not specify an order. Different orderings yield different DP results, and brute-forcing
all orderings is n!.

### Key Insight

"ORDER FIXES FEASIBILITY, DP OPTIMIZES VALUE."

The greedy step does not choose items --- it only establishes the order in which items should
be considered. Once the order is fixed, the DP handles the actual selection.

### The Full 8-Step Procedure

**Step 1: Identify the ordering dependency.** Determine which aspect of the DP transition
depends on the order of items. Usually, it is a constraint that tightens as you process
more items (e.g., accumulated weight, elapsed time, remaining budget).

**Step 2: Pairwise exchange argument.** Consider two adjacent items i and j. Compute the
cost/feasibility of placing i before j vs j before i. If one ordering is always at least as
good as the other (given some condition on i and j's attributes), you have found the greedy
criterion.

**Step 3: Derive the comparator.** From the exchange argument, extract a comparison function
cmp(i, j) that returns true if i should come before j.

**Step 4: Verify strict weak ordering.** The comparator must satisfy:
  - Irreflexivity: not cmp(x, x).
  - Asymmetry: if cmp(x, y), then not cmp(y, x).
  - Transitivity: if cmp(x, y) and cmp(y, z), then cmp(x, z).
If these fail, the sort is undefined behavior (literally, in C++).

**Step 5: Sort items by the comparator.**

**Step 6: Run DP on sorted items.** The DP processes items in the sorted order. Because the
order is optimal (by the exchange argument), any solution the DP might miss due to a
different ordering is provably no better than one it considers.

**Step 7: Extract the answer from the DP table.**

**Step 8: Verify.** On small cases, check that reordering items does not improve the answer.

### Proof That Sorting Suffices

**Theorem:** If the exchange argument shows that swapping two adjacent out-of-order items
never worsens the objective, then the globally sorted order is optimal among all orderings.

**Proof:** Any permutation can be reached from any other by a sequence of adjacent swaps
(bubble sort). If every swap that "corrects" the order (moves toward the sorted permutation)
is non-worsening, then the sorted permutation is at least as good as any other. Formally,
the number of inversions (pairs out of sorted order) decreases with each correcting swap,
and the objective never worsens, so the sorted order (zero inversions) is globally optimal.

### Classic Example: Job Scheduling with Deadlines and Penalties

Items have weight w_i and deadline d_i. Processing i before j is better when
w_i + d_j >= w_j + d_i, i.e., sort by w_i - d_i (or equivalently d_i - w_i ascending).
After sorting, run knapsack DP to select which jobs to do within their deadlines.

---

## Technique 7: Counting DP --- v=0 vs v>=1 Optimization

### Problem Pattern

You have a counting/optimization DP where for each item type, you can use it 0, 1, 2, ...,
up to some limit k times. The naive inner loop over usage count v = 0, 1, ..., k makes the
transition O(k) per state.

### Key Insight

Split the transition into two cases:
- **v = 0:** Do not use item i at all. Transition from the previous item's layer.
- **v >= 1:** Use item i at least once. Transition from the SAME item's layer with one fewer
  usage (i.e., reduce the state by one unit of item i).

This converts the O(k) inner loop into O(1) per state.

### Formal Derivation

Let dp[i][s] = number of ways to form state s using items 1..i.

Naive recurrence:
```
dp[i][s] = sum_{v=0}^{k_i} dp[i-1][s - v * w_i]
```
This is O(k_i) per state.

Optimized: define dp[i][s] by cases.
```
dp[i][s] = dp[i-1][s]                          (v = 0: item i not used)
          + dp[i][s - w_i]                      (v >= 1: item i used at least once more)
```

Why does the second term work? If we use item i at least once, we can "peel off" one copy.
The remaining s - w_i must also be formed using items 1..i (same layer, since we might use
item i again). This is exactly dp[i][s - w_i].

For bounded knapsack (at most k_i copies), this simple trick does not directly apply without
additional correction. It works perfectly for unbounded knapsack.

For bounded: dp[i][s] = dp[i-1][s] + dp[i][s - w_i] - dp[i-1][s - (k_i + 1) * w_i].
The subtracted term removes the overcount from using more than k_i copies.

---

## Technique 8: Bounded Knapsack via Binary Decomposition

### Problem Pattern

0/1 knapsack with item multiplicities: item r has weight w_r, value v_r, and up to k_r
copies available. Treating each copy as a separate item gives O(W * sum(k_r)) time, which
is too slow when k_r is large.

### Key Insight

Represent each count 0, 1, ..., k_r using O(log k_r) "grouped" items with sizes that are
powers of 2.

### The Decomposition

For item r with k_r copies, create items with multiplicities: 1, 2, 4, 8, ..., 2^{p-1},
and a remainder term k_r - (2^p - 1), where p is the largest integer such that 2^p - 1 <= k_r.

Example: k_r = 13. We create items with counts 1, 2, 4, 6 (since 1+2+4 = 7 <= 13, next
power 8 would give 15 > 13, so remainder = 13 - 7 = 6).

Each "grouped" item of count c has weight c * w_r and value c * v_r, and is treated as a
single 0/1 item (take it or leave it).

### Proof of Representability

**Claim:** Every integer in {0, 1, ..., k_r} can be represented as a subset sum of
{1, 2, 4, ..., 2^{p-1}, k_r - 2^p + 1}.

**Proof:** The powers 1, 2, ..., 2^{p-1} can represent every integer in {0, 1, ..., 2^p - 1}
(standard binary representation). Adding the remainder R = k_r - 2^p + 1, we can also
represent every integer in {R, R+1, ..., R + 2^p - 1} = {R, ..., k_r}. Since R <= 2^p - 1
(because k_r <= 2^{p+1} - 2 by choice of p... actually more precisely: R = k_r - 2^p + 1
and 2^p - 1 <= k_r, so R <= k_r - (k_r) + ... let me be precise). We have R = k_r - 2^p + 1
and 2^p - 1 <= k_r, so R <= k_r - (2^p - 1) = k_r - 2^p + 1. Also the range {0,...,2^p - 1}
and {R,...,k_r} overlap since R <= 2^p (as k_r < 2^{p+1} implies R < 2^p + 1). So their
union is {0, ..., k_r}. QED.

### Complexity

O(log k_r) items per original item. Total time: O(W * sum_r(log k_r)).

### Code

```cpp
vector<pair<int,int>> items;  // (weight, value) of decomposed items
for (int r = 0; r < n; r++) {
    int remaining = k[r];
    for (int p = 1; remaining > 0; p *= 2) {
        int count = min(p, remaining);
        items.push_back({count * w[r], count * v[r]});
        remaining -= count;
    }
}
// Now run standard 0/1 knapsack on items[]
```

---

## Technique 9: Modulo Decomposition + Sliding Window DP

### Problem Pattern

Knapsack-style transition: dp[i][x] = OP over {dp[i-1][x - t * w_i] : t = 0, 1, ..., k_i},
where OP is min, max, or sum. Naively O(k_i) per state. We want O(1) amortized.

### Key Insight

All predecessor states x - t * w_i for varying t share the same remainder r = x mod w_i.
Fix r, and let x = r + q * w_i. Then predecessors are at q' = q, q-1, ..., q-k_i. This is
a sliding window of width k_i over a 1D array indexed by q. Use a monotonic deque for
min/max, or prefix sums for sum.

### Full Derivation

Let w = w_i for brevity. For each remainder r in {0, 1, ..., w-1}, define:

    f(q) = dp[i-1][r + q * w]       (the previous layer's value at capacity r + q*w)

The transition becomes:

    dp[i][r + q * w] = OP_{t=0}^{min(q, k_i)} { f(q - t) + t * v_i }

For min/max, rewrite by separating the terms:

    dp[i][r + q * w] = OP_{t=0}^{min(q, k_i)} { (f(q-t) - (q-t)*v_i) } + q * v_i

Define g(j) = f(j) - j * v_i. Then:

    dp[i][r + q * w] = q * v_i + OP_{j in [q - k_i, q]} { g(j) }

This is a sliding window OP over g, with window size k_i, as q increases. Use a monotonic
deque.

### Code (Sliding Window Min for Knapsack)

```cpp
// For each item i with weight w, value v, count k:
for (int r = 0; r < w; r++) {
    deque<pair<int,int>> dq;  // (g_value, index_q)
    int max_q = (W - r) / w;
    for (int q = 0; q <= max_q; q++) {
        int j = r + q * w;
        int g = dp[j] - q * v;  // dp[] is from previous layer

        // Remove elements outside window
        while (!dq.empty() && dq.front().second < q - k)
            dq.pop_front();

        // Maintain monotonicity (for min: remove larger; for max: remove smaller)
        while (!dq.empty() && dq.back().first >= g)  // for min
            dq.pop_back();

        dq.push_back({g, q});
        dp[j] = dq.front().first + q * v;  // update in-place (careful with ordering)
    }
}
```

### Complexity

For each item: O(w) remainders, each with O(W/w) elements, each processed in amortized O(1)
by the deque. Total per item: O(W). Grand total: O(n * W), independent of k_i.

---

## Technique 10: Greedy Dominance Principle

### Problem Pattern

A DP has many states at the same "stage" (same number of items processed, same prefix
length, etc.). Some states are provably never better than others for ANY future continuation.
These dominated states can be discarded, dramatically reducing state space.

### Key Insight

Among states at the same stage, if state A is "at least as good" as state B on every
dimension that matters for future transitions, then B is dominated by A and can be discarded.

When this applies aggressively enough, DP collapses into Greedy + Binary Search.

### The LIS Example (Canonical)

In Longest Increasing Subsequence, consider two subsequences of the same length k that end
at different values. The one ending at the smaller value is ALWAYS at least as good for
extension (any element that extends the larger-ending one also extends the smaller-ending
one, but not vice versa).

So we maintain: last[k] = smallest ending value among all increasing subsequences of length k.

**Dominance here:** Same length, smaller end dominates larger end. We only need one state per
length --- the dominant one.

### General Pattern for Dominance

Four conditions must hold:

**(1) States are comparable.** There exists a partial order on states at the same stage where
"A dominates B" is well-defined.

**(2) Future depends on few parameters.** The value of future transitions depends only on the
parameters used in the dominance comparison (e.g., subsequence length and ending value).

**(3) Monotonicity of transitions.** If A dominates B now, then after any valid transition
applied to both, A's successor still dominates B's successor (or B's successor does not
exist).

**(4) Exchange argument.** For any solution using dominated state B, there exists a solution
using dominant state A that is at least as good.

### How DP Becomes Greedy

When dominance is strong enough that only ONE state survives per stage, the DP reduces to a
greedy algorithm: at each step, make the choice that leads to the dominant state. Binary
search enters when you need to find the right state to update (as in LIS).

---

## Technique 11: LIS in O(n log n)

### The Algorithm

Maintain array last[1..L] where last[k] = smallest ending value of any increasing
subsequence of length k found so far. L = length of longest IS found so far.

For each element a[r]:
1. Binary search for the largest k such that last[k] < a[r].
2. Set last[k+1] = a[r].
3. Update L = max(L, k+1).

Answer: L.

### Proof That last[] Is Always Sorted

**Claim:** At every point during the algorithm, last[1] < last[2] < ... < last[L].

**Proof by contradiction:** Suppose last[k] >= last[k+1] for some k. Then there exists an
increasing subsequence S of length k+1 ending at last[k+1]. The first k elements of S form
an increasing subsequence of length k ending at S[k] < last[k+1] <= last[k]. But last[k] is
defined as the SMALLEST ending value of any IS of length k, so last[k] <= S[k] < last[k+1]
<= last[k]. Contradiction. QED.

**Consequence:** Binary search is valid because last[] is sorted.

### Why Binary Search Finds the Right Position

We want the longest subsequence we can extend with a[r]. This means we need the largest k
with last[k] < a[r]. Since last[] is sorted, this is a standard binary search
(upper_bound - 1, or lower_bound depending on convention).

### Counting Number of LIS

Track two arrays:
- dp[r] = length of LIS ending at index r.
- cnt[r] = number of distinct LIS of that length ending at index r.

For each r, dp[r] = 1 + max{dp[j] : j < r, a[j] < a[r]}, and cnt[r] = sum of cnt[j] over
all j achieving that max. Can be accelerated with BIT/segment tree.

### Code

```cpp
vector<int> last;  // 0-indexed: last[k] = smallest end of IS of length k+1
for (int r = 0; r < n; r++) {
    auto it = lower_bound(last.begin(), last.end(), a[r]);
    if (it == last.end())
        last.push_back(a[r]);
    else
        *it = a[r];
}
int LIS_length = last.size();
```

---

## Technique 12: 2D LIS (Envelope Nesting)

### Problem Pattern

Given n rectangles (or envelopes) with width w_i and height h_i, find the longest chain
where each rectangle strictly fits inside the next (w_i < w_j AND h_i < h_j).

### Key Insight

Sort by (width ascending, height DESCENDING for equal widths). Then run 1D LIS on the
height sequence.

### Why Descending Height for Equal Widths

If two envelopes have the same width, neither can nest inside the other (we need STRICT
inequality). If we sorted heights ascending for equal widths, LIS might pick both --- creating
an invalid chain where width is not strictly increasing.

By sorting heights descending within equal widths, any increasing subsequence of heights
must come from DIFFERENT widths (since same-width heights are decreasing, you cannot pick
two of them in an increasing subsequence).

### Formal Proof

**Claim:** After sorting by (w asc, h desc), every strictly increasing subsequence of h
values corresponds to a valid nesting chain.

**Proof:** Let h_{i_1} < h_{i_2} < ... < h_{i_k} be a strictly increasing subsequence
(where i_1 < i_2 < ... < i_k in the sorted order).

For any consecutive pair i_a, i_{a+1}:
- Since i_a < i_{a+1} in sorted order: w_{i_a} <= w_{i_{a+1}}.
- Since h_{i_a} < h_{i_{a+1}} and within equal widths, heights are sorted descending:
  if w_{i_a} == w_{i_{a+1}}, then h_{i_a} > h_{i_{a+1}} (descending order), contradicting
  h_{i_a} < h_{i_{a+1}}.
- Therefore w_{i_a} < w_{i_{a+1}} (strict).

So we have both w_{i_a} < w_{i_{a+1}} and h_{i_a} < h_{i_{a+1}} for every consecutive pair.
This is a valid nesting chain. QED.

### Code

```cpp
sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
    return a.w < b.w || (a.w == b.w && a.h > b.h);  // width asc, height DESC
});

// Run standard O(n log n) LIS on the h values
vector<int> last;
for (auto& e : envelopes) {
    auto it = lower_bound(last.begin(), last.end(), e.h);
    if (it == last.end()) last.push_back(e.h);
    else *it = e.h;
}
int ans = last.size();
```

---

## Technique 13: Sliding Range Minimum/Maximum in DP

### Problem Pattern

A DP transition of the form: dp[i] = min (or max) over dp[j] for j in some sliding window
[i - K, i - 1]. Naive: O(K) per state. We want O(1) amortized.

### Key Insight

Maintain a monotonic deque (monoqueue). For sliding minimum: the deque stores indices in
increasing order, with corresponding dp values also in increasing order. The front of the
deque is always the minimum in the current window.

### Invariant

The deque stores a subset of indices in the current window [i - K, i - 1] such that:
1. Indices are in increasing order (front to back).
2. dp values at those indices are in increasing order (for min) or decreasing order (for max).
3. For every index j in the window but NOT in the deque, there exists an index j' in the
   deque with j' > j and dp[j'] <= dp[j] (for min). In other words, j was removed because
   a later, better value made it useless.

### Why Amortized O(1)

Each index is pushed onto the deque exactly once and popped at most once (either from the
front when it leaves the window, or from the back when a better element arrives). Total
operations over n steps: at most 2n pushes and 2n pops = O(n). Amortized O(1) per step.

### Code Template

```cpp
// Sliding window minimum over dp[] with window size K
// new_dp[i] = min(dp[j] for j in [i-K, i-1]) + cost[i]
deque<int> dq;  // stores indices
for (int i = 0; i < n; i++) {
    // Remove indices that have left the window
    while (!dq.empty() && dq.front() < i - K)
        dq.pop_front();

    // Current answer uses front of deque (if window is non-empty)
    if (!dq.empty())
        new_dp[i] = dp[dq.front()] + cost[i];

    // Before adding i to deque (for future windows that include i):
    // Remove indices from back that are worse than dp[i]
    while (!dq.empty() && dp[dq.back()] >= dp[i])
        dq.pop_back();
    dq.push_back(i);
}
```

---

## Technique 14: DP Lessons Collection

These are recurring patterns and pitfalls encountered across many problems. Each is a
condensed principle.

### Lesson 1: "Subset of Subset" --- Model Both Choices in One State

When the problem involves choosing a set S and then a subset T of S, do NOT run two
separate DPs. Instead, design a single DP whose state tracks the status of each element:
unused, in S but not T, or in both S and T. This avoids the combinatorial explosion of
iterating over all possible S.

### Lesson 2: Inner Decisions Depend on Outer --- Add Dimensions

If a transition within the DP requires making a sub-decision that depends on the current
state, add a dimension to the DP for that sub-decision rather than trying to compute it
on the fly. The extra dimension makes the dependency explicit and the recurrence clean.

### Lesson 3: Items with Multiple Roles

When an item can play different roles (unused, used in one structure, used in another),
define the DP state to track which role each item has been assigned. Typical encoding: DP
state includes a counter or flag for each role.

### Lesson 4: dp[r] Depends Only on dp[r-1] --- Compress

If the recurrence for layer r references only layer r-1 (not r-2, r-3, etc.), you can
drop the layer index and use a single array, updating in the correct order (backward for
0/1 knapsack, forward for unbounded). This saves a factor of n in memory.

This is the same principle as Technique 4, but stated generally: it applies to any DP
where only the immediately previous layer matters, not just knapsack.

### Lesson 5: Nested Constrained Choices --- Model Together, Define Precisely

When the problem has two or more interleaved choices with constraints between them, resist
the urge to handle them separately. Define a DP state that captures all active constraints
simultaneously. The state space may be larger, but the transitions become correct and clean.

The key discipline: write down EXACTLY what dp[state] represents. If the definition is
ambiguous, the recurrence will be wrong. Precision in the state definition is the single
most important step in any DP design.

---

## Technique 15: Minimum Deletions to Sort = n - LIS

### Problem Pattern

Given a sequence of n elements, find the minimum number of elements to remove so that the
remaining sequence is sorted (non-decreasing or strictly increasing, depending on the
problem).

### Key Insight

The elements we KEEP form a sorted subsequence. To minimize deletions, maximize the number
of kept elements. The longest sorted subsequence we can keep is exactly the Longest
Increasing Subsequence (LIS) --- strictly increasing or non-decreasing as required.

Therefore: minimum deletions = n - LIS length.

### Proof

Let L = LIS length. We can keep L elements (forming the LIS), so we delete n - L.

Can we do better (delete fewer than n - L)? That would mean keeping more than L elements in
sorted order, i.e., a sorted subsequence of length > L. But that contradicts the definition
of L as the LONGEST such subsequence.

Therefore n - L is both achievable and optimal. QED.

### Variants

- "Minimum deletions to make non-decreasing": use longest non-decreasing subsequence
  (use upper_bound instead of lower_bound in the O(n log n) algorithm).
- "Minimum deletions to make strictly increasing": use standard LIS with lower_bound.
- "Minimum deletions to sort array that can be sorted by removing elements from one end":
  different problem, LIS does not apply directly.

---

## Summary of When to Use Each Technique

| # | Technique | Use When |
|---|-----------|----------|
| 1 | Push DP | Transitions reach forward, not backward |
| 2 | String DP | Comparing/aligning two sequences |
| 3 | First-Violation DP | Counting with forbidden states, direct IE is exponential |
| 4 | Backward Inner Loop | 0/1 knapsack with 1D compression |
| 5 | Value-Based Knapsack | Capacity huge, total value small |
| 6 | Exchange + DP | Items unordered, DP needs an order |
| 7 | v=0 vs v>=1 | Unbounded/counting with usage loop |
| 8 | Binary Decomposition | Bounded knapsack, large multiplicities |
| 9 | Modulo + Sliding Window | Bounded knapsack, O(nW) regardless of k |
| 10 | Greedy Dominance | States can be pruned by dominance relation |
| 11 | LIS O(n log n) | Longest increasing subsequence |
| 12 | 2D LIS | Nesting / chaining with two keys |
| 13 | Sliding Window DP | Transition is min/max over a window |
| 14 | DP Lessons | General design principles |
| 15 | Min Deletions = n - LIS | Minimum removal to sort |

---

*End of Advanced DP Techniques Handbook.*
