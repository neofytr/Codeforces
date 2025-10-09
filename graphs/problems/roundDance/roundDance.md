# roundDance

```markdown
## Code Documentation: Round Dance Problem (Codeforces 1833E)

This document provides a comprehensive analysis of the provided C++ code, which solves the "Round Dance" problem (Problem E) from Codeforces Contest 1833 ([https://codeforces.com/contest/1833/problem/E](https://codeforces.com/contest/1833/problem/E)).

### 1. Problem Description (Inferred)

The problem describes a round dance where `n` people stand in a circle. Each person `i` holds the hand of exactly one other person `j`.  The input provides, for each person `i`, the person `j` they are holding hands with.  The goal is to determine the minimum and maximum number of circles that can be formed.

A circle is defined as a group of people where each person holds the hand of exactly two other people in the group, forming a closed loop.  A linear chain is a group where some people may only hold one person's hand.  When the graph has linear chains, we are allowed to connect some ends of linear chains to form closed circles. The constraints require finding the minimal and maximal number of circles that can be formed given `n` people and the connections between them.

### 2. Approach Explanation

The code uses a graph-based approach to solve the problem.  The main idea is to:

1.  **Represent the dance as a graph:**  The `graph` variable is an adjacency list where `graph[i]` contains the indices of the people holding hands with person `i`.
2.  **Identify connected components:** The code iterates through each person (`node`) and uses a Breadth-First Search (BFS) to explore the connected component to which the node belongs.
3.  **Classify each component as a cycle or a linear chain:**  During the BFS, a `cycle` flag is maintained. If, within a connected component, every person holds exactly two hands (i.e., the degree of each node is 2), then the component is a cycle. Otherwise, it is considered a linear chain.
4.  **Calculate the minimum and maximum number of circles:**
    *   **Minimum:** If there are no linear chains (`linearCount == 0`), the minimum number of circles is simply the number of cycles (`cycleCount`). If there are linear chains, we need at least one extra circle because we can connect all the linear chains into one big circle. So, the minimum is `cycleCount + 1` if `linearCount > 0`, otherwise `cycleCount`.
    *   **Maximum:** The maximum number of circles is obtained by considering each linear chain as a separate circle. Hence, the maximum is `cycleCount + linearCount`.

### 3. Key Insights and Algorithmic Techniques Used

*   **Graph Representation:** Using an adjacency list (`vector<vector<int>> graph`) is efficient for representing the relationships between people.
*   **Breadth-First Search (BFS):**  BFS is used to traverse the graph and identify connected components.  It ensures that all reachable nodes from a starting node are visited.
*   **Connected Component Analysis:** The core idea is to decompose the problem into independent connected components.  This allows us to analyze each component individually.
*   **Cycle Detection by Degree:** The code smartly identifies cycles by checking the degree of each node within a connected component.  If all nodes in a component have a degree of 2, it's a cycle. This avoids complex cycle detection algorithms like DFS with back edges.
*   **Avoiding Duplicate Edges:** The `mp` (map) is used to avoid adding duplicate edges to the graph when processing the input. This ensures that each connection is only considered once. Without this check, the degree computation could be wrong and classification into a cycle or chain might be flawed.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Reading input and constructing the graph: O(n)
    *   BFS traversal of each connected component: O(n) in the worst case, since we visit each node and edge at most once.
    *   Calculating minimum and maximum circles: O(1)

    Therefore, the overall time complexity is **O(n)** per test case.  With `t` test cases, the total time complexity is O(t\*n).

*   **Space Complexity:**
    *   `graph`: O(n) to store the adjacency list.
    *   `vis`: O(n) to keep track of visited nodes during BFS.
    *   `que`: O(n) in the worst case, if all nodes are in the same connected component.
    *   `mp`: O(n) to store edge information and prevent duplication.

    Therefore, the overall space complexity is **O(n)**.

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:**  This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large numbers or multiplication. It's a safety measure that trades a small amount of memory for increased range.  The corresponding `int32_t main()` ensures compatibility.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  This optimization disables synchronization between the C++ standard input/output streams and the C standard input/output streams, and it unties `cin` from `cout`.  This significantly speeds up input and output operations, which is crucial for performance in competitive programming.
*   **Using a `map` to avoid duplicate edges:** The `mp` (map) ensures that each undirected edge between two people is only added to the graph once. This is essential for correctly determining the degree of each node and classifying connected components.
*   **Clear and concise variable names:** Although brief, variable names like `linearCount`, `cycleCount`, `vis`, and `graph` are sufficiently descriptive to understand their purpose.

### 6. Edge Cases Handled

*   **Disconnected Graph:** The code correctly handles the case where the graph is not connected, as it iterates through all nodes and performs BFS on each unvisited node.  This ensures that all connected components are processed.
*   **Self-loops:**  The edge case of self-loops (a person holding their own hand) isn't explicitly handled, but if they exist, they would be considered linear chains since the degree of that node would only be 1.
*   **Duplicate Edges:** As noted above, the `mp` map is crucial for preventing duplicate edges which can skew cycle detection.

This documentation provides a comprehensive understanding of the code's functionality, algorithmic approach, complexity, and important considerations for solving the "Round Dance" problem.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: roundDance
// URL: https://codeforces.com/contest/1833/problem/E
// Difficulty: hard
// Tags: 
// Strategy: 

void solve() {
    int n;
    cin >> n;

    int v;
    vector<vector<int>> graph(n + 1);
    map<pair<int, int>, bool> mp;
    for (int r = 1; r <= n; r++) {
        cin >> v;
        if (mp[{v, r}] || mp[{r, v}])
            continue;
        graph[r].push_back(v), graph[v].push_back(r);
        mp[{r, v}] = true;
    }

    queue<int> que;
    vector<bool> vis(n + 1, false);

    int linearCount = 0;
    int cycleCount = 0;

    for (int node = 1; node <= n; node++)
        if (!vis[node]) {
            int src = node;
            vis[src] = true;

            bool cycle = true;
            que.push(src);
            while(!que.empty()) {
                int x = que.front();
                que.pop();

                if (graph[x].size() != 2)
                    cycle = false;

                for (int v : graph[x])
                    if (!vis[v])
                        vis[v] = true, que.push(v);
            }

            if (!cycle)
                linearCount++;
            else 
                cycleCount++;
        }

    int mini = cycleCount + (linearCount ? 1 : 0);
    int maxi = cycleCount + linearCount;
    cout << mini << " " << maxi << endl; 
    cycleCount = 0;
    linearCount = 0;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }    
    return 0;
}
```

---
*Documentation generated on 2025-10-09 20:03:12*
