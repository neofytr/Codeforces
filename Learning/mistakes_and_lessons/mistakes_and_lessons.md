# Failure Modes and Their Fixes

A systematic classification of bugs in competitive programming, organized by
the mathematical or logical reason each is wrong. Learn the *category* of
mistake, not just the individual instance.

---

## Category 1: Arithmetic Pitfalls

### 1.1 Integer Overflow

**The bug.** Two `int` values multiplied, or a sum of 10^5 values each up to
10^9, overflows 32-bit signed integer range [-2^31, 2^31 - 1] ~ [-2.1e9, 2.1e9].

**Why it is wrong.** C++ signed integer overflow is *undefined behavior*. The
compiler is free to do anything — it may silently wrap, optimize away your
overflow check, or produce garbage.

**The fix.** Use `long long` everywhere in CP. The standard idiom:

```cpp
#define int long long
```

placed before `main` (which you declare as `int32_t main()`). This redefines
`int` to 64-bit, covering up to ~9.2 * 10^18.

**The cost.** 2x memory per integer, negligible speed difference. Almost always
worth it in competition.

**Remaining danger.** Even `long long` overflows when multiplying two values
near 10^18. When doing modular multiplication with large moduli, use
`__int128` or binary multiplication:

```cpp
long long mulmod(long long a, long long b, long long m) {
    return (__int128)a * b % m;
}
```

### 1.2 Modular Arithmetic: Subtraction

**The bug.** `(a - b) % m` in C++ can be negative.

**Why it is wrong.** The C++ standard defines `%` so that `(a/b)*b + a%b == a`,
which means `a % b` has the sign of `a`. For example, `(-3) % 5 == -3`, not 2.
Mathematically, we want the result in [0, m-1].

**The fix.**

```cpp
((a - b) % m + m) % m
```

Or define a utility:

```cpp
int mod(int a, int m) { return ((a % m) + m) % m; }
```

### 1.3 Modular Arithmetic: Division

**The bug.** `(a / b) % m` does NOT equal `(a % m) * modular_inverse(b, m) % m`
computed naively as `(a % m) / (b % m)`.

**Why it is wrong.** Division is not defined in modular arithmetic. You must
multiply by the modular inverse: b^{-1} mod m, which exists if and only if
gcd(b, m) = 1.

**The fix.** Use Fermat's little theorem when m is prime:
    b^{-1} = b^{m-2} mod m
computed via binary exponentiation.

Or use extended GCD for general m (see templates).

### 1.4 Floating Point Comparison

**The bug.** Comparing `double` values with `==`.

**Why it is wrong.** Floating point arithmetic is not exact. 0.1 + 0.2 != 0.3
in IEEE 754. Accumulated rounding errors make `==` unreliable.

**The fix.**
- Use integer arithmetic whenever possible (multiply both sides by denominators).
- If floats are unavoidable, compare with epsilon: `|a - b| < 1e-9`.
- For binary search on doubles, iterate a fixed number of times (e.g., 100)
  rather than checking convergence.

### 1.5 Integer Division Truncation

**The bug.** `a / b` in C++ truncates toward zero, not toward negative infinity.
So `-7 / 2 == -3`, not `-4`.

**Why it is wrong.** Mathematical floor division: floor(-7/2) = -4.
C++ truncation: trunc(-7/2) = -3. These differ for negative dividends.

**The fix.** For floor division:

```cpp
int floordiv(int a, int b) {
    return a / b - (a % b != 0 && (a ^ b) < 0);
}
```

Or: `(a - (b-1)) / b` when b > 0 and you want ceiling instead of floor.

**Ceiling division (positive values):**

```cpp
int ceildiv(int a, int b) {
    return (a + b - 1) / b;  // only correct for a >= 0, b > 0
}
```

---

## Category 2: Off-by-One and Indexing Errors

### 2.1 Prefix Sum Indexing

**The convention.** P[0] = 0, P[i] = a[0] + a[1] + ... + a[i-1].

**The bug.** Confusing inclusive and exclusive bounds.

| What you want | Formula |
|---|---|
| Sum of a[l..r] inclusive | P[r+1] - P[l] |
| Sum of a[l..r) exclusive of r | P[r] - P[l] |

