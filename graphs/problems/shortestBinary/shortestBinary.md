# shortestBinary

```markdown
## Shortest Path in Binary Matrix - Problem Analysis and Solution

### 1. Problem Description

The problem, as indicated in the code comments and the linked LeetCode URL ([https://leetcode.com/problems/shortest-path-in-binary-matrix/description/](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/)), is "Shortest Path in Binary Matrix".  The task is to find the length of the shortest path from the top-left cell (0, 0) to the bottom-right cell (n-1, n-1) in a square binary matrix (grid) of size n x n.  The path must satisfy the following conditions:

*   The path can only traverse cells with a value of 0 (representing an open cell).
*   The path can move in 8 directions (up, down, left, right, and diagonally).
*   The length of the path is the number of cells visited.

If no such path exists, the function should return -1.

### 2. Approach Explanation

The solution employs a Breadth-First Search (BFS) algorithm to find the shortest path.  Here's a breakdown:

1.  **Initialization:**
    *   `dist[i][j]` array:  A 2D array of size `n x n` is initialized with `INT_MAX` representing the shortest distance from the source (0, 0) to each cell (i, j).  `INT_MAX` means initially, no path is known to any cell.
    *   `que`: A queue is used to store the cells to be visited during the BFS traversal. It contains pairs of (row, col) coordinates.
    *   `vis[i][j]` array: A 2D boolean array `vis[i][j]` is used to keep track of visited cells.  It prevents revisiting cells and thus avoids infinite loops.
    *   Check for initial blockage: If the starting cell `grid[0][0]` is 1, there's no path, and the function cannot even start searching.

2.  **BFS Traversal:**
    *   The algorithm starts by adding the source cell (0, 0) to the queue and marking it as visited (`vis[0][0] = true`).  The initial distance from the source to itself is set to 0 (`dist[0][0] = 0`).
    *   The `while` loop continues as long as the queue is not empty. Inside the loop:
        *   The `s` variable gets the current queue size to process all elements at the same "level" before advancing further, ensuring shortest-path logic.
        *   The cell at the front of the queue (`que.front()`) is dequeued.
        *   The algorithm iterates through all 8 possible neighbors of the current cell using nested loops.
        *   For each neighbor:
            *   It checks if the neighbor is within the grid boundaries (`x >= 0 && x < n && y >= 0 && y < n`).
            *   It ensures the neighbor is not the current cell itself (`!(x == nodeX && y == nodeY)`).
            *   It checks if the neighbor is an open cell (`!grid[y][x]`).
            *   It checks if the neighbor has not been visited before (`!vis[y][x]`).
            *   If all conditions are met, the neighbor is marked as visited (`vis[y][x] = true`), its distance is updated (`dist[y][x] = dist[nodeY][nodeX] + 1`), and it is added to the queue for further exploration.

3.  **Result:**
    *   After the BFS traversal is complete, the algorithm checks the distance to the destination cell (`dist[n-1][n-1]`).
    *   If the distance is still `INT_MAX`, it means there is no path to the destination, and the function returns -1.
    *   Otherwise, it returns `dist[n-1][n-1] + 1`.  The `+ 1` is crucial because the `dist` array stores the number of *edges* (moves) from the starting cell, not the total number of cells visited. We need the number of *cells* in the path.

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):** BFS is the perfect algorithm for finding the shortest path in an unweighted graph (or a graph where all edges have the same weight). In this case, each valid move (to an adjacent cell) has a weight of 1.  BFS guarantees finding the shortest path because it explores nodes level by level.
*   **Distance Tracking:**  The `dist` array efficiently stores the minimum distance from the source to each cell found so far during the BFS traversal.
*   **Visited Set:** The `vis` array is essential to prevent cycles and redundant computations. Without it, the algorithm would potentially loop infinitely.
*   **8-Directional Movement:** The nested loops `for (int x = nodeX - 1; x <= nodeX + 1; x++)` and `for (int y = nodeY - 1; y <= nodeY + 1; y++)` efficiently handle all eight possible directions.

### 4. Time and Space Complexity Analysis

*   **Time Complexity: O(N^2)**, where N is the side length of the square matrix.  In the worst case, BFS might visit every cell in the grid. The nested loops inside the main while loop iterate a constant number of times (8 neighbors).
*   **Space Complexity: O(N^2)**.  The space is primarily used by the `dist` and `vis` arrays, both of size `N x N`. The queue `que` can, in the worst case, hold all the nodes of the grid.

### 5. Important Code Patterns or Tricks Used

*   **Using `INT_MAX` for Initialization:**  Initializing the `dist` array with `INT_MAX` is a common technique in shortest-path algorithms. It allows us to easily identify unvisited or unreachable nodes.
*   **Visited Array ( `vis`) Importance:** This is a standard trick in graph traversals. Without the visited array, the algorithm would be stuck in a loop, and would probably have a StackOverflow error if the input size is large enough.
*   **Iterating Through 8 Directions:** The nested loop structure used to iterate through the 8 directions is concise and efficient.
*   **`dist + 1`:** Remembering to add `1` to the final `dist` value to get the number of *cells* visited is crucial for satisfying the problem's requirement.

### 6. Edge Cases Handled

*   **Starting Cell Blocked:** The code explicitly checks if the starting cell `grid[0][0]` is blocked (equal to 1). If it is, the algorithm cannot proceed, and no path exists.
*   **No Path:**  If after the BFS traversal, the distance to the destination cell `dist[n-1][n-1]` is still `INT_MAX`, it means there is no path, and the function returns -1.
*   **Single Cell Matrix:** The code will still work correctly for a 1x1 matrix.
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
        int n = (int)grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> que;
        vector<vector<bool>> vis(n, vector<bool>(n, false));

        int srcX = 0, srcY = 0;
        int destX = n - 1, destY = n - 1;
        if (!grid[srcY][srcX]) {
            dist[srcY][srcX] = 0;
            vis[srcY][srcY] = true;
            que.push({srcY, srcX});
        }

        while (!que.empty()) {
            int s = (int)que.size();
            while (s--) {
                auto elt = que.front();
                int nodeX = elt.second;
                int nodeY = elt.first;
                que.pop();

                for (int x = nodeX - 1; x <= nodeX + 1; x++) {
                    for (int y = nodeY - 1; y <= nodeY + 1; y++) {
                        if (x >= 0 && x < n && y >= 0 && y < n && !(x == nodeX && y == nodeY)) {
                            if (!grid[y][x] && !vis[y][x]) {
                                vis[y][x] = true;
                                dist[y][x] = dist[nodeY][nodeX] + 1;
                                que.push({y, x});
                            }
                        }
                    }
                }
            }
        }

        if (dist[destY][destX] == INT_MAX)
            return -1;

        return dist[destY][destX] + 1; // since we've to return the number of visited cells and not distance
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
*Documentation generated on 2025-08-02 14:30:54*
