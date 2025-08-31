# strongVertices

```markdown
## Competitive Programming Solution Documentation: Strong Vertices

This document provides a detailed explanation of the provided C++ code, which solves the "Strong Vertices" problem from Codeforces (problemset/problem/1857/D).

### 1. Problem Description (Inferred)

The problem, as indicated by the code and comments, can be summarized as follows:

Given two arrays `a` and `b` of size `n`, construct a directed graph with `n` vertices (numbered from 1 to `n`). There is an edge from vertex `u` to vertex `v` (where `1 <= u, v <= n` and `u != v`) if and only if `a[u] - a[v] >= b[u] - b[v]`.

A vertex `u` is considered "strong" if it can reach all other vertices in the graph. The task is to find and output the indices of all strong vertices.

The problem URL is: [https://codeforces.com/problemset/problem/1857/D](https://codeforces.com/problemset/problem/1857/D)

### 2. Approach Explanation

The core idea of the solution is to transform the edge condition and identify a simple criterion for determining strong vertices.  The provided code does the following:

1. **Transformation of the Edge Condition:** The condition `a[u] - a[v] >= b[u] - b[v]` is rearranged to `a[u] - b[u] >= a[v] - b[v]`.

2. **Creation of Array c:** A new array `c` is created where `c[r] = a[r] - b[r]` for `1 <= r <= n`.  Now, the edge condition is simplified to: there is an edge from `u` to `v` if and only if `c[u] >= c[v]`.

3. **Identification of Strong Vertices:** A vertex `u` is strong if it can reach all other vertices.  From the simplified edge condition, it's evident that a vertex `u` can reach all other vertices if and only if `c[u]` is the maximum value in the `c` array.  Why?

    *   If `c[u]` is the maximum, then for any other vertex `v`, `c[u] >= c[v]`, so there is an edge from `u` to `v`.
    *   If `c[u]` is *not* the maximum, then there exists a vertex `v` such that `c[v] > c[u]`.  Thus, there will be no edge from `u` to `v`. And vertex `u` will not reach the largest element.

4. **Implementation:**  The code finds the maximum value in the `c` array and then iterates through the array, collecting the indices of all elements that equal the maximum value. These indices represent the strong vertices.

### 3. Key Insights and Algorithmic Techniques Used

*   **Problem Transformation:** The key insight is to transform the given edge condition into a more manageable form by rearranging the terms and creating the `c` array. This simplification is crucial for understanding the structure of the graph.
*   **Graph Reduction to Array Analysis:**  The problem is cleverly transformed from a graph problem to a simple array problem (finding the maximum element and its occurrences).
*   **Greedy Approach (Implicit):** By focusing on the maximum value in the `c` array, we implicitly use a greedy approach.  We immediately identify the vertices that can reach all others without needing to perform any explicit graph traversals (like BFS or DFS).
*   **Understanding Reachability:** The simplified edge condition `c[u] >= c[v]` directly defines reachability. If `c[u]` is maximal, `u` can reach all vertices.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Reading input: O(n)
    *   Calculating `c` array: O(n)
    *   Finding the maximum value in `c`: O(n)
    *   Finding the indices of the maximum values: O(n)
    *   Therefore, the overall time complexity is O(n) per test case.  Since there are `t` test cases, the total time complexity is O(t * n).

*   **Space Complexity:**
    *   `a` array: O(n)
    *   `b` array: O(n)
    *   `c` array: O(n)
    *   `indexes` vector: O(n) in the worst case (when all vertices are strong)
    *   Therefore, the overall space complexity is O(n) per test case.

### 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a common optimization technique in C++ competitive programming to speed up input/output by disabling synchronization between the C and C++ standard streams and unlinking `cin` from `cout`.
*   **Using `#define int long long`**: This is a common trick to prevent integer overflow issues.  It redefines `int` as `long long` for the entire code.  This makes sure no overflows will happen for numbers that may be up to 10^9 in value. (The problem statement would need to specify the input constraints for this to be vital.)
*   **Clear Code Structure:** The code is well-structured and easy to follow, with descriptive variable names and comments explaining the logic.

### 6. Edge Cases Handled

The code implicitly handles the following edge cases:

*   **Empty Graph (n = 0):** The loops will not execute, and no output will be produced (which is acceptable). The problem specification needs to be specific.
*   **All Vertices are Strong:** If all elements in the `c` array are equal, then all vertices will be strong, and the code will correctly identify them.
*   **Single Vertex (n = 1):** A single vertex is always considered strong because it can "reach" all other vertices (there are none). The code correctly handles this case.

In summary, the solution efficiently solves the "Strong Vertices" problem by transforming the graph problem into a simple array problem, leveraging a greedy approach, and providing a clean and well-documented implementation. The key takeaway is how problem transformation can dramatically simplify complex scenarios.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: strongVertices
// URL: https://codeforces.com/problemset/problem/1857/D
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n + 1), b(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> a[r];
        for (int r = 1; r <= n; r++)
            cin >> b[r];

        // there is an edge from u to v in the graph where 1 <= u != v <= n iff
        // a[u] - a[v] >= b[u] - b[v]
        // iff a[u] - b[u] >= a[v] - b[v]
        // iff c[u] >= c[v]

        vector<int> c(n + 1);
        for (int r = 1; r <= n; r++)
            c[r] = a[r] - b[r];

        // the largest element of c will have vertices to all of the other indexes, i.e, to all other
        // possible nodes
        // the next largest element won't be able to reach the largest element anyhow
        // since it would have edges to only smaller elements and any smaller elements will have edges to other smaller elements

        // so, only the maximal vertices will be strong

        int maxi = c[1];
        for (int r = 1; r <= n; r++)
            maxi = max(maxi, c[r]);

        int count = 0;
        vector<int> indexes;
        for (int r = 1; r <= n; r++)
            if (c[r] == maxi)
                indexes.push_back(r), count++;
        cout << count << endl;
        for (int r : indexes)
            cout << r << " ";
        cout << endl;
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-31 15:30:22*
