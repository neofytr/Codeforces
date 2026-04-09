# Sliding Window Data Structures: A Rigorous Treatment

---

## Section 1: When Two Pointers Need Data Structures

### The Divide

The two-pointer technique manages the **window** --- it decides which segment $[l, r]$
to examine. But many problems also require maintaining an **aggregate** over the
current window: the minimum, maximum, GCD, median, or some other summary statistic.

The fundamental question is: can the aggregate be maintained cheaply as the window
slides?

### Definition (Invertible Aggregate)

An aggregate operation $\oplus$ over a window is **invertible** if there exists an
operation $\ominus$ such that for any window state $S$ and element $x$:

$$\text{remove}(S, x) = S \ominus x \quad \text{where} \quad (S \oplus x) \ominus x = S$$

When $\oplus$ is invertible, we maintain the aggregate directly in $O(1)$ per
add/remove, and no additional data structure is needed.

| Operation | $\oplus$ | $\ominus$ | Invertible |
|-----------|---------|---------|------------|
| Sum | $+$ | $-$ | Yes |
| XOR | $\oplus$ | $\oplus$ | Yes (self-inverse) |
| Product | $\times$ | $\div$ | Yes (if no zeros) |
| Bitwise OR | $\mid$ | ??? | No |
| Minimum | $\min$ | ??? | No |
| Maximum | $\max$ | ??? | No |
| GCD | $\gcd$ | ??? | No |

For **non-invertible** operations, we need specialized data structures. The rest of
this guide addresses exactly this case.

### The Architectural Principle

Even when we use a data structure for the aggregate, we still use the two-pointer
skeleton for window management. The structure of the code is:

```
r = 0
for l = 0 to n-1:
    while r < n and canExtend(l, r):
        DS.add(a[r])        // data structure handles aggregate
        r++
    answer[l] = DS.query()  // data structure answers aggregate query
    DS.remove(a[l])          // data structure handles removal
```

The data structure provides `add`, `remove`, and `query`. The two-pointer logic
provides the window management. They are orthogonal concerns.

---

## Section 2: The Monotonic Deque --- Sliding Window Min/Max

### Problem Statement

Given an array $a[0], \ldots, a[n-1]$ and a fixed window size $k$, compute:

$$m[i] = \min(a[i], a[i+1], \ldots, a[i+k-1]) \quad \text{for } i = 0, 1, \ldots, n-k$$

(The max version is symmetric; replace $\min$ with $\max$ and reverse comparisons.)

### The Dominance Principle

**Definition.** Element $a[i]$ is **dominated** by element $a[j]$ (for the min problem)
if $i < j$ and $a[i] \ge a[j]$.

**Lemma 1.** If $a[i]$ is dominated by $a[j]$, then $a[i]$ is never the minimum of
any window that contains $a[j]$.

**Proof.** If both $a[i]$ and $a[j]$ are in the window, then $a[j] \le a[i]$, so
$a[i]$ is not the minimum. Moreover, since $i < j$, element $a[i]$ will leave the
window (as the window slides right) no later than $a[j]$. So for all future windows:
either $a[j]$ is present (and dominates $a[i]$), or $a[i]$ has already left. In
neither case is $a[i]$ the minimum. $\blacksquare$

**Corollary.** We can safely discard all dominated elements. The remaining elements
form a subsequence with **strictly increasing values** (if $i < j$ and both survive,
then $a[i] < a[j]$, otherwise $a[i]$ would be dominated by $a[j]$).

### The Data Structure

Maintain a **deque** $D$ of indices. The invariant is:

1. **Index order.** The indices in $D$ are in strictly increasing order (left to right).
2. **Value order.** The values $a[D[0]], a[D[1]], \ldots$ are in strictly increasing
   order.
3. **Window membership.** All indices in $D$ are within the current window.

Under this invariant, $D[0]$ (the front) holds the index of the minimum.

### Operations

**add(r)** --- add element $a[r]$ to the window:
```
while D is not empty and a[D.back()] >= a[r]:
    D.pop_back()       // discard dominated elements
D.push_back(r)
```

**remove(l)** --- remove the element that has just left the window:
```
if D is not empty and D.front() < l:
    D.pop_front()
```

Alternatively, for a fixed-size window sliding by one position, the removal condition
is $D.\text{front}() == l - 1$ (the element that just fell off the left edge) or more
robustly $D.\text{front}() \le r - k$ where $r$ is the current right boundary.

**query()** --- return the current window minimum:
```
return a[D.front()]
```

### Theorem 4 (Correctness)

**Claim.** After processing each window position, $D.\text{front}()$ is the index of
the minimum element in the current window.

**Proof.** By the invariant, all indices in $D$ are within the current window, and
their values are strictly increasing. We must show that the true minimum is in $D$.

