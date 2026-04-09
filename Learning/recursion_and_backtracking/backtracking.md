# Recursion and Backtracking: A Rigorous Treatment

## Section 1: Recursion as Structural Induction

### The Correspondence

Every correct recursive algorithm is, implicitly, a proof by mathematical induction.
This is not a metaphor; it is a formal equivalence.

| Recursion                | Induction                                          |
|--------------------------|----------------------------------------------------|
| Base case (return value) | Base case of induction (P(0) or P(base) is true)   |
| Recursive call on smaller input | Inductive hypothesis (assume P(k) for all k < n) |
| Combining recursive results | Inductive step (prove P(n) using the hypothesis) |
| Termination (inputs shrink) | Well-ordering (every decreasing sequence in N terminates) |

**Formal statement**: Let f be a recursive function with the property that:
1. f(x) returns the correct answer for all base cases x
2. For non-base inputs x, f(x) makes recursive calls only on strictly smaller inputs
   (under some well-founded ordering), and correctly combines their results

Then f(x) is correct for all valid inputs x.

**Proof**: By strong induction on the size of x (under the well-founded ordering).
Base cases are given. For non-base x, all recursive calls are on smaller inputs,
so by the inductive hypothesis they return correct results. The combination step
is correct by assumption (2). Therefore f(x) is correct. QED.

### Pre-order vs Post-order Processing

**Pre-order** (top-down): Process the current node before recursing on children.

```
f(node):
    process(node)        // <-- before recursion
    for child in children(node):
        f(child)
```

**Post-order** (bottom-up): Process the current node after recursing on children.

```
f(node):
    for child in children(node):
        results.append(f(child))
    return combine(results)  // <-- after recursion
```

Post-order corresponds most directly to mathematical induction: you assume the answers
for all subproblems (children), then combine them to get the answer for the current
problem. This is why DP transitions and tree DP are naturally post-order.

Pre-order is used when the parent's state must be communicated downward (e.g., depth,
path from root, constraints inherited from ancestors).

### The Recursion Tree

Any recursive computation can be visualized as a tree:
- Each node represents one function call
- Children of a node are the recursive calls it makes
- Leaves are base cases
- The total work is the sum of work at all nodes

**Time complexity**: T(n) = (number of nodes) * (work per node), if work per node is
uniform. Otherwise, sum the work across all nodes.

---

## Section 2: The Include/Exclude Framework

### Generating All Subsets

**Problem**: Enumerate all subsets of {a[0], a[1], ..., a[n-1]}.

**Algorithm**: At each index i, make a binary choice: include a[i] or exclude a[i].

```cpp
void generate(int i, vector<int>& current) {
    if (i == n) {
        process(current);  // current is a complete subset
        return;
    }
    // Exclude a[i]
    generate(i + 1, current);
    // Include a[i]
    current.push_back(a[i]);
    generate(i + 1, current);
    current.pop_back();  // backtrack
}
```

**Theorem**: This generates all 2^n subsets of {a[0], ..., a[n-1]}, each exactly once.

**Proof by induction on n**:

*Base (n=0)*: The only subset of the empty set is the empty set. The algorithm calls
process({}) once. Correct.

*Inductive step*: Assume the algorithm correctly generates all 2^{n-1} subsets of
{a[1], ..., a[n-1]} (the subproblem after deciding on a[0]).

The first recursive call (exclude a[0]) generates all subsets of {a[1],...,a[n-1]}
that do not contain a[0]. By IH, there are 2^{n-1} of them.

The second recursive call (include a[0]) generates all subsets of {a[1],...,a[n-1]}
augmented with a[0]. By IH, there are 2^{n-1} of them.

These two families are disjoint (one contains a[0], the other does not) and their
union is all subsets of {a[0],...,a[n-1]}. Total: 2^{n-1} + 2^{n-1} = 2^n. QED.

**Complexity**: O(2^n) calls, each doing O(1) work (ignoring the cost of process()).
The recursion tree is a complete binary tree of depth n.

### Handling Duplicates