**Why it goes wrong.** Off-by-one in the upper bound. If you define P[i] as
"sum of first i elements," then P[r] gives the sum of a[0..r-1], and you need
P[r+1] for a[0..r].

**The fix.** Always use 0-indexed arrays and the convention that P[i] = sum of
a[0..i-1]. Then sum of a[l..r] = P[r+1] - P[l]. Drill this until it is
automatic.

### 2.2 Binary Search Boundaries

**The bug.** Starting binary search at left = 0, right = n-1 and accessing
array[mid] can miss edge cases or go out of bounds.

**The fix.** Use the sentinel-based template:

```
left = -1       (always invalid / always satisfies "too low")
right = n       (always invalid / always satisfies "too high")
```

Loop invariant: answer is in (left, right). When left + 1 == right, the
answer is right (for "first true") or left (for "last true").

This eliminates all off-by-one issues because the boundaries are *exclusive*
sentinels that never get queried.

### 2.3 Difference Array Boundaries

**The bug.** To add v to a[l..r], you set D[l] += v and D[r+1] -= v.
If r = n-1, then D[r+1] = D[n], which is out of bounds for an array of size n.

**The fix.** Allocate the difference array with size n+1 (or n+2 for safety).
This is a constant amount of extra memory and eliminates the edge case
entirely.

### 2.4 Loop Bounds in Combinatorics

**The bug.** "Choose k items from n" — iterating up to n when you should
iterate up to n-1 (or vice versa).

**Common sources:**
- Stars and bars: n items into k bins uses C(n+k-1, k-1), not C(n, k).
- Fence-post: n points create n-1 intervals.
- 0-indexed vs 1-indexed: always decide at the start and stick to it.

### 2.5 Graph Indexing (1-indexed vs 0-indexed)

**The bug.** Codeforces problems typically use 1-indexed vertices. If your
adjacency list is 0-indexed, you forget to subtract 1 from input (or vice
versa).

**The fix.** Convention: always use 1-indexed for graph problems (allocate
arrays of size n+1). Read vertices directly from input without adjustment.

---

## Category 3: Algorithm Choice Errors

### 3.1 Cycle Detection: Directed vs Undirected

**Undirected graphs.** A cycle exists if and only if DFS finds a back edge
to a vertex that is NOT the parent of the current vertex in the DFS tree.

**Directed graphs.** A cycle exists if and only if DFS finds a back edge to
a vertex currently on the recursion stack (colored GRAY in the 3-color
scheme: WHITE = unvisited, GRAY = in progress, BLACK = finished).

**The bug.** Using parent-tracking (undirected method) on a directed graph.
This gives false positives: an edge u->v where v is visited but not on the
stack is NOT a cycle in a directed graph.

**The bug (reverse).** Using 3-color (directed method) on an undirected graph
without excluding the parent edge. Every undirected edge u-v creates edges
u->v and v->u, so the DFS will immediately see v->u as a "back edge" to a
GRAY vertex, falsely detecting a cycle of length 2.

### 3.2 Knapsack: Loop Order

**0/1 Knapsack (each item used at most once).**
Iterate items in the outer loop, weights in the inner loop *backwards*:

```cpp
for (int i = 0; i < n; i++)
    for (int w = W; w >= weight[i]; w--)
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
```

**Unbounded Knapsack (each item used arbitrarily many times).**
Iterate weights *forwards*:

```cpp
for (int i = 0; i < n; i++)
    for (int w = weight[i]; w <= W; w++)
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
```

**Why.** Backward iteration ensures each item is counted once (we read from
the previous layer). Forward iteration allows re-using the item (we read from
the current layer, which already includes this item).

### 3.3 Coin Change: Combinations vs Permutations

