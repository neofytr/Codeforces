# wordLadder

```markdown
## Word Ladder Problem Documentation

This document provides a comprehensive analysis of the provided C++ code, which solves the "Word Ladder" problem.

### 1. Problem Description

The "Word Ladder" problem, as defined on LeetCode (https://leetcode.com/problems/word-ladder/description/), asks us to find the length of the shortest transformation sequence from a `beginWord` to an `endWord`, using a given `wordList`. The transformation must follow these rules:

1.  Only one letter can be changed at a time.
2.  Each transformed word must exist in the `wordList`.

If no such transformation sequence exists, the function should return 0.

### 2. Approach Explanation

The provided code uses a graph-based Breadth-First Search (BFS) approach to find the shortest path. Here's a breakdown:

1.  **Graph Construction:**  The `wordList` and `beginWord` are treated as nodes in a graph.  An edge exists between two words if they differ by only one letter (are neighbors).
2.  **Adjacency Check:** The `isNeighbour` function efficiently determines if two words are neighbors by comparing them character by character.
3.  **Handling `beginWord`:** The code checks if the `beginWord` is present in `wordList`. If not, it's treated as an extra node (`n`) and its neighbors are determined.  This ensures we can always start the BFS from the `beginWord`.
4.  **Handling `endWord`:** If the `endWord` is not present in the `wordList`, the code immediately returns 0 because a transformation is impossible.
5.  **Breadth-First Search (BFS):** BFS is used to traverse the graph starting from the `beginWord` (source).  The distance from the source to each node is tracked.
6.  **Result:** The distance from the `beginWord` to the `endWord` is returned, incremented by 1 to include the `beginWord` itself in the transformation count.

### 3. Key Insights and Algorithmic Techniques Used

*   **Graph Representation:**  Representing the problem as a graph allows us to leverage graph traversal algorithms like BFS to find the shortest path.
*   **Breadth-First Search (BFS):** BFS is crucial for finding the *shortest* path in an unweighted graph. The algorithm explores all neighbors at the current depth before moving to the next depth, guaranteeing that the first time the `endWord` is reached, it's via the shortest possible path.
*   **Adjacency List:** The `graph` is represented using an adjacency list (`vector<vector<int>>`), which is efficient for sparse graphs (graphs where most nodes are not connected to each other). In this case, the number of neighbors for each word is likely to be relatively small compared to the total number of words.
*   **Virtual Node for `beginWord`:** The code intelligently handles the case where the `beginWord` is not in the `wordList` by adding a "virtual" node representing it and connecting it to its neighbors in the `wordList`.  This avoids special-case handling during the BFS.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   `isNeighbour`: O(L), where L is the length of the words.
    *   Graph Construction: O(N^2 * L), where N is the number of words in `wordList`. This comes from the nested loops comparing each pair of words.
    *   BFS: O(V + E), where V is the number of vertices (words + potentially the beginWord) and E is the number of edges. In the worst case, E could be close to V^2, but often it's significantly less.  The BFS itself is O(N + E) or approximately O(N^2) if we assume a dense graph.

    Therefore, the overall time complexity is dominated by the graph construction: **O(N^2 * L)**.
*   **Space Complexity:**
    *   `graph`: O(V + E), where V is the number of vertices (words + potentially the beginWord) and E is the number of edges.  This can be O(N^2) in the worst case.
    *   `vis` and `dist`: O(N), where N is the number of words.
    *   Queue: O(N) in the worst case.

    Therefore, the overall space complexity is **O(N^2)** in the worst case, due to the adjacency list representation of the graph.

### 5. Important Code Patterns or Tricks Used

*   **Adjacency List Representation:** Using an adjacency list is very common when dealing with graph problems, especially when the graph is sparse.
*   **`INT_MAX` for Unreachable Nodes:** Using `INT_MAX` as the initial distance value in the `dist` vector is a standard way to represent unreachable nodes in BFS-based shortest path algorithms.
*   **`isNeighbour` Function:**  Encapsulating the neighbor check logic into a separate function makes the code more readable and maintainable.
*   **Handling Edge Cases:** Properly handling cases where the `beginWord` or `endWord` are not in the `wordList` is crucial for robustness.

### 6. Edge Cases Handled

*   **`endWord` Not in `wordList`:**  The code explicitly checks if the `endWord` is present in the `wordList`. If not, it returns 0 because no transformation is possible.
*   **`beginWord` Not in `wordList`:** The code handles the case where the `beginWord` is not in the `wordList` by creating a virtual node and connecting it to its neighbors.  This allows the BFS to start correctly.
*   **No Transformation Sequence Exists:** If the BFS completes and the `endWord` is not reachable (i.e., `dist[end] == INT_MAX`), the code returns 0, indicating that no transformation sequence exists.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

// Problem: wordLadder
// URL: https://leetcode.com/problems/word-ladder/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  private:
    bool isNeighbour(string &u, string &v) {
        int n = (int)u.size();
        int count = 0;
        for (int index = 0; index < n; index++) {
            if (u[index] != v[index])
                count++;
            if (count > 1)
                return false;
        }
        return count == 1;
    }

  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        int n = (int)wordList.size();
        vector<vector<int>> graph(n + 1);
        bool found = false;
        int src = -1;
        bool foundEnd = false;
        int end = -1;

        for (int u = 0; u < n; u++) {
            if (wordList[u] == beginWord) {
                found = true;
                src = u;
            }
            if (wordList[u] == endWord) {
                foundEnd = true;
                end = u;
            }
            for (int v = u + 1; v < n; v++) {
                if (isNeighbour(wordList[u], wordList[v])) {
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
            }
        }

        if (!found) {
            for (int v = 0; v < n; v++) {
                if (isNeighbour(beginWord, wordList[v])) {
                    graph[n].push_back(v);
                    graph[v].push_back(n); // bidirectional
                }
            }
            src = n;
        }

        if (!foundEnd) {
            return 0;
        }

        vector<bool> vis(n + 1, false);
        vector<int> dist(n + 1, INT_MAX);
        queue<int> que;

        dist[src] = 0;
        vis[src] = true;
        que.push(src);

        while (!que.empty()) {
            int node = que.front();
            que.pop();
            for (int v : graph[node]) {
                if (!vis[v]) {
                    vis[v] = true;
                    dist[v] = dist[node] + 1;
                    que.push(v);
                }
            }
        }

        if (dist[end] == INT_MAX)
            return 0;
        return dist[end] + 1; // add 1 to include the beginWord
    }
};

```

---
*Documentation generated on 2025-07-31 00:22:41*
