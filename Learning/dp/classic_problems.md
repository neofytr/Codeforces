# A Gallery of DP Recurrences

A catalog not of problems but of **recurrence types**. Each entry gives the precise recurrence,
a correctness argument, complexity analysis, and the canonical code pattern. Master these
recurrences and you will recognize them instantly in new problems.

---

## Type 1: Linear DP

### 1.1 Definition

The state is a single integer i in {0, 1, ..., n}, and f(i) depends on f(i-1), f(i-2), ...,
f(i-k) for some fixed window k.

### 1.2 General Recurrence

    f(i) = AGG_{j=1}^{k} h(f(i-j), i, j)

where AGG is summation (counting) or min/max (optimization), and h is the combining function.

### 1.3 Canonical Examples

**Fibonacci / Staircase climbing:**
    f(i) = f(i-1) + f(i-2)
    Base: f(0) = 1, f(1) = 1

**Dice combinations (sum to n using dice faces 1..6):**
    f(i) = SUM_{j=1}^{6} f(i-j)       for i >= 1
    Base: f(0) = 1; f(i) = 0 for i < 0

**Cut ribbon (maximize pieces of lengths a, b, c from ribbon of length n):**
    f(i) = max(f(i-a), f(i-b), f(i-c)) + 1
    Base: f(0) = 0; f(i) = -infinity for i < 0
    Answer: f(n) if f(n) >= 0, else impossible.

### 1.4 Correctness Proof (Dice Combinations)

**Claim.** f(i) counts the number of ordered sequences of dice rolls summing to i.

*Proof by strong induction on i.*

Base: f(0) = 1. There is exactly one sequence summing to 0: the empty sequence. Correct.

Inductive step: Assume f(j) is correct for all j < i. Any sequence summing to i has a last
roll, say j in {1,...,6}. Removing this last roll gives a sequence summing to i - j. The
number of such sequences is f(i-j). Since the last roll can be any of {1,...,6}, and these
cases are disjoint and exhaustive:

    f(i) = SUM_{j=1}^{6} f(i-j)

By the inductive hypothesis, each f(i-j) is correct. Hence f(i) is correct. QED.

### 1.5 Complexity

Time: O(nk) where k is the window size. Space: O(n), reducible to O(k) via rolling array.

### 1.6 Code Pattern

```cpp
vector<long long> dp(n + 1, 0);
dp[0] = 1;  // or appropriate base case
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k && i - j >= 0; j++) {
        dp[i] = (dp[i] + dp[i - j]) % MOD;  // counting
        // dp[i] = max(dp[i], dp[i-j] + val); // optimization
    }
}
```

---

## Type 2: The Knapsack Family

The state is a capacity w (or more generally, a resource budget), and we process items
one by one, deciding how many copies of each to include.

### 2.1 0/1 Knapsack

**Items:** n items, each with weight w_i and value v_i. Each used at most once.
**State:** dp[w] = maximum value achievable with capacity w.
**Recurrence (after space optimization):**

    For each item i = 1, ..., n:
        For w = W down to w_i:
            dp[w] = max(dp[w], dp[w - w_i] + v_i)

**Base:** dp[0] = 0, dp[w] = 0 for all w (or -infinity if exact capacity is required).

**Correctness.** See fundamentals.md Section 4.2 for the proof that backward iteration
ensures each item is used at most once.

**Complexity.** O(nW) time, O(W) space.

### 2.2 Unbounded Knapsack

**Difference:** Each item can be used unlimited times.
**Recurrence:**

    For each item i = 1, ..., n:
        For w = w_i to W:
            dp[w] = max(dp[w], dp[w - w_i] + v_i)

**Alternatively (single-pass, no item loop):**

    For w = 1 to W:
        For each item i:
            if w >= w_i: dp[w] = max(dp[w], dp[w - w_i] + v_i)

**Correctness.** Forward iteration allows dp[w - w_i] to already include item i, effectively
permitting unlimited copies.

**Complexity.** O(nW) time, O(W) space.

### 2.3 Bounded Knapsack

**Items:** n items, item i available in at most k_i copies.
**Naive approach:** Treat k_i copies of item i as separate items. O(W * SUM k_i) --- too slow
if k_i is large.

**Binary lifting trick:** Decompose k_i copies into groups of sizes 1, 2, 4, ..., 2^t, and
a remainder k_i - (2^{t+1} - 1). Each group is treated as a single "super-item". Now we
have O(SUM log k_i) items, each used at most once: apply 0/1 knapsack.

