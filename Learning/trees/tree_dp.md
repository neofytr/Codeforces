# Tree DP and Rerooting

---

## 1. Tree DP -- The General Framework

### 1.1 The Principle

**Observation.** A rooted tree is a recursively defined structure: the tree rooted at v consists of v together with the subtrees rooted at each child of v. This recursive structure makes dynamic programming a natural fit.

**Principle.** For tree DP, the natural computation order is *post-order* (bottom-up): process all children of v before processing v itself. This is guaranteed by a DFS where the DP computation for v occurs after the recursive calls to all children.

**General form:**

    dp[v] = combine({dp[c] : c in children(v)}, info(v))

where `combine` is problem-specific and `info(v)` encodes local vertex/edge information.

### 1.2 General Skeleton

```cpp
vector<long long> dp(n, 0);

function<void(int, int)> dfs = [&](int v, int par) {
    // Initialize dp[v] with base case / local info
    dp[v] = /* base value */;
    for (int u : adj[v]) {
        if (u == par) continue;
        dfs(u, v);
        // Combine dp[u] into dp[v]
        dp[v] = combine(dp[v], dp[u]);
    }
    // Possibly update a global answer using dp[v]
};

dfs(root, -1);
```

---

## 2. Four Common Patterns

### Pattern 1: Subtree Aggregation

    dp[v] = f(v) + sum_{c in children(v)} dp[c]

Example: counting the number of vertices, sum of values, or number of leaves in a subtree. The function f(v) contributes the local information at v.

### Pattern 2: Subtree Optimization

    dp[v] = optimize_{valid configurations} g(dp[c_1], ..., dp[c_k], info(v))

Example: maximum independent set on a tree. Define dp[v][0] = max independent set in T(v) not including v, dp[v][1] = ... including v. Then:

    dp[v][0] = sum_{c} max(dp[c][0], dp[c][1])
    dp[v][1] = val(v) + sum_{c} dp[c][0]

### Pattern 3: Diameter-like (tracking two best values)

The DP returns one value (e.g., height), but a global answer is updated using two best values from children. The diameter algorithm is the archetype. This pattern appears whenever the answer is a "path through some vertex" and requires combining two descending paths.

### Pattern 4: Balance / comparison of subtrees

    dp[v] = some balance measure, parent aggregates and compares children's values.

Example: checking if a tree is balanced (|h(left) - h(right)| <= 1 at every node).

---

## 3. Rerooting DP

### 3.1 The Problem

**Problem.** For each vertex v in V, compute f(v) = the answer to some query assuming v is the root.

**Naive approach.** For each v, re-root the tree and run tree DP. Time: O(n^2).

**Efficient approach.** Two-pass rerooting in O(n).

### 3.2 The Two-Pass Algorithm

**Key insight.** When we move the root from v to a child c, the only structural change is:
- c's subtree loses c (it becomes the new root), and gains everything outside the old subtree of c.
- v's contribution to c changes from "parent" to "child in c's subtree."

We can precompute enough information to handle this transition in O(1) per vertex.

**Pass 1 (Down pass).** Root the tree at vertex 1. Compute dp_down[v] for each v via standard tree DP.

    dp_down[v] = combine({dp_down[c] + edge(v,c) : c in children(v)})

This captures information from the subtree below v.

**Pass 2 (Up/Reroot pass).** For each vertex v with parent p, compute dp_up[v] = the contribution from everything outside T(v). When v is the root, its answer uses both dp_down[v] (its subtree) and nothing else. When a child c of v becomes the root, c's answer combines:
- dp_down[c] (its original subtree, unchanged), and
- the rest of the tree = dp_up[v] combined with contributions from all siblings of c.

Formally:

    dp_up[c] = combine(dp_up[v], {dp_down[s] + edge(v,s) : s in children(v), s != c}) + edge(v,c)

The final answer for each vertex v is:

    f(v) = combine(dp_down[v], dp_up[v])

### 3.3 The Invertibility Requirement

**Critical requirement.** To compute the sibling contributions efficiently (excluding one child), we need the combine operation to be "invertible" or "subtractable."

**Case 1: combine = sum.** To get the sum of all children's values except c, compute total_sum - dp_down[c]. O(1).

**Case 2: combine = max.** We cannot simply subtract the max. Instead, store the top two maximum values among children. If c contributed the maximum, use the second maximum. O(1) with O(k) preprocessing per vertex (where k is the number of children).

**Case 3: combine = product.** If dp_down[c] != 0, divide. If dp_down[c] = 0, count zeros: if more than one zero, the product-excluding-c is 0; if exactly one zero (which is c), the product-excluding-c is the product of nonzero terms.

**General solution with prefix/suffix arrays.** For any associative combine operation, precompute prefix[i] = combine(dp_down[c_1], ..., dp_down[c_i]) and suffix[i] = combine(dp_down[c_i], ..., dp_down[c_k]). Then:

    combine_excluding_c_i = combine(prefix[i-1], suffix[i+1])

This works in O(k) per vertex (total O(n) over the whole tree), regardless of whether the operation is invertible.

### 3.4 Complexity

Both passes visit each vertex once, and the work per vertex is proportional to its degree. Total: O(n).