Suppose $a[m]$ is the minimum of the current window and $m \notin D$. Then $m$ was
removed from $D$ at some point during a `pop_back` operation when processing some
index $j > m$ with $a[j] \le a[m]$. But then $a[j] \le a[m]$, contradicting the
assumption that $a[m]$ is the minimum of the window (since $j$ is also in the window).
$\blacksquare$

### Theorem 5 (Amortized $O(1)$ per operation)

**Claim.** Processing all $n$ elements takes $O(n)$ total time.

**Proof.** Each index is pushed onto $D$ exactly once and popped at most once (either
from the back during a future `add`, or from the front during a `remove`). The total
number of push and pop operations is at most $2n$. Since each `add` does a constant
amount of work plus some pops, and each `remove` does $O(1)$ work, the total is
$O(n)$.

Amortized per operation: $O(n) / n = O(1)$. $\blacksquare$

### Implementation for Fixed Window Size $k$

```cpp
deque<int> dq;
for (int r = 0; r < n; r++) {
    // add a[r]
    while (!dq.empty() && a[dq.back()] >= a[r])
        dq.pop_back();
    dq.push_back(r);

    // remove elements outside window
    if (dq.front() <= r - k)
        dq.pop_front();

    // query: window is full when r >= k - 1
    if (r >= k - 1)
        answer[r - k + 1] = a[dq.front()];
}
```

### Implementation for Variable Window (Two-Pointer Integration)

When the window size is not fixed but determined by two pointers:

```cpp
deque<int> dq;
int r = 0;
for (int l = 0; l < n; l++) {
    while (r < n && canExtend(l, r)) {
        // add a[r] to deque
        while (!dq.empty() && a[dq.back()] >= a[r])
            dq.pop_back();
        dq.push_back(r);
        r++;
    }
    // query
    if (!dq.empty())
        window_min = a[dq.front()];

    // remove a[l] from deque
    if (!dq.empty() && dq.front() == l)
        dq.pop_front();
}
```

---

## Section 3: The Two-Stack Queue --- Aggregate Over Sliding Window

### Motivation

The monotonic deque is specialized to min/max. What if we need the sliding window
GCD, or the sliding window result of any **associative** binary operation?

We need a structure that supports:
- `push_back(x)` --- add $x$ to the right end
- `pop_front()` --- remove from the left end
- `query()` --- return the aggregate $a[l] \oplus a[l+1] \oplus \cdots \oplus a[r]$

where $\oplus$ is an arbitrary **associative** (but not necessarily invertible)
operation.

### Key Insight: A Stack Naturally Supports Aggregates

A stack with elements $x_1, x_2, \ldots, x_t$ (bottom to top) can maintain the
running aggregate $x_1 \oplus x_2 \oplus \cdots \oplus x_i$ for each prefix by
storing, alongside each element $x_i$, the value:

$$\text{agg}_i = x_1 \oplus x_2 \oplus \cdots \oplus x_i$$

On push of $x_{t+1}$: $\text{agg}_{t+1} = \text{agg}_t \oplus x_{t+1}$. This is
$O(1)$.

On pop: just remove the top element. The new top has $\text{agg}_t$ ready. Also $O(1)$.

Query (aggregate of all elements in the stack): $\text{agg}_t$ (the top annotation).
$O(1)$.

**The problem:** a stack supports removal from the top only, but a queue needs removal
from the bottom. This is where the two-stack trick comes in.

### Construction: Simulating a Queue with Two Stacks

Maintain two stacks: **front** (for popping) and **back** (for pushing). Both carry
aggregate annotations as described above.

**push_back(x):**
```
back.push(x)
back.agg = back.empty() ? x : back.top_agg ⊕ x
```

**pop_front():**
```
if front.empty():
    // Transfer all elements from back to front, reversing order
    while back is not empty:
        x = back.pop()
        front.push(x)
        front.agg = front.empty() ? x : front.top_agg ⊕ x
front.pop()
```

**query():**
```
if front.empty(): return back.top_agg
if back.empty():  return front.top_agg
return front.top_agg ⊕ back.top_agg
```

**Why the combination is correct:** The front stack contains elements in **reverse**
order of their position in the queue (the front of the queue is at the top of the
front stack). Its aggregate annotation gives $a[l] \oplus \cdots \oplus a[m]$. The
back stack contains elements in order, giving $a[m+1] \oplus \cdots \oplus a[r]$.
Combining by $\oplus$ gives the full window aggregate, using associativity:

$$(a[l] \oplus \cdots \oplus a[m]) \oplus (a[m+1] \oplus \cdots \oplus a[r]) = a[l] \oplus \cdots \oplus a[r]$$

### Theorem 6 (Amortized $O(1)$ per operation)

**Claim.** A sequence of $n$ push/pop operations on the two-stack queue takes $O(n)$
total time.