**Claim.** Any count from 0 to k_i can be represented as a subset-sum of these groups.

*Proof.* The groups {1, 2, 4, ..., 2^t, r} where r = k_i - (2^{t+1} - 1) can represent
any integer from 0 to k_i. The binary groups {1, 2, ..., 2^t} represent all integers
from 0 to 2^{t+1} - 1. Adding any subset of these to r (or not using r) extends the range
to [0, k_i]. QED.

**Complexity.** O(W * SUM log k_i) time.

### 2.4 Subset Sum via Bitset

**Problem.** Given items with weights w_1, ..., w_n, determine which total weights are
achievable using each item at most once.

**State:** A bitset B of size W+1, where B[w] = 1 iff weight w is achievable.
**Transition:**

    For each item i:
        B = B | (B << w_i)

**Correctness.** B << w_i shifts all achievable weights by w_i. The OR accumulates both
"don't use item i" (old B) and "use item i" (shifted B).

**Complexity.** O(nW/64) time using 64-bit words. The factor of 1/64 from bitwise parallelism
is significant in practice: W = 10^6 and n = 100 gives ~1.5 * 10^6 word operations.

**Code pattern:**

```cpp
bitset<MAXW + 1> dp;
dp[0] = 1;
for (int i = 0; i < n; i++) {
    dp |= (dp << w[i]);
}
// dp[w] == 1 iff weight w is achievable
```

---

## Type 3: Grid DP

### 3.1 Definition

State space is a 2D grid {0,...,m-1} x {0,...,n-1}. Transitions go right and/or down
(or more generally, from cells with smaller indices to larger).

### 3.2 Recurrence

**Path counting:**
    f(i, j) = f(i-1, j) + f(i, j-1)
    Base: f(0, 0) = 1

**Minimum cost path:**
    f(i, j) = grid[i][j] + min(f(i-1, j), f(i, j-1))
    Base: f(0, 0) = grid[0][0]

**With obstacles:** If cell (i,j) is blocked, f(i,j) = 0 (counting) or infinity (min cost).

### 3.3 Correctness

*Proof (path counting).* f(i,j) = number of paths from (0,0) to (i,j) using only right and
down moves. Any such path arrives at (i,j) from either (i-1,j) (down move) or (i,j-1) (right
move). These cases are disjoint. By induction, f(i-1,j) and f(i,j-1) are correct. QED.

### 3.4 Complexity

Time: O(mn). Space: O(mn), reducible to O(n) with rolling array.

### 3.5 Code Pattern

```cpp
// Counting paths, O(n) space
vector<long long> dp(n, 0);
dp[0] = 1;
for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (obstacle[i][j]) { dp[j] = 0; continue; }
        if (j > 0) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        // dp[j] already holds f(i-1, j) from previous row iteration
    }
}
```

---

## Type 4: Interval DP

### 4.1 Definition

State: a contiguous interval [l, r] of the input. Transition: split the interval at some
point k and combine solutions for [l, k] and [k+1, r].

### 4.2 General Recurrence

    f(l, r) = OPT_{l <= k < r} [f(l, k) + f(k+1, r) + cost(l, r)]

    Base: f(i, i) = base_value (single element)

### 4.3 Canonical Example: Matrix Chain Multiplication

Given matrices M_1, ..., M_n with dimensions p_0 x p_1, p_1 x p_2, ..., p_{n-1} x p_n,
find the parenthesization minimizing total scalar multiplications.

    f(l, r) = min_{l <= k < r} [f(l, k) + f(k+1, r) + p_{l-1} * p_k * p_r]
    Base: f(i, i) = 0

### 4.4 Correctness

*Proof.* Any parenthesization of M_l * ... * M_r has an outermost multiplication, splitting
the product at some k into (M_l * ... * M_k) * (M_{k+1} * ... * M_r). The cost of this
outermost multiplication is p_{l-1} * p_k * p_r. By optimal substructure, both sub-products
must be optimally parenthesized. The recurrence tries all possible split points and takes
the minimum. QED.

### 4.5 Computation Order

Process intervals by increasing length: len = 1, 2, ..., n. For each length, iterate over
all starting points l, with r = l + len - 1.

### 4.6 Complexity

