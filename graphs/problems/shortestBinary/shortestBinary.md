# shortestBinary

```markdown
## Documentation: Shortest Path in Binary Matrix

This document describes a C++ solution to the "Shortest Path in Binary Matrix" problem on LeetCode ([https://leetcode.com/problems/shortest-path-in-binary-matrix/description/](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/)).

### 1. Problem Description

Given an *n x n* binary matrix `grid`, where `0` represents an empty cell and `1` represents a blocked cell, find the length of the shortest clear path from the top-left cell (0, 0) to the bottom-right cell (n - 1, n - 1). A clear path is a path where all the cells are `0`, and you can move to one of the eight adjacent cells (including diagonals). If there is no such path, return `-1`. The length of the path is the number of cells in the path.

### 2. Approach Explanation

The solution utilizes a Breadth-First Search (BFS) algorithm to find the shortest path.  BFS is suitable because it explores the graph layer by layer, guaranteeing that the first time the target cell is reached, it's via the shortest path. The algorithm can be summarized as follows:

1.  **Initialization:**
    *   Check if the starting cell `grid[0][0]` or the target cell `grid[n-1][n-1]` is blocked (equal to 1). If so, return `-1` because no path exists.
    *   Create a queue `que` to store the cells to be visited.
    *   Create a `vis` (visited) matrix to keep track of visited cells to avoid cycles.
    *   Initialize the queue with the starting cell (0, 0) and mark it as visited.
    *   Initialize `depth` to 1 (representing the starting cell).

2.  **BFS Traversal:**
    *   While the queue is not empty:
        *   Process all the cells at the current level (indicated by `sz = que.size()`).
        *   For each cell (y, x) in the current level:
            *   If the cell is the target cell (n - 1, n - 1), return the current `depth`.
            *   Explore all 8 adjacent cells (ny, nx):
                *   Check if the new cell (ny, nx) is within the bounds of the grid (ny >= 0 && ny < n && nx >= 0 && nx < n).
                *   Check if the new cell has not been visited (`!vis[ny][nx]`) and is not blocked (`!grid[ny][nx]`).
                *   If all conditions are met, mark the new cell as visited and add it to the queue.
        *   Increment `depth` to represent the next level in the search.

3.  **No Path Found:**
    *   If the queue becomes empty and the target cell has not been reached, return `-1`, indicating that no clear path exists.

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):**  BFS is crucial for finding the shortest path in an unweighted graph (or a graph where all edges have the same weight, as is the case here). It explores the graph level by level, so the first path found is guaranteed to be the shortest.
*   **Visited Matrix:**  The `vis` matrix is essential to prevent infinite loops and to ensure that each cell is visited at most once, optimizing the search.
*   **8-Directional Movement:** The problem requires moving in all 8 directions (up, down, left, right, and diagonals). The `dx` and `dy` arrays conveniently represent the offsets for these directions.
*   **Early Exit:** The solution incorporates an early exit check. If the start or end cell is a `1`, then it immediately exits. This is an important optimization.
*   **Level-by-Level Processing:** The inner `while(sz--)` loop allows processing nodes level by level in BFS, which is key to correctly tracking the path length/depth.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n<sup>2</sup>), where *n* is the size of the grid. In the worst case, we might need to visit every cell in the grid once. The BFS operations (queue operations and neighbor exploration) take constant time per cell.
*   **Space Complexity:** O(n<sup>2</sup>) due to the queue `que` and the visited matrix `vis`. In the worst case, the queue could hold all the cells in the grid.

### 5. Important Code Patterns or Tricks Used

*   **`dx` and `dy` arrays:**  These arrays are a common trick for simplifying the exploration of neighboring cells in grid-based problems. They eliminate the need to write repetitive code for each direction.
*   **`auto [y, x] = que.front();`:** This is a convenient C++17 feature (structured binding) to unpack the `pair` retrieved from the queue, making the code more readable.
*   **Level Order Traversal with Size:** The `sz = que.size()` and the inner `while(sz--)` loop implement level-order traversal. This pattern correctly tracks the distance (depth) from the starting node.  Without it, the `depth` variable would not be incremented correctly reflecting the path length.

### 6. Edge Cases Handled

*   **Blocked Starting or Ending Cell:** The solution explicitly checks if the starting cell or the ending cell is blocked.  If either is blocked, it immediately returns -1.
*   **No Path Exists:** If the BFS traversal completes without finding a path to the target cell (i.e., the queue becomes empty), the solution returns -1, indicating that no path exists.
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
*Documentation generated on 2025-08-02 14:40:16*