**Problem**: If the input contains duplicates, the above generates duplicate subsets.
For example, {1, 1}: include/exclude on position 0 and 1 generates {}, {1}, {1}, {1,1},
where the subset {1} appears twice.

**Solution**: Sort the input. When deciding to exclude a[i], skip all copies of a[i].

```cpp
void generate(int i, vector<int>& current) {
    if (i == n) {
        process(current);
        return;
    }
    // Include a[i]
    current.push_back(a[i]);
    generate(i + 1, current);
    current.pop_back();
    // Exclude a[i] -- skip all duplicates of a[i]
    int j = i + 1;
    while (j < n && a[j] == a[i]) j++;
    generate(j, current);
}
```

**Theorem**: After sorting, this generates each distinct multiset-subset exactly once.

**Proof sketch**: For a group of k identical elements with value v, the algorithm decides
how many copies of v to include (0, 1, 2, ..., or k). The "include" branch takes one
copy and recurses (allowing more copies). The "exclude" branch skips all copies of v,
ensuring we never reconsider v. Each choice of count (0 through k) is generated exactly
once.

More formally: let the sorted array have groups of sizes k_1, k_2, ..., k_g (where
group j consists of k_j identical elements). The number of distinct subsets is
the product (k_1 + 1)(k_2 + 1)...(k_g + 1). The algorithm generates exactly this
many subsets, as it independently chooses 0 to k_j copies from each group.

---

## Section 3: Permutation Generation

### Method 1: Swap-Based (Heap-style)

**Algorithm**: To generate all permutations of a[0..n-1]:

```cpp
void permute(int i) {
    if (i == n) {
        process(a);
        return;
    }
    for (int j = i; j < n; j++) {
        swap(a[i], a[j]);
        permute(i + 1);
        swap(a[i], a[j]);  // backtrack
    }
}
```

**Theorem**: This generates all n! permutations, each exactly once.

**Proof by induction on n**:

*Base (n=1)*: One permutation, generated by the single base-case call. Correct.

*Inductive step*: At position i=0, the loop places each of the n elements at position 0.
For each choice of element at position 0, the recursive call permute(1) generates all
permutations of the remaining n-1 elements in positions 1..n-1.

By the inductive hypothesis, permute(1) generates all (n-1)! permutations of the
remaining elements. Since we try each of n elements at position 0, and the resulting
permutations are distinct (different first elements, or same first element but
different sub-permutations from different swap histories):

Total permutations = n * (n-1)! = n!

**Distinctness**: If two calls place different elements at position 0, all resulting
permutations differ at position 0. If they place the same element (impossible in this
loop since j ranges over distinct indices), the sub-permutations would need to differ.
Since each j in [i, n) selects a distinct element for position i, all n! permutations
are distinct. QED.

### Method 2: Chosen-Array

**Algorithm**: Maintain a boolean array `chosen[0..n-1]` tracking which elements are
already placed. At each position, try all unchosen elements.

```cpp
void permute(int pos, vector<int>& perm) {
    if (pos == n) {
        process(perm);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!chosen[i]) {
            chosen[i] = true;
            perm.push_back(a[i]);
            permute(pos + 1, perm);
            perm.pop_back();
            chosen[i] = false;
        }
    }
}
```

**Complexity comparison**:
- Swap-based: O(n!) calls, O(1) work per non-leaf call (just a swap). Total: O(n * n!).
- Chosen-array: O(n!) calls, O(n) work per call (scanning chosen[]). Total: O(n * n!).

Both are O(n * n!) total, but the swap-based method has better cache behavior.

### Generating Permutations with Duplicates

Sort the array. In the chosen-array method, add the constraint: among identical elements,
only choose them in left-to-right order. Concretely:

```cpp
if (i > 0 && a[i] == a[i-1] && !chosen[i-1]) continue;
```

**Why this works**: If we have k copies of value v, the constraint forces us to use them
in the fixed order (1st copy, then 2nd, ...). This eliminates the k! internal orderings
of identical elements, generating n! / (k_1! * k_2! * ... * k_g!) distinct permutations.

---

## Section 4: Backtracking with Pruning

### General Framework

