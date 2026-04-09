# maxMinPath

```markdown
# Competitive Programming Solution Documentation

This document provides a comprehensive analysis of the provided C++ code, focusing on the problem it solves, the approach taken, and relevant algorithmic aspects.

## 1. Problem Description

The code solves the "maxMinPath" problem, accessible at [https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D](https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D).

The problem statement (inferred from the code and comments) can be summarized as follows:

Given a directed graph with `n` nodes (labeled 1 to `n`) and `m` edges, where each edge has a weight, and a maximum edge count `d`. The goal is to find the minimum possible maximum edge weight among all paths from node 1 to node `n` with at most `d` edges.

Formally:
* Let `x` be a path from node 1 to node `n` with at most `d` edges.
* Let `m(x)` be the maximum edge weight in the path `x`.
* Find `min(m(x))` for all valid paths `x`.

If no such path exists, the program should output -1. The nodes are numbered from 1 to `n`, and the edges are directed. The problem likely expects the code to output the number of edges and the path.

## 2. Approach Explanation

The solution employs a binary search approach combined with Breadth-First Search (BFS).

1.  **Binary Search:** The core idea is to use binary search to find the minimum possible maximum edge weight.  The search space is the range of possible edge weights, from 0 (or a small value) up to the maximum edge weight in the graph. The `pathExists` function serves as the predicate for the binary search.

2.  **`pathExists(maxWt, maxEdges, graph)` function:** This function determines if there exists a path from node 1 to node `n` with at most `maxEdges` edges, where all edge weights in the path are less than or equal to `maxWt`. It uses BFS to explore the graph.  The `dist` vector tracks the minimum number of edges needed to reach each node, considering only edges with weights less than or equal to `maxWt`.

3.  **`buildPath(maxWt, maxEdges, graph)` function:**  This function reconstructs a path between node 1 to node `n` with at most `maxEdges` edges, where all edges are less than or equal to `maxWt`.  It uses BFS in similar style to the `pathExists` function but maintains a `parent` vector to store how each node was reached.  Once BFS has completed, the path is constructed by backtracking from node `n` to node 1 using the `parent` vector.

4.  **Main Function:**
    *   Reads input: `n`, `m`, `d`, and the graph's edges.
    *   Sets the initial search space for binary search: `left = -1` (no path with negative max edge weight) and `right = maxwt` (the maximum edge weight).
    *   Performs binary search using `pathExists` to narrow down the minimum possible maximum edge weight.
    *   If a valid path is found (`pathExists` returns true), the code calls `buildPath` to reconstruct and output the path and the number of edges.
    *   If no path is found, the code outputs -1.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search on Monotonic Predicate:** The key insight is recognizing that the problem lends itself to binary search. The predicate `pathExists(r, d, graph)` is monotonic: if a path exists with a maximum edge weight of `r`, then a path also exists with a maximum edge weight of `r + 1`. This monotonicity allows efficient searching.

*   **Breadth-First Search (BFS):** BFS is used to find the shortest path (in terms of the number of edges) between two nodes, subject to the constraint on edge weights. BFS is appropriate for finding shortest paths in unweighted graphs (or graphs where the cost is the number of edges), which matches the problem's requirement of finding a path with at most `d` edges.

*   **Graph Representation:** The graph is represented using an adjacency list (`vector<vector<pair<int, int>>> graph`), where `graph[u]` contains a list of pairs `(v, w)`, indicating an edge from node `u` to node `v` with weight `w`.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Building the graph takes O(m) time.
    *   Binary search runs in O(log(maxwt)) iterations.
    *   Inside each iteration of the binary search, `pathExists` and `buildPath` perform BFS, which takes O(V + E) time, where V is the number of nodes (n) and E is the number of edges (m) under current weight limits. In the worst case, that may mean O(n + m) if all edges have weights lower than the current value.
    *   Reconstructing the path in `buildPath` takes O(n) in the worst case.
    *   Therefore, the overall time complexity is O(m + log(maxwt) * (n + m)).

*   **Space Complexity:**
    *   The graph representation takes O(m) space.
    *   The `dist` and `parent` vectors in BFS take O(n) space.
    *   The queue in BFS takes O(n) space in the worst case.
    *   The path vector in buildPath takes O(n) space in the worst case
    *   Therefore, the overall space complexity is O(n + m).

## 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:** Using `vector<vector<pair<int, int>>>` is a standard and efficient way to represent graphs when dealing with edge weights.

*   **`#define int long long`:** This macro is a common practice in competitive programming to prevent integer overflow issues, especially when dealing with larger numbers.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to speed up input/output operations by disabling synchronization between the C++ standard input/output streams and the C standard input/output streams.

