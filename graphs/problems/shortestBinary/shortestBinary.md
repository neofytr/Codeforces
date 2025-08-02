# shortestBinary

```markdown
## Shortest Path in Binary Matrix - Documentation

This document provides a comprehensive analysis of the provided C++ code that solves the "Shortest Path in Binary Matrix" problem.

**1. Problem Description:**

The problem (available on LeetCode: [https://leetcode.com/problems/shortest-path-in-binary-matrix/description/](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/)) requires finding the shortest path from the top-left cell (0, 0) to the bottom-right cell (n-1, n-1) in a square binary matrix (grid) where:

*   `0` represents a free cell (passable).
*   `1` represents a blocked cell (unpassable).
*   The path can only traverse through free cells (0s).
*   Movement is allowed in 8 directions (horizontally, vertically, and diagonally).
*   The length of the path is the number of cells visited.
*   If no such path exists, return -1.

**2. Approach Explanation:**

The code implements a Breadth-First Search (BFS) algorithm to find the shortest path. Here's a breakdown:

1.  **Initialization:**
    *   It checks if the start cell (0, 0) or the end cell (n-1, n-1) is blocked (value is 1). If either is blocked, it returns -1 because no path is possible.
    *   A queue `que` is used to store cells to be visited, initialized with the starting cell (0, 0).
    *   A 2D boolean vector `vis` is used to keep track of visited cells, initialized to `false` for all cells. The starting cell is marked as visited.
    *   `dx` and `dy` arrays store the 8 possible directions of movement.
    *   `depth` variable keeps track of the current path length, starting from 1 (as the starting cell is already counted).

2.  **BFS Traversal:**
    *   The `while` loop continues as long as the queue is not empty.
    *   In each iteration (level of BFS), it processes all the cells at the current `depth`.
    *   The inner `while` loop iterates through all cells currently in the queue (nodes at the same distance from the start node).
    *   For each cell `(y, x)` dequeued from the queue:
        *   It checks if the cell is the target cell (n-1, n-1). If it is, the current `depth` is returned as the shortest path length. **(Important: Target check inside the current level processing loop)**
        *   It iterates through the 8 possible directions (using `dx` and `dy` arrays).
        *   For each neighbor `(ny, nx)`:
            *   It checks if the neighbor is within the grid boundaries (`ny >= 0 && ny < n && nx >= 0 && nx < n`).
            *   It checks if the neighbor has not been visited (`!vis[ny][nx]`).
            *   It checks if the neighbor is a free cell (`!grid[ny][nx]`).
            *   If all conditions are met, the neighbor is marked as visited, added to the queue, and will be processed in the next BFS level.
    *   After processing all cells at the current `depth`, the `depth` is incremented.

3.  **No Path Found:**
    *   If the queue becomes empty and the target cell has not been reached, it means there is no valid path.  The function returns -1.

**3. Key Insights and Algorithmic Techniques:**

*   **Breadth-First Search (BFS):** BFS is the optimal algorithm for finding the shortest path in an unweighted graph (or a graph where all edges have the same weight, like this problem).  BFS explores the graph layer by layer, guaranteeing that the first time the target node is reached, it's via the shortest path.
*   **8-Directional Movement:** The `dx` and `dy` arrays efficiently represent the 8 possible movement directions, making the code concise and readable.
*   **Visited Matrix:** The `vis` matrix is crucial to avoid cycles and ensure that the algorithm explores each cell at most once, optimizing the search process and preventing infinite loops.
*   **Target Check within Level Processing:** The critical optimization is to check for the target inside the inner `while (sz--)` loop, which is processing the current level/depth. Checking for the target *after* enqueueing the neighbor cell may not guarantee the shortest path if there are other paths to the target one level later. Additionally, checking the target inside the `for` loop would lead to incorrect result when `n = 1`.

**4. Time and Space Complexity:**

*   **Time Complexity:** O(N<sup>2</sup>), where N is the size of the grid. In the worst case, BFS might visit every cell in the grid.
*   **Space Complexity:** O(N<sup>2</sup>).  In the worst case, the queue could potentially hold all the cells in the grid. The `vis` matrix also takes O(N<sup>2</sup>) space.

**5. Important Code Patterns or Tricks Used:**

*   **`dx` and `dy` arrays for 8-directional movement:** This is a common pattern used in grid-based problems to efficiently represent and iterate over neighboring cells.
*   **Using `queue` for BFS:** The standard `queue` data structure from the STL is ideal for implementing BFS.
*   **`vis` matrix for cycle detection:** This prevents infinite loops and ensures that each cell is visited only once.
*   **`auto [y, x] = que.front();`:** This C++17 feature provides a convenient way to unpack the coordinates from the queue element.

**6. Edge Cases Handled:**

*   **Blocked Start or End Cell:** The code explicitly checks if the starting cell (0, 0) or the ending cell (n-1, n-1) is blocked.  If either is blocked, it immediately returns -1.
*   **No Path Exists:** If the BFS traversal completes without finding the target cell (queue becomes empty), the code returns -1, indicating that no valid path exists.
*   **n=1 case:** It correctly handles the case where the input grid is of size 1x1. The target cell check within the current depth guarantees correctness.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

// Problem: shortestBinary
// URL: https://leetcode.com/problems/shortest-path-in-binary-matrix/description/
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
            return -1;

        queue<pair<int, int>> que;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        que.push({0, 0});
        vis[0][0] = true;
        int depth = 1;

        while (!que.empty()) {
            int sz = que.size();
            while (sz--) {
                auto [y, x] = que.front();
                que.pop();
                if (y == n - 1 && x == n - 1) // checking and returning here is much safer and correct; what will happen if there is only one element, we can't check in the loop
                    return depth;
                for (int dir = 0; dir < 8; ++dir) {
                    int ny = y + dy[dir], nx = x + dx[dir];
                    if (ny >= 0 && ny < n && nx >= 0 && nx < n && !vis[ny][nx] && !grid[ny][nx]) {
                        vis[ny][nx] = true;
                        que.push({ny, nx});
                        /*

                        if (ny == n-1 && nx == n-1) {
                            return depth + 1;
                        }
                            
                        This will fail only for n = 1
                        */
                    }
                }
            }
            depth++;
        }

        return -1;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> grid[row][col];
        }
    }

    Solution sol;
    cout << sol.shortestPathBinaryMatrix(grid) << endl;
    return EXIT_SUCCESS;
}
```

---
*Documentation generated on 2025-08-02 14:41:04*