**Proof.** Each element is:
1. Pushed onto the back stack exactly once: $O(1)$.
2. Transferred from back to front at most once: $O(1)$ per element (the transfer
   moves all elements, but each element is transferred at most once in its lifetime).
3. Popped from the front stack exactly once: $O(1)$.

Total work per element: $O(1)$ (three constant-time operations across its lifetime).
For $n$ elements: $O(n)$ total. Amortized per operation: $O(1)$. $\blacksquare$

**Important note on the transfer cost.** A single `pop_front` call might trigger a
transfer costing $O(k)$ where $k$ is the size of the back stack. But this transfer
serves the next $k$ pops (since the front stack now has $k$ elements). The cost is
amortized. This is the standard "banker's analysis" for the two-stack queue.

### Implementation

```cpp
template<typename T, typename Op>
struct SlidingWindowAgg {
    struct Frame { T val, agg; };
    stack<Frame> front_stk, back_stk;
    Op op;
    T identity;

    SlidingWindowAgg(Op op, T identity) : op(op), identity(identity) {}

    void push(T x) {
        T new_agg = back_stk.empty() ? x : op(back_stk.top().agg, x);
        back_stk.push({x, new_agg});
    }

    void pop() {
        if (front_stk.empty()) {
            while (!back_stk.empty()) {
                T x = back_stk.top().val;
                back_stk.pop();
                T new_agg = front_stk.empty() ? x : op(front_stk.top().agg, x);
                front_stk.push({x, new_agg});
            }
        }
        front_stk.pop();
    }

    T query() {
        if (front_stk.empty()) return back_stk.top().agg;
        if (back_stk.empty()) return front_stk.top().agg;
        return op(front_stk.top().agg, back_stk.top().agg);
    }
};
```

Usage for sliding GCD:
```cpp
SlidingWindowAgg<int, function<int(int,int)>> sw(__gcd, 0);
```

Usage for sliding min:
```cpp
SlidingWindowAgg<int, function<int(int,int)>> sw(
    [](int a, int b){ return min(a, b); },
    INT_MAX
);
```

**Note.** For min/max specifically, the monotonic deque is preferred (simpler, same
complexity, and supports direct index access). The two-stack queue shines for
operations like GCD where the monotonic deque's dominance argument does not apply.

---

## Section 4: Sliding Window Median (and $k$-th Smallest)

### Problem Statement

Maintain a multiset $W$ representing the current window, supporting:
- `insert(x)`: add element $x$
- `erase(x)`: remove one copy of element $x$
- `median()`: return the median of $W$ (or the $k$-th smallest element)

### The Two-Multiset Approach

Maintain two multisets:
- **lo**: the smaller half (contains the $\lceil |W|/2 \rceil$ smallest elements)
- **hi**: the larger half (contains the remaining elements)

### Invariants

1. **Size balance:** $|\text{lo}| = |\text{hi}|$ or $|\text{lo}| = |\text{hi}| + 1$.
2. **Order:** every element in $\text{lo}$ is $\le$ every element in $\text{hi}$.
   Formally: $\max(\text{lo}) \le \min(\text{hi})$.

Under these invariants: $\text{median} = \max(\text{lo}) = \text{*lo.rbegin()}$.

### Operations

**rebalance()** --- restore the size invariant after an insert or erase:
```
while lo.size() > hi.size() + 1:
    hi.insert(*lo.rbegin())
    lo.erase(lo.find(*lo.rbegin()))
while lo.size() < hi.size():
    lo.insert(*hi.begin())
    hi.erase(hi.begin())
```

**insert(x):**
```
if lo.empty() or x <= *lo.rbegin():
    lo.insert(x)
else:
    hi.insert(x)
rebalance()
```

**erase(x):**
```
if lo.count(x) > 0 and (hi.empty() or x <= *lo.rbegin()):
    lo.erase(lo.find(x))
else:
    hi.erase(hi.find(x))
rebalance()
```

**median():**
```
return *lo.rbegin()
```

### Complexity

Each `insert` or `erase` performs $O(\log n)$ work (multiset operations), plus at
most 2 rebalancing steps (each $O(\log n)$). Total per operation: $O(\log n)$.

For a sliding window of size $k$ over $n$ elements: $O(n \log n)$ total (or
$O(n \log k)$ if you like, since the multisets have size $\le k$).

### Generalization to $k$-th Smallest

Instead of median, maintain the invariant $|\text{lo}| = k$ (for the $k$-th smallest).
The rebalance logic adjusts to maintain this fixed size for $\text{lo}$.

### Alternative: Order-Statistics Tree (Policy-Based)

In C++, `__gnu_pbds::tree` provides an order-statistics tree with $O(\log n)$
`find_by_order(k)` and `order_of_key(x)`. This gives a single-structure solution but
requires careful handling of duplicate values (wrap values in pairs $(a[i], i)$).