**Combinations (order doesn't matter):** outer loop on coins, inner on amount.

```cpp
for (int coin : coins)
    for (int j = coin; j <= amount; j++)
        dp[j] += dp[j - coin];
```

**Permutations (order matters):** outer loop on amount, inner on coins.

```cpp
for (int j = 1; j <= amount; j++)
    for (int coin : coins)
        if (j >= coin) dp[j] += dp[j - coin];
```

**Why.** In the combinations version, each coin is "introduced" once, so
sequences like (1,2) and (2,1) are not both counted. In the permutations
version, at each amount, all coins are available, so both orderings are
counted.

### 3.4 Shortest Path Algorithm Selection

| Condition | Algorithm | Complexity |
|---|---|---|
| Unweighted | BFS | O(V + E) |
| Non-negative weights | Dijkstra | O((V + E) log V) |
| Negative weights, no neg cycles | Bellman-Ford | O(V * E) |
| All pairs | Floyd-Warshall | O(V^3) |
| DAG | Topological sort + relaxation | O(V + E) |

**The bug.** Using Dijkstra with negative edge weights. Dijkstra assumes that
once a vertex is finalized, its distance is optimal. Negative edges violate
this assumption, and the algorithm produces incorrect results.

### 3.5 Forgetting to Handle Disconnected Graphs

**The bug.** Running a single BFS/DFS from node 1 and assuming all vertices
are reached.

**The fix.** Always loop over all vertices and start a new BFS/DFS from any
unvisited vertex:

```cpp
for (int i = 1; i <= n; i++)
    if (!visited[i])
        bfs(i);  // or dfs(i)
```

---

## Category 4: Performance Pitfalls

### 4.1 unordered_map and Hash Collision Attacks

**The bug.** Using `unordered_map<int, int>` with default hash. On Codeforces,
adversarial test cases can cause O(n) collisions per lookup, turning O(n)
expected time into O(n^2).

**Why.** The default hash for integers in many GCC versions is the identity
function. An adversary who knows this can construct inputs where all keys
hash to the same bucket.

**The fix.** Use a custom hash with randomized salt:

```cpp
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<int, int, custom_hash> mp;
```

Or just use `map<int, int>` (O(log n) per operation, but no adversarial risk).

### 4.2 endl vs '\n'

**The bug.** Using `endl` in a loop that prints many lines.

**Why.** `endl` flushes the output buffer after every line. Flushing is a
system call, which is slow. With 10^5 lines, this can add hundreds of
milliseconds.

**The fix.** Use `'\n'` instead of `endl`. Only flush when necessary (e.g.,
interactive problems).

### 4.3 Missing Fast I/O

**The bug.** Not adding `ios::sync_with_stdio(false); cin.tie(nullptr);` at
the start of main.

**Why.** By default, C++ synchronizes `cin`/`cout` with `scanf`/`printf`,
which adds overhead. `cin.tie(nullptr)` prevents `cout` from flushing before
every `cin` read.

**The cost of forgetting:** 5-10x slowdown on I/O-heavy problems. This alone
can cause TLE.

**The fix:**

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

**Warning:** After this, do NOT mix `cin`/`cout` with `scanf`/`printf`.

### 4.4 Unnecessary Copies of Large Data Structures

**The bug.** Passing `vector<int> v` by value to a function.

**Why.** This copies the entire vector on every call. If the vector has 10^5
elements and the function is called 10^5 times, that is 10^{10} copy
operations.

**The fix.** Pass by reference: `vector<int>& v` or `const vector<int>& v`.

### 4.5 Resizing Inside Loops

**The bug.** Calling `push_back` in a tight loop on a vector that will
eventually hold n elements, without `reserve(n)`.

**Why.** `push_back` occasionally reallocates and copies the entire vector.
Amortized O(1), but the hidden constant and cache effects matter in tight TL.

**The fix.** `v.reserve(n)` before the loop, or preallocate: `vector<int> v(n)`.

---

## Category 5: Logical and Structural Errors

### 5.1 Greedy Without Proof

**The bug.** Applying a greedy heuristic that "seems right" without proving
correctness.

**Why it is dangerous.** Greedy algorithms are either exactly right or
completely wrong — there is rarely a middle ground. A greedy that fails on
one test case will fail on many.

**The fix.** Before coding, prove the greedy is correct (exchange argument)
or find a counterexample. If you cannot do either in 5 minutes, switch to DP.

### 5.2 DP State Definition Mismatch

**The bug.** The DP state does not capture enough information for transitions,
or captures too much (making the state space too large).

**Symptoms:**
- "I need to know something about the past that my state doesn't record"
  -> state is incomplete, need augmentation (Pattern 3).
- "My DP has 10^{15} states" -> state captures too much, need to find what
  can be dropped.

**The fix.** Before coding, explicitly write:
1. What is dp[...] (the state)?
2. What is the value stored (the answer for this subproblem)?
3. What are the transitions (recurrence)?
4. What is the base case?
5. What is the final answer (which state gives it)?

### 5.3 Not Handling Edge Cases

**Common edge cases that break solutions:**
- n = 1 (single element / trivial input).
- All elements equal.
- All elements zero.
- Negative numbers when the solution assumes non-negative.
- Empty graph (no edges).
- Disconnected graph (when solution assumes connected).
- k = 0 or k = n (boundary values of parameters).
- String of length 1.

**The fix.** After writing the solution, mentally test it on these inputs.

### 5.4 Wrong Comparator for Sorting

**The bug.** Writing a comparator that is not a strict weak ordering.

**Requirements for a valid comparator:**
1. Irreflexivity: comp(a, a) = false.
2. Asymmetry: comp(a, b) = true implies comp(b, a) = false.
3. Transitivity: comp(a, b) and comp(b, c) implies comp(a, c).

**Common violation:** Using `<=` instead of `<`. This violates irreflexivity
(a <= a is true), and `std::sort` has undefined behavior.

**The consequence:** Runtime error or infinite loop inside `std::sort`.

---

## Category 6: Areas for Growth (Self-Assessment)

### Sliding Window (37.5% completion)

**Diagnosis:** Weakest area. The main difficulty is with non-invertible
operations (min/max over sliding windows) and problems where the window
condition is non-trivial.

**Action items:**
- Practice monotonic deque for sliding window min/max.
- Practice variable-length windows with complex predicates.
- Understand the two-stack trick for general associative operations.

### Number Theory (68.3% completion)

**Diagnosis:** Basic NT (GCD, sieve, modular arithmetic) is solid. Advanced
topics need work.

**Action items:**
- Modular GCD and extended Euclidean applications.
- Prime power decomposition problems.
- Euler's totient function and its multiplicative properties.
- Chinese Remainder Theorem (constructive).

### Graphs (78% completion)

**Diagnosis:** BFS, DFS, Dijkstra, basic DP on trees solid. Advanced topics
upcoming.

**Action items:**
- Strongly connected components (Tarjan's / Kosaraju's).
- Articulation points and bridges.
- Bipartite matching.
- Euler paths and circuits.

### DP (75% completion)

**Diagnosis:** Standard knapsack, grid DP, and basic state DP are reliable.
Need more work on:
- Bitmask DP.
- DP on trees (rerooting technique).
- Digit DP.
- Optimization techniques (Knuth's, divide-and-conquer optimization).

---

## The Debugging Protocol

When a solution gives Wrong Answer or TLE, follow this systematic procedure:

### Step 1: Read the Problem Again
50% of WA comes from misreading the problem. Check:
- 1-indexed vs 0-indexed?
- "at most" vs "exactly" vs "at least"?
- Output format (YES/Yes/yes)?

### Step 2: Check Arithmetic
- Overflow? Add `#define int long long` and resubmit.
- Modular arithmetic? Check subtraction and division.
- Division truncation? Check signs.

### Step 3: Check Edge Cases
- n = 1, k = 0, empty input.
- All same values. All zeros.

### Step 4: Stress Test
Write a brute force solution and a random input generator. Compare outputs:

```bash
while true; do
    python3 gen.py > input.txt
    ./brute < input.txt > out1.txt
    ./sol < input.txt > out2.txt
    if ! diff -q out1.txt out2.txt; then
        echo "MISMATCH"
        cat input.txt
        break
    fi
done
```

This finds almost every bug, given enough time.

### Step 5: For TLE
- Check complexity. Is it tight for the constraints?
- Check I/O: fast I/O enabled? No `endl`?
- Check data structures: `unordered_map` with custom hash?
- Check unnecessary copies or allocations.