**Backtracking** = recursion + pruning. The idea:

1. Build the solution incrementally (one decision at a time)
2. At each step, check if the partial solution can possibly lead to a valid complete solution
3. If not, **prune**: abandon this branch and backtrack

**Formal**: Let S be the search space (all possible complete assignments). Backtracking
explores a tree where:
- Internal nodes are partial assignments
- Leaves are complete assignments
- Pruning removes subtrees rooted at partial assignments that violate constraints

Without pruning: enumerate all of S (brute force).
With pruning: enumerate only the "feasible" branches, potentially much smaller.

### N-Queens: A Case Study

**Problem**: Place n queens on an n x n chessboard such that no two queens attack each
other (same row, column, or diagonal).

**Observation**: Since no two queens share a row, we can place exactly one queen per row.
The problem reduces to: for each row i (0 to n-1), choose a column c_i such that no
two queens share a column or diagonal.

**Naive complexity**: n^n (any column for any row).
**With one-per-row**: n! (permutations of columns).
**With pruning**: Much less in practice (exact count depends on n).

**Implementation with O(1) conflict detection**:

Track three boolean arrays:
- `col[c]` = true if column c is occupied
- `diag1[r + c]` = true if the diagonal (r + c = constant) is occupied
- `diag2[r - c + n - 1]` = true if the anti-diagonal (r - c = constant) is occupied

The index shift `+ n - 1` for diag2 ensures non-negative indices (r - c ranges from
-(n-1) to n-1).

```cpp
int n, count = 0;
bool col[MAXN], diag1[2*MAXN], diag2[2*MAXN];

void solve(int row) {
    if (row == n) { count++; return; }
    for (int c = 0; c < n; c++) {
        if (col[c] || diag1[row + c] || diag2[row - c + n - 1])
            continue;  // prune
        col[c] = diag1[row + c] = diag2[row - c + n - 1] = true;
        solve(row + 1);
        col[c] = diag1[row + c] = diag2[row - c + n - 1] = false;  // backtrack
    }
}
```

**Why diagonals are indexed by r+c and r-c**:

*Theorem*: Two cells (r1, c1) and (r2, c2) are on the same diagonal iff r1+c1 = r2+c2
or r1-c1 = r2-c2.

*Proof*: Diagonals going down-right have slope +1: r = c + k, so r - c = k (constant).
Diagonals going down-left have slope -1: r = -c + k, so r + c = k (constant). QED.

### Pruning Power

The number of valid N-Queens configurations for small n:

| n | Solutions | Nodes explored (with pruning) | n! (without pruning) |
|---|-----------|-------------------------------|----------------------|
| 8 | 92        | ~15,000                       | 40,320               |
| 12| 14,200    | ~1,000,000                    | 479,001,600          |

Pruning reduces the search space by orders of magnitude.

---

## Section 5: From Recursion to Dynamic Programming

### The Overlapping Subproblems Criterion

**Definition**: A recursive algorithm has **overlapping subproblems** if the same
subproblem (same function arguments) is solved multiple times during the computation.

**Example**: Fibonacci. f(n) = f(n-1) + f(n-2). The call tree for f(5):

```
f(5) -> f(4) -> f(3) -> f(2) -> f(1)
                     |          -> f(0)
                     -> f(1)
              -> f(2) -> f(1)
                      -> f(0)
       -> f(3) -> f(2) -> f(1)
                       -> f(0)
              -> f(1)
```

f(2) is computed 3 times, f(3) is computed 2 times. Without memoization: O(2^n).
With memoization: O(n) (each subproblem computed once).

### Memoization: Top-Down DP

**Recipe**:
1. Write the recursive solution
2. Identify the state: the minimal set of parameters that uniquely determines the answer
3. Store computed results in a table (map or array) indexed by state
4. Before computing, check if the state is already in the table

### Example: 0/1 Knapsack

**Problem**: n items with weights w_i and values v_i. Knapsack capacity W.
Maximize total value subject to total weight <= W.

**Recursive formulation**:

```
solve(i, rem) = maximum value achievable using items i..n-1 with remaining capacity rem

Base: solve(n, rem) = 0          (no items left)
Transition:
  solve(i, rem) = max(
      solve(i+1, rem),            // skip item i
      solve(i+1, rem - w[i]) + v[i]  // take item i (if rem >= w[i])
  )
```

**Without memoization**: The recursion tree has up to 2^n leaves (each item is taken or
skipped). Time: O(2^n).

**With memoization**: The state space is {(i, rem) : 0 <= i <= n, 0 <= rem <= W}.
Size: O(n * W). Each state is computed once, in O(1) time.
Total time: **O(n * W)** (pseudo-polynomial).

**Proof of correctness by induction on i (from n down to 0)**:

*Base (i = n)*: No items remain. Maximum value is 0. Correct.

*Inductive step*: Assume solve(i+1, *) is correct for all capacities.
For solve(i, rem), there are two cases:
- Item i is not taken: the optimal value from items i+1..n-1 with capacity rem is
  solve(i+1, rem), which is correct by IH.
- Item i is taken (if rem >= w[i]): we gain v[i] and the remaining capacity is
  rem - w[i]. The optimal value from items i+1..n-1 is solve(i+1, rem - w[i]), correct by IH.

The maximum of these two cases is the optimal value for solve(i, rem). QED.

### Recognizing When to Memoize vs When Greedy Suffices

| Property                  | Memoization / DP         | Greedy                    |
|---------------------------|--------------------------|---------------------------|
| Overlapping subproblems   | Yes (many repeated calls)| No (each subproblem once) |
| Optimal substructure      | Yes                      | Yes                       |
| Greedy choice property    | Not necessarily          | Yes (must prove)          |
| Need to try all options   | Yes (max/min over choices)| No (one choice suffices) |

**Rule of thumb**: If the recurrence takes a max or min over multiple choices and the
greedy choice property is not provable, use DP.

---

## Section 6: Backtracking Applications and Patterns

### Generating Combinations (n choose k)

**Problem**: Generate all k-element subsets of {0, 1, ..., n-1}.

```cpp
void combine(int start, int remaining, vector<int>& current) {
    if (remaining == 0) {
        process(current);
        return;
    }
    // Pruning: need 'remaining' more elements from [start, n)
    // Only proceed if n - start >= remaining
    for (int i = start; i <= n - remaining; i++) {
        current.push_back(i);
        combine(i + 1, remaining - 1, current);
        current.pop_back();
    }
}
```

**The bound `i <= n - remaining`** is crucial pruning: if fewer than `remaining` elements
are available from position i onward, no valid combination can be completed. This avoids
exploring dead-end branches.

**Number of nodes in the pruned tree**: O(C(n, k)), which can be exponentially smaller
than the unpruned tree.

### Sudoku Solver

Backtracking with constraint propagation:
1. Find the empty cell with the fewest candidates (MRV heuristic: Minimum Remaining Values)
2. Try each candidate; for each, propagate constraints (eliminate from peers)
3. If a contradiction arises (some cell has zero candidates), backtrack

**Why MRV helps**: Choosing the most constrained cell first maximizes the probability of
early pruning. A cell with 2 candidates branches into 2 subtrees; a cell with 9 candidates
branches into 9. Choosing the cell with 2 candidates first prunes 7/9 of the search space
at the first level.

### The Backtracking Template

```cpp
void backtrack(State& state, int depth) {
    if (is_solution(state)) {
        record_solution(state);
        return;
    }
    for (Choice c : candidates(state, depth)) {
        if (is_valid(state, c)) {       // pruning
            apply(state, c);            // make choice
            backtrack(state, depth + 1);
            undo(state, c);             // undo choice (backtrack)
        }
    }
}
```

The correctness of this template relies on:
1. **Completeness**: `candidates()` generates all possible choices at this depth
2. **Soundness**: `is_valid()` only prunes choices that provably cannot lead to a solution
3. **Restoration**: `undo()` perfectly restores the state (no side effects leak)

If these three properties hold, the algorithm explores exactly the set of all valid
complete assignments, generating each exactly once.