---

## Section 5: When to Use What --- Decision Framework

### The Decision Tree

Given a sliding window problem requiring an aggregate:

```
Is the aggregate operation invertible?
├── YES: maintain directly with add/remove. O(1) per step.
│   Examples: sum, XOR, product (no zeros), count, frequency map.
│
└── NO: Is the operation min or max?
    ├── YES: use the monotonic deque. O(1) amortized.
    │   The dominance principle gives a simpler, faster structure than
    │   the general two-stack queue.
    │
    └── NO: Is the operation associative?
        ├── YES: use the two-stack queue. O(1) amortized.
        │   Examples: GCD, LCM, bitwise OR, bitwise AND,
        │   matrix multiplication, string hashing.
        │
        └── NO: use a balanced BST or segment tree. O(log n) per step.
            Examples: median, k-th smallest, count of elements in range.
```

### Summary Table

| Aggregate | Invertible? | Best Structure | Per-Operation |
|-----------|------------|----------------|---------------|
| Sum | Yes | Direct variable | $O(1)$ |
| XOR | Yes | Direct variable | $O(1)$ |
| Product (no zeros) | Yes | Direct variable | $O(1)$ |
| Frequency count | Yes | Hash map / array | $O(1)$ |
| Count distinct | Partially | Freq map + counter | $O(1)$ amortized |
| Minimum | No | Monotonic deque | $O(1)$ amortized |
| Maximum | No | Monotonic deque | $O(1)$ amortized |
| GCD | No | Two-stack queue | $O(1)$ amortized |
| LCM | No | Two-stack queue | $O(1)$ amortized |
| Bitwise AND | No | Two-stack queue | $O(1)$ amortized |
| Bitwise OR | No | Two-stack queue | $O(1)$ amortized |
| Median | No | Two multisets | $O(\log n)$ |
| $k$-th smallest | No | Two multisets / PBDS | $O(\log n)$ |
| Range count | No | Balanced BST | $O(\log n)$ |

### A Note on "Count Distinct"

Counting distinct elements in a window is a special case. The frequency map is
invertible (we can decrement counts), and the "number of distinct elements" can be
maintained as a counter that increments when a frequency goes from 0 to 1, and
decrements when it goes from 1 to 0. This gives $O(1)$ amortized add/remove and
$O(1)$ query. No fancy data structure needed.

---

## Section 6: Combining Two Pointers with Sliding Window Structures

### The General Template

```cpp
// Two-pointer skeleton with sliding window data structure
SlidingWindowStructure DS;
int r = 0;
for (int l = 0; l < n; l++) {
    while (r < n && /* monotonicity check using DS */) {
        DS.add(a[r]);
        r++;
    }
    // Process window [l, r-1] using DS.query()
    process(l, r - 1, DS.query());
    DS.remove(a[l]);
}
```

The two-pointer logic provides $O(n)$ total window moves. The data structure provides
$O(T)$ per add/remove/query. Total: $O(nT)$.

| Structure | $T$ | Total |
|-----------|-----|-------|
| Direct (invertible) | $O(1)$ | $O(n)$ |
| Monotonic deque | $O(1)$ amortized | $O(n)$ |
| Two-stack queue | $O(1)$ amortized | $O(n)$ |
| Two multisets | $O(\log n)$ | $O(n \log n)$ |

### When Two Pointers is Not Possible

Sometimes the predicate lacks monotonicity (e.g., "subarray XOR equals $k$" --- XOR
is not monotone in window size). In these cases, consider:

1. **Fixed-size sliding window:** iterate over all windows of size $k$ with the data
   structure but without two pointers.
2. **Prefix + hash map:** for XOR/sum with exact target, use
   $\text{prefix}[r] \oplus T$ lookups.
3. **Segment tree / sparse table:** for range queries without the sliding constraint.

The sliding window data structures from this guide still apply to fixed-size windows;
you simply slide both endpoints forward by 1 each step, performing one add and one
remove per step.

---

## Appendix: Proof That Associativity Suffices for the Two-Stack Queue

The two-stack queue combines aggregates from the front and back stacks:

$$\text{total} = \text{front\_agg} \oplus \text{back\_agg}$$

This requires that:

$$(a[l] \oplus \cdots \oplus a[m]) \oplus (a[m+1] \oplus \cdots \oplus a[r]) = a[l] \oplus \cdots \oplus a[r]$$

This is exactly the statement of **associativity** of $\oplus$. No commutativity is
needed (the elements stay in order within each stack). No invertibility is needed
(we never "undo" an operation; we just recompute from scratch when transferring).

The operation need not even have an identity element in the general case, though
having one simplifies the implementation (avoids special-casing empty stacks).

This makes the two-stack queue remarkably general. Any associative operation ---
including non-commutative ones like matrix multiplication or string concatenation ---
can be used.