States: O(n^2). Transition: O(n) per state. Total: O(n^3).
With Knuth's optimization (if cost satisfies quadrangle inequality): O(n^2).

### 4.7 Code Pattern

```cpp
// dp[l][r] = min cost to process interval [l, r]
for (int i = 0; i < n; i++) dp[i][i] = 0;  // base case

for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        dp[l][r] = LLONG_MAX;
        for (int k = l; k < r; k++) {
            dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + cost(l, r));
        }
    }
}
```

---

## Type 5: State Machine DP

### 5.1 Definition

The state includes a "mode" or "phase" from a finite set Q = {q_1, ..., q_m}. At each step,
the system may transition between modes according to transition rules.

### 5.2 General Recurrence

    f(i, q) = OPT_{q' : transition (q', q) is valid at step i} [f(i-1, q') + cost(i, q)]

Here i indexes the step (day, position, etc.) and q is the current mode.

### 5.3 Canonical Example: Vacations

**Problem.** n days, each day has available activities (subsets of {rest, contest, gym}).
Cannot do the same activity on consecutive days. Maximize days with activities.

**States:** (day i, last activity q) where q in {rest, contest, gym} = {0, 1, 2}.

**Recurrence:**

    f(i, q) = max_{q' != q, q' available on day i} [f(i-1, q')] + (q != rest ? 1 : 0)

Actually, more precisely:

    f(i, q) = (1 if q is an activity, 0 if rest) + max_{q' != q} f(i-1, q')

where we only consider q if it is available on day i (or q = rest, always available).

### 5.4 Stock Trading as State Machine

**Problem.** Buy/sell stock with at most K transactions.

**States:** (day i, transactions used j, holding/not holding) = (i, j, {0, 1}).

**Recurrence:**

    f(i, j, 0) = max(f(i-1, j, 0), f(i-1, j, 1) + price[i])    // hold or sell
    f(i, j, 1) = max(f(i-1, j, 1), f(i-1, j-1, 0) - price[i])  // hold or buy

### 5.5 Correctness

*Proof template.* The state machine has no "memory" beyond the current mode q. The recurrence
considers all valid transitions into (i, q) and takes the optimum. By induction, all
predecessors are correct, hence f(i, q) is correct. The finite state set Q ensures the
state space is O(n * |Q|). QED.

### 5.6 Complexity

Time: O(n * |Q|^2) or O(n * |Q|) if transitions are sparse. Space: O(|Q|) with rolling.

---

## Type 6: Digit DP

### 6.1 Problem Class

Count integers in [0, N] (or [L, R]) satisfying some property P that depends on the digits.

### 6.2 State

    (pos, tight, info)

where:
  - pos: current digit position (from most significant to least significant)
  - tight: boolean indicating whether the digits chosen so far exactly match the prefix of N
    (if tight, the next digit is constrained to be <= N's digit at pos; if not tight, it
    can be 0-9 freely)
  - info: accumulated information about digits chosen so far (digit sum, remainder mod k,
    set of digits used, etc.)

### 6.3 General Recurrence

    f(pos, tight, info) = SUM_{d=0}^{limit} f(pos+1, tight', info')

where:
  - limit = digit[pos] if tight, else 9
  - tight' = tight AND (d == digit[pos])
  - info' = update(info, d)

**Base case:** f(n_digits, *, info) = 1 if info satisfies P, else 0.

### 6.4 Correctness

*Proof.* Each path from root (pos=0) to leaf (pos=n_digits) in the recursion tree corresponds
to exactly one integer. The tight flag ensures we never exceed N. The info field tracks exactly
the information needed to evaluate P. By construction, the recursion generates each integer
in [0, N] exactly once and checks P at the leaf. QED.

### 6.5 Range Queries via Subtraction

To count integers in [L, R] with property P:

    count(L, R) = count(0, R) - count(0, L-1)

This reduces the two-endpoint problem to two single-endpoint problems.

### 6.6 Complexity

Time: O(n_digits * 10 * |info states|). Often the bottleneck is the info state space.

### 6.7 Code Pattern

```cpp
// Memoization: dp[pos][tight][info]
int digit[MAXD]; // digits of N, most significant first
int n_digits;

map<tuple<int,bool,int>, long long> memo;

long long solve(int pos, bool tight, int info) {
    if (pos == n_digits) return satisfies(info) ? 1 : 0;
    auto key = make_tuple(pos, tight, info);
    if (memo.count(key)) return memo[key];
    
    int limit = tight ? digit[pos] : 9;
    long long result = 0;
    for (int d = 0; d <= limit; d++) {
        result += solve(pos + 1, tight && (d == limit), update(info, d));
    }
    return memo[key] = result;
}
```

---

## Type 7: Tree DP

### 7.1 Basic Subtree DP

**State:** (node v), sometimes (node v, additional info k).
**Recurrence:**

    f(v) = COMBINE_{u in children(v)} (f(u)) + local_cost(v)

where COMBINE depends on the problem (sum, product, max, etc.).

### 7.2 Canonical Example: Maximum Independent Set on Trees

**Problem.** Select a subset of nodes with no two adjacent, maximizing total weight.

**States:** (v, included?) for each node v.

**Recurrence:**

    f(v, 0) = SUM_{u in children(v)} max(f(u, 0), f(u, 1))    // v excluded
    f(v, 1) = weight(v) + SUM_{u in children(v)} f(u, 0)       // v included

**Base (leaf v):** f(v, 0) = 0, f(v, 1) = weight(v).
**Answer:** max(f(root, 0), f(root, 1)).

### 7.3 Correctness

*Proof.* If v is excluded, each child u can independently be included or excluded --- we take
the better option. If v is included, no child can be included (adjacency constraint), so we
must take f(u, 0) for each child. By induction on tree height, all children's values are
correct, hence f(v, *) is correct. QED.

### 7.4 Tree Diameter and Related

**Problem.** Find the longest path in a tree.

**Recurrence.** At each node v, maintain depth[v] = length of longest path starting at v and
going into v's subtree.

    depth[v] = max_{u in children(v)} (depth[u] + 1)

The diameter through v is the sum of the two largest depth values among v's children (the
longest downward path through v uses the two deepest subtrees).

    diameter = max_v (top_two_depths(v))

**Complexity.** O(n).

### 7.5 Rerooting Code Pattern

```cpp
// Pass 1: compute dp_down[v]
void dfs_down(int v, int p) {
    dp_down[v] = base;
    for (int u : adj[v]) {
        if (u == p) continue;
        dfs_down(u, v);
        dp_down[v] = combine(dp_down[v], dp_down[u]);
    }
}

// Pass 2: compute dp_up[v] and full answer
void dfs_up(int v, int p) {
    // answer[v] = combine(dp_down[v], dp_up[v])
    // For each child u of v, compute dp_up[u] from dp_up[v] and siblings' dp_down
    
    // Precompute prefix/suffix of children's dp_down values
    vector<int> children;
    for (int u : adj[v]) if (u != p) children.push_back(u);
    
    int k = children.size();
    vector<Val> prefix(k+1, identity), suffix(k+1, identity);
    for (int i = 0; i < k; i++)
        prefix[i+1] = combine(prefix[i], dp_down[children[i]]);
    for (int i = k-1; i >= 0; i--)
        suffix[i] = combine(suffix[i+1], dp_down[children[i]]);
    
    for (int i = 0; i < k; i++) {
        int u = children[i];
        Val siblings = combine(prefix[i], suffix[i+1]);
        dp_up[u] = combine(dp_up[v], siblings);
        dfs_up(u, v);
    }
}
```

**Complexity.** O(n) for both passes.

---

## Type 8: Longest Increasing Subsequence (LIS)

### 8.1 The O(n^2) Recurrence

**State:** dp[i] = length of LIS ending at index i.

**Recurrence:**

    dp[i] = 1 + max({dp[j] : j < i, a[j] < a[i]} union {0})

**Base:** dp[i] = 1 for all i (each element alone is a subsequence of length 1 --- but more
precisely, the max over the empty set is 0, so dp[i] = 1).

**Answer:** max_{i} dp[i].

### 8.2 Correctness

*Proof.* The LIS ending at position i must have a[i] as its last element. The penultimate
element (if any) is some a[j] with j < i and a[j] < a[i]. The length of the LIS ending at j
is dp[j]. Trying all valid j and taking the max gives the longest possible. The +1 accounts
for a[i] itself. QED.

### 8.3 The O(n log n) Algorithm (Patience Sorting)

Maintain an array tails[] where tails[l] = smallest possible last element of an increasing
subsequence of length l+1.

**Key invariant:** tails[] is always strictly increasing.

**Algorithm:**
```
tails = empty
for i = 0 to n-1:
    if a[i] > tails.back() (or tails is empty):
        tails.push_back(a[i])    // extend longest subsequence
    else:
        j = lower_bound(tails, a[i])   // binary search
        tails[j] = a[i]                // replace to keep tails minimal
LIS length = tails.size()
```

### 8.4 Correctness of the O(n log n) Algorithm

**Theorem.** After processing a[0..i], tails[l] is the smallest value v such that there
exists an increasing subsequence of length l+1 in a[0..i] ending with v.

*Proof by induction on i.*

Base: After processing a[0], tails = [a[0]]. An IS of length 1 ending with a[0] exists, and
it is the only option. Correct.

Inductive step: Consider a[i].

Case 1: a[i] > tails.back(). Then a[i] extends the longest IS found so far. We append a[i].
For all previous lengths, the minimum tails are unchanged (a[i] is not smaller). Correct.

Case 2: a[i] <= tails.back(). Let j = first index where tails[j] >= a[i]. We set tails[j]
= a[i]. This means: there exists an IS of length j+1 ending with a[i] (take the IS of length
j ending with tails[j-1] < a[i], append a[i]). And a[i] <= tails[j] (old), so tails[j] does
not increase. For all other lengths, tails are unchanged. Correct. QED.

**Complexity.** O(n log n) time (binary search per element), O(n) space.

### 8.5 Counting LIS

**Problem.** Count the number of longest increasing subsequences.

**Approach.** Maintain cnt[i] alongside dp[i]:

    dp[i] = length of LIS ending at i
    cnt[i] = number of LIS of that length ending at i

**Recurrence:**

    For each j < i with a[j] < a[i]:
        if dp[j] + 1 > dp[i]:
            dp[i] = dp[j] + 1
            cnt[i] = cnt[j]
        elif dp[j] + 1 == dp[i]:
            cnt[i] += cnt[j]

**Base:** dp[i] = 1, cnt[i] = 1 for all i.
**Answer:** SUM_{i : dp[i] == LIS_length} cnt[i].
**Complexity.** O(n^2). Can be reduced to O(n log n) with BIT/segment tree.

### 8.6 Code Pattern (O(n log n) LIS)

```cpp
vector<int> tails;
for (int i = 0; i < n; i++) {
    auto it = lower_bound(tails.begin(), tails.end(), a[i]);
    if (it == tails.end()) {
        tails.push_back(a[i]);
    } else {
        *it = a[i];
    }
}
int lis_length = tails.size();
```

For strictly increasing: use lower_bound. For non-decreasing: use upper_bound.

---

## Type 9: Bitmask DP Recurrences

### 9.1 Travelling Salesman Problem (TSP)

**State:** (mask, v) where mask is the set of visited cities and v is the current city.

**Recurrence:**

    f(mask, v) = min_{u : u in mask, u != v, (mask ^ (1<<v), u) is valid} [f(mask ^ (1<<v), u) + dist(u, v)]

**Base:** f(1 << start, start) = 0.
**Answer:** min_v [f((1<<n)-1, v) + dist(v, start)].
**Complexity:** O(2^n * n^2).

### 9.2 Assignment Problem (Hungarian via Bitmask)

**Problem.** n workers, n jobs. cost[i][j] = cost of assigning worker i to job j. Minimize
total cost, one job per worker.

**State:** dp[mask] = minimum cost of assigning jobs in mask to the first popcount(mask)
workers.

**Recurrence:**

    Let i = popcount(mask)  // which worker we're assigning
    dp[mask] = min_{j in mask} [dp[mask ^ (1<<j)] + cost[i-1][j]]

**Base:** dp[0] = 0.
**Answer:** dp[(1<<n)-1].
**Complexity:** O(2^n * n).

### 9.3 Correctness (Assignment Problem)

*Proof.* Worker assignment proceeds in order: worker 0, worker 1, ..., worker n-1. When
mask has k bits set, workers 0..k-1 have been assigned to the jobs indicated by the set bits
of mask. Worker k is assigned next by trying all jobs in mask's complement. The minimum over
all valid assignments to worker k gives dp[mask]. By induction on popcount(mask), the
recurrence is correct. QED.

---

## Type 10: Miscellaneous Important Recurrences

### 10.1 Edit Distance (Levenshtein)

**State:** (i, j) = first i characters of string A, first j characters of string B.

**Recurrence:**

    f(i, j) = f(i-1, j-1)                          if A[i] == B[j]
    f(i, j) = 1 + min(f(i-1,j), f(i,j-1), f(i-1,j-1))  otherwise

where f(i-1,j) = delete, f(i,j-1) = insert, f(i-1,j-1) = replace.

**Base:** f(i,0) = i, f(0,j) = j.
**Complexity:** O(nm) time, O(min(n,m)) space.

### 10.2 Longest Common Subsequence (LCS)

**Recurrence:**

    f(i, j) = f(i-1, j-1) + 1                  if A[i] == B[j]
    f(i, j) = max(f(i-1, j), f(i, j-1))        otherwise

**Base:** f(i, 0) = f(0, j) = 0.
**Complexity:** O(nm) time, O(min(n,m)) space.

### 10.3 Partition DP (Divide Sequence into Groups)

**Problem.** Partition a[1..n] into at most K contiguous groups, minimizing some cost function.

**State:** dp[k][i] = optimal cost of partitioning a[1..i] into at most k groups.

**Recurrence:**

    dp[k][i] = min_{0 <= j < i} [dp[k-1][j] + cost(j+1, i)]

**Base:** dp[0][0] = 0; dp[0][i] = infinity for i > 0.
**Answer:** dp[K][n].
**Complexity:** O(Kn^2) naive. O(Kn log n) with divide-and-conquer optimization (when
opt is monotone). O(Kn) with SMAWK or Knuth when applicable.

### 10.4 Profile DP (Broken Profile)

**Problem.** Tile an m x n grid with dominoes (or other shapes).

**State:** (column j, profile mask) where mask represents the "ragged edge" --- which cells in
column j are already filled by dominoes placed in column j-1.

**Recurrence:** Transition from one column to the next, trying all valid placements of
dominoes that complete the current column and possibly extend into the next.

**Complexity:** O(n * 2^m * transitions per state). Feasible when m is small (m <= 15-20).

### 10.5 Probability/Expected Value DP

**Structure.** Same as counting/optimization DP but the value function represents a
probability or expected value.

**Recurrence template:**

    E[s] = SUM_{transitions t} P(t | s) * (cost(t) + E[next(s, t)])

**Key difference.** Transitions are weighted by probabilities, and we take the weighted sum
rather than min/max. If we also choose actions, it becomes:

    E[s] = OPT_{a in A(s)} SUM_{outcomes o} P(o | s, a) * (cost(s, a, o) + E[next(s, a, o)])

---

## Summary: Recurrence Recognition Guide

| If you see...                      | Think...              | Key recurrence form                      |
|------------------------------------|-----------------------|------------------------------------------|
| "ways to reach sum/state"          | Linear/Knapsack DP    | f(i) = SUM f(i-c_j) or f(w) += f(w-w_i) |
| "min cost path on grid"            | Grid DP               | f(i,j) = grid[i][j] + min(above, left)   |
| "split array/string optimally"     | Interval DP           | f(l,r) = opt_k [f(l,k) + f(k+1,r)]      |
| "state changes with constraints"   | State Machine DP      | f(i,q) = opt_{q'} f(i-1,q') + cost       |
| "count numbers with digit prop."   | Digit DP              | f(pos, tight, info) = SUM_d f(...)        |
| "optimal on tree structure"        | Tree DP               | f(v) = combine children + local           |
| "longest increasing subsequence"   | LIS                   | Binary search on tails array              |
| "subset of n<=20 items"            | Bitmask DP            | f(mask) = opt f(mask') + cost             |
| "partition into K groups"          | Partition DP          | f(k,i) = opt_j f(k-1,j) + cost(j+1,i)   |
| "match/align two sequences"        | Edit Distance/LCS     | f(i,j) = f(i-1,j-1) + ... or max/min     |

---

## Closing Remark: The Meta-Theorem of DP

**Theorem (Informal).** If a combinatorial optimization or counting problem can be decomposed
into subproblems such that (1) the subproblems overlap and (2) optimal (or correct) solutions
to subproblems compose into optimal (or correct) solutions to larger problems, then dynamic
programming solves the problem in time proportional to |states| * |transitions per state|.

The art of DP is not in the algorithm (which is always "fill a table using a recurrence").
The art is in the STATE DESIGN: finding the minimal sufficient statistic that makes the
recurrence correct. Every problem in this gallery is, at its core, a different answer to the
question: *what do I need to remember about the past to make optimal decisions about the future?*