*   **`for (auto &[v, w] : graph[u])`:** This is a C++17 feature called structured binding in range-based for loops.  It allows you to directly access the elements of the pair (node and weight) without needing to use `pair.first` and `pair.second`.

## 6. Any Edge Cases Handled

*   **No Path Exists:** The code explicitly handles the case where no path exists from node 1 to node `n` with at most `d` edges, by outputting -1.  This is handled in the main loop and after the binary search.
*   **Directed Graph:** The code inherently handles directed graphs due to the way the adjacency list is populated, only adding edges in one direction.
*   **1-based indexing:** The code implicitly assumes 1-based indexing of nodes.

```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: maxMinPath
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/D
// Difficulty: hard
// Tags:
// Strategy:

bool pathExists(int maxWt, int maxEdges, vector<vector<pair<int, int>>> &graph) {
    // we are to find if there is a path from 1 to n such that all the edge weights are atmost maxWt
    // we will build the shortest such path, so, if its within d edges, we are done
    int n = graph.size(); // n + 1 since 1-based
    vector<int> parent(n);
    vector<int> dist(n, 1e9); // number of edges to reach each node
    queue<int> que;

    int src = 1;
    dist[src] = 0;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (auto &[v, w] : graph[u]) {
            if (w <= maxWt && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }

    return dist[n - 1] <= maxEdges;
}

pair<vector<int>, int> buildPath(int maxWt, int maxEdges, const vector<vector<pair<int, int>>> &graph) {
    int n = graph.size();
    vector<int> dist(n, 1e9);
    vector<int> parent(n, -1);
    queue<int> que;

    int src = 1;
    dist[src] = 0;
    parent[src] = src;
    que.push(src);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (auto &[v, w] : graph[u]) {
            if (w <= maxWt && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                que.push(v);
            }
        }
    }

    vector<int> path;
    int dst = n - 1;
    if (parent[dst] == -1 || dist[dst] > maxEdges)
        return {{}, -1};

    while (dst != parent[dst]) {
        path.push_back(dst);
        dst = parent[dst];
    }
    path.push_back(dst);
    reverse(path.begin(), path.end());

    return {path, (int)path.size() - 1}; // edges = nodes - 1
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, d;
    cin >> n >> m >> d;

    vector<vector<pair<int, int>>> graph(n + 1);
    int a, b, c;
    int maxwt = -1;
    while (m--) {
        cin >> a >> b >> c;
        maxwt = max(maxwt, c);
        graph[a].push_back({b, c}); // directed edges since we can only travel along the road one way
    }

    // there are n nodes labelled 1 to n and m directed edges between them
    // each edge is directed from a lower number node to a higher number node
    // this means, that is graph is acylic (a DAG basically)

    // Let x is a path from 1 to n with atmost d edges
    // We define m(x) to be the maximum edge weight in the path x
    // We are to determine min(m(x) for all paths x from 1 to n with atmost d edges)

    // We define a predicate f as follows
    // f(r) = 1 if there is a path from 1 to n with atmost d edges that has all the edge weights atmost r
    //      = 0 otherwise

    // if there is a path from 1 to n with atmost d edges that has all the edge weights atmost r, then
    // such a path with edge weights atmost r + 1 will exist

    // thus, f is monotonic

    int left = -1;     // since all edge weights are non-negative, this isnt' possible
    int right = maxwt; // since edge weights range from 0 to 1e9, this is possible

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (pathExists(mid, d, graph))
            right = mid;
        else
            left = mid;
    }

    if (!pathExists(right, d, graph)) {
        cout << -1 << endl;
        return 0;
    }

    auto [path, numEdges] = buildPath(right, d, graph);
    cout << numEdges << '\n';
    for (int v : path)
        cout << v << ' ';
    cout << '\n';

    return 0;
}
```

---
*Documentation generated on 2025-08-08 16:59:12*
