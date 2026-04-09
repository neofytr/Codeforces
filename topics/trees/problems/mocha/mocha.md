# mocha

```markdown
# Competitive Programming Solution Documentation

## 1. Problem Description

The problem is [Mocha and Diana (Easy Version)](https://codeforces.com/problemset/problem/1559/D1) from Codeforces Round #738 (Div. 2).

Mocha and Diana each have a forest (an undirected graph without cycles, not necessarily connected) consisting of `n` nodes labeled from 1 to `n`. The task is to find the maximum number of edges that can be added to both forests such that after adding the edges, both graphs remain forests. The edges added to Mocha's forest must be the same edges added to Diana's forest. The output should be the number of edges added and the list of edges.

## 2. Approach Explanation

The core idea is to iterate through all possible edges (u, v) where `1 <= u < v <= n` and check if adding that edge would create a cycle in either Mocha's or Diana's forest.  This can be efficiently done using the Disjoint Set Union (DSU) data structure.

For each potential edge (u, v):

1.  Check if adding the edge (u, v) to Mocha's forest would create a cycle. This is equivalent to checking if `u` and `v` are already in the same connected component in Mocha's forest using `mocha.isConnected(u, v)`.
2.  Similarly, check if adding the edge (u, v) to Diana's forest would create a cycle using `diana.isConnected(u, v)`.
3.  If adding the edge (u, v) would not create a cycle in either forest (i.e., both `mocha.isConnected(u, v)` and `diana.isConnected(u, v)` return `false`), then add the edge (u, v) to both forests using `mocha.unite(u, v)` and `diana.unite(u, v)`. Also store this edge in the answer vector `ans`.
4.  Finally, output the total number of added edges (the size of `ans`) and the list of edges in the `ans` vector.

## 3. Key Insights and Algorithmic Techniques Used

*   **Disjoint Set Union (DSU):** The DSU data structure is crucial for efficiently determining if two nodes are in the same connected component in a forest.  It provides `isConnected` to check connectivity and `unite` to merge connected components, both with near-constant amortized time complexity due to path compression and union by size/rank optimizations.

*   **Greedy Approach:** The solution iterates through all possible edges in a systematic way and greedily adds an edge if it doesn't violate the forest property for both graphs.  The correctness of this greedy approach stems from the fact that if an edge can be added without creating cycles in either forest, it should be added to maximize the number of edges. The order in which we consider edges doesn't affect the final outcome.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DSU initialization takes O(n) time.
    *   Iterating through all possible edges takes O(n<sup>2</sup>) time.
    *   For each edge, `isConnected` and `unite` operations in DSU take approximately O(α(n)) amortized time each, where α(n) is the inverse Ackermann function, which grows extremely slowly and can be considered nearly constant for practical values of n.
    *   Therefore, the overall time complexity is dominated by the O(n<sup>2</sup> * α(n)) part, which is approximately O(n<sup>2</sup>).

*   **Space Complexity:**
    *   The DSU data structures (`mocha` and `diana`) each require O(n) space to store the parent and size information.
    *   The `ans` vector can store at most O(n) edges in the best-case scenario where the initial graphs are very sparse. However, in some cases, it can store upto O(n^2) edges so, overall O(n^2) space in worst cases.

## 5. Important Code Patterns or Tricks Used

*   **DSU Implementation with Path Compression and Union by Size:** The provided DSU implementation includes both path compression (`getRoot` function) and union by size (`unite` function), which significantly optimizes its performance. This reduces the amortized time complexity of `isConnected` and `unite` operations to near constant.
*   **Iterating Through Potential Edges Systematically:** The loop `for (int u = 1; u <= n; u++) for (int v = u + 1; v <= n; v++)` ensures that each possible edge (u, v) with `u < v` is considered exactly once, avoiding redundant checks and potential duplicates in the `ans` vector. This avoids adding same edge twice like (1, 2) and (2, 1).
*   **Using `ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard trick in competitive programming to disable synchronization between C++ streams and the C standard input/output library, which can significantly improve the input/output performance, especially for problems with a large amount of input or output.

## 6. Any Edge Cases Handled

*   The problem statement guarantees that both initial graphs are forests, so the code doesn't need to explicitly check for cycles in the initial input.
*   The condition `u < v` in the nested loop prevents processing the same edge twice and ensures that only valid edges are considered.
*   The DSU inherently handles the case where nodes are already connected in a forest; it simply doesn't add an edge if `isConnected` returns `true`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mocha
// URL: https://codeforces.com/problemset/problem/1559/D1
// Difficulty: hard
// Tags:
// Strategy:

class disjointSetUnion {
  public:
    vector<int> parent;
    vector<int> size;

    disjointSetUnion(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int r = 1; r <= n; r++)
            parent[r] = r, size[r] = 1;
    }

    int getRoot(int x) {
        int y = x;
        while (x != parent[x])
            x = parent[x];

        int tmp;
        while (y != parent[y])
            tmp = parent[y], parent[y] = x, y = tmp;
        return x;
    }

    bool isConnected(const int x, const int y) { return getRoot(x) == getRoot(y); }

    void unite(const int x, const int y) {
        int rootX = getRoot(x);
        int rootY = getRoot(y);
        if (rootX == rootY)
            return;

        int sizeX = size[rootX];
        int sizeY = size[rootY];

        if (sizeY > sizeX) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m1, m2;
    cin >> n >> m1 >> m2;

    int u, v;
    disjointSetUnion mocha(n), diana(n);
    while (m1--)
        cin >> u >> v, mocha.unite(u, v);
    while (m2--)
        cin >> u >> v, diana.unite(u, v);

    // a forest is an undirected graph without cycles (not necessarily connected)
    // mocha and diana are friends
    // both of them have forests with nodes numbered 1 to n
    // they would like to add edges to their forests such that:

    // 1. after adding edges, both their graphs are still forests
    // 2. they add the same edges

    // they want to know the maximum number of edges they can add, and which edges to add

    int cnt = 0;
    vector<pair<int, int>> ans;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (!mocha.isConnected(u, v) && !diana.isConnected(u, v))
                cnt++, ans.push_back({u, v}), mocha.unite(u, v), diana.unite(u, v);

    cout << cnt << endl;
    for (auto &[u, v] : ans)
        cout << u << " " << v << endl;

    return 0;
}
```

---
*Documentation generated on 2025-09-04 23:50:34*
