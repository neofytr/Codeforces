# AKBAR

```markdown
## Competitive Programming Solution Documentation: AKBAR (SPOJ)

This document provides a comprehensive analysis of the provided C++ code, which solves the AKBAR problem on SPOJ ([https://www.spoj.com/problems/AKBAR/](https://www.spoj.com/problems/AKBAR/)).

### 1. Problem Description (Inferred)

The AKBAR problem likely involves a graph where nodes represent cities and edges represent roads between them.  There are `n` cities, `r` roads connecting them, and `m` Akbar's soldiers placed in certain cities with a certain strength (range). The goal is to determine if every city is occupied by exactly one soldier, where an occupation means the soldier can reach the city within their strength range. The "strength" of a soldier determines the number of hops (edges traversed) they can make from their initial city. If any city is unoccupied, or if any city is occupied by more than one soldier, the answer is "No". Otherwise, the answer is "Yes".

### 2. Approach Explanation

The code utilizes a Breadth-First Search (BFS) approach to simulate the spread of Akbar's soldiers through the cities.  For each soldier, a BFS is performed from the soldier's city, limited by their strength. The `vis` array is crucial:

- `vis[i] == -1`: City `i` is unvisited.
- `vis[i] == k`: City `i` is visited by soldier `k`.

The algorithm iterates through each soldier:

1. **Check for Pre-Occupation:**  Before starting a BFS for a soldier, it checks if the soldier's starting city (`k`) is already occupied. If it is, the answer is immediately "No" because it means multiple soldiers would occupy the same location.

2. **BFS Exploration:** A BFS is initiated from the soldier's city. The BFS maintains a queue of cities to explore. The `currS` variable tracks the current strength level (number of hops from the source). The BFS continues as long as the queue is not empty and the `currS` is less than or equal to the soldier's maximum strength (`maxS`).

3. **City Visitation:** For each city visited during the BFS:
   - If the city is unvisited (`vis[v] == -1`), it's marked as visited by the current soldier (`vis[v] = k`), and the city is added to the queue for further exploration.
   - If the city is already visited by a *different* soldier (`vis[v] != -1 && vis[v] != k`), it means multiple soldiers are occupying the same city, and the answer is immediately "No".

4. **Verification:** After processing all soldiers, the code iterates through all cities (nodes). If any city remains unvisited (`vis[node] == -1`), it means no soldier could reach it, and the answer is "No".

5. **Output:** If all cities are visited by exactly one soldier, the answer is "Yes".

### 3. Key Insights and Algorithmic Techniques Used

- **Breadth-First Search (BFS):**  BFS is the fundamental algorithm used to simulate the spread of the soldiers' influence. BFS guarantees that cities are visited in increasing order of distance from the source.
- **Visitation Tracking (vis array):** The `vis` array is critical for keeping track of which cities are occupied and by which soldier. It also efficiently prevents revisits by the same soldier within the strength limit, reducing redundant exploration.
- **Early Exit Optimization:** The code includes crucial optimizations by immediately returning "No" if a city is found to be occupied by multiple soldiers or if a soldier attempts to start from an already occupied city.  This avoids unnecessary computation and improves efficiency.
- **Strength Limit Enforcement:**  The `currS` and `maxS` variables ensure that the BFS exploration for each soldier respects the strength limit.

### 4. Time and Space Complexity Analysis

- **Time Complexity:**
    - Building the graph: O(r)
    - BFS for each soldier: O(m * (V + E)) where V is the number of vertices(cities) and E is the number of edges(roads) within the range of the soldiers' strength. In the worst case, the BFS might visit all nodes and edges.
    - Verification Loop: O(n)
    - Overall, the dominant factor is the BFS loop, making the time complexity approximately O(r + m * (n + r)).  Note that, if the maximum strength value is significantly smaller than n, the complexity could be lower since the BFS will explore a smaller portion of the graph.

- **Space Complexity:**
    - Graph: O(n + r)  (adjacency list)
    - `vis` array: O(n)
    - Queue: O(n) in the worst case (if all nodes are reachable within the strength limit).
    - Overall, the space complexity is O(n + r).

### 5. Important Code Patterns or Tricks Used

- **`#define int long long`:**  This macro is a common trick in competitive programming to prevent integer overflow issues, especially when dealing with large test cases. It effectively makes `int` equivalent to `long long`.  However, always be mindful of the potential memory impact when changing the size of the `int` data type.

- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to disable synchronization between C++ standard input/output streams and C standard input/output streams and also untie `cin` from `cout`.  This significantly speeds up input/output operations, which is essential for problems with tight time limits.

- **Early return for "No" cases:**  The code immediately returns "No" whenever a conflict is detected (city visited by multiple soldiers or starting city already visited), avoiding unnecessary computations. This optimization is key to meeting time constraints.

### 6. Edge Cases Handled

- **Pre-Occupied Starting City:** The code explicitly checks if a soldier's starting city is already occupied before initiating the BFS. This is a crucial edge case that must be handled correctly.
- **Cities Not Reachable:** The code checks after processing all soldiers to see if any city remains unvisited. If so, it means that not all cities are occupied, and the answer is "No."
- **Multiple Soldiers Occupying the Same City:**  The BFS exploration ensures that no city is visited by multiple soldiers.
- **Empty Graph:** If `r` is 0, the graph is empty.  The code will still correctly process this case, as the BFS will not explore any neighbors.
- **Soldier strength of 0**: If a soldier has strength 0, they only occupy their starting city, and the BFS effectively doesn't run beyond the source.

This detailed analysis provides a comprehensive understanding of the AKBAR problem solution. The combination of BFS, careful visitation tracking, and early exit optimizations allows the code to efficiently determine whether all cities are occupied by exactly one soldier.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: AKBAR
// URL: https://www.spoj.com/problems/AKBAR/
// Difficulty: medium
// Tags: 
// Strategy: 

void solve() {
    int n, r, m;
        cin >> n >> r >> m;

        int u, v;
        vector<vector<int>> graph(n + 1);
        while(r--)
            cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

        vector<int> vis(n + 1, -1);
        queue<int> que;
        while(m--) {
            int k, maxS;
            cin >> k >> maxS;

            int currS = 0;
            int src = k;
            if (vis[src] != -1) {
                cout << "No\n";
                return;
            }
            vis[src] = k;
            que.push(src);

            while(!que.empty()) {
                if (currS >= maxS)
                    break;
                int sz = que.size();
                while(sz--) {
                    int x = que.front();
                    que.pop();

                    for (int v : graph[x])
                        if (vis[v] == -1)
                            vis[v] = k, que.push(v);
                        else if (vis[v] != k) {
                            cout << "No\n";
                            return;
                        }
                }
                currS++;
            }

            while(!que.empty())
                que.pop();
        }

    for (int node = 1; node <= n; node++)
        if (vis[node] == -1) {
            cout << "No\n";
            return;
        }
    cout << "Yes\n";
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
*Documentation generated on 2025-10-04 13:43:23*
