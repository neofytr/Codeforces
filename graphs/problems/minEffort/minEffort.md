# minEffort

```markdown
# Minimum Effort Path

## 1. Problem Description

The problem, as inferred from the code and comments referencing [LeetCode problem 1631: Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/description/), asks us to find the minimum effort required to traverse from the top-left cell (0, 0) to the bottom-right cell (n-1, m-1) of a 2D grid `heights` of dimensions n x m.  The effort of a path is defined as the maximum absolute difference in height between any two consecutive cells along the path. The goal is to find the path with the minimum possible effort. Movement is allowed in four directions: up, down, left, and right.

## 2. Approach Explanation

The code implements Dijkstra's algorithm to find the minimum effort path.  The key idea is to treat the grid as a graph where each cell is a node, and there's an edge between adjacent cells. The weight of an edge represents the absolute difference in height between the connected cells.  We want to find the shortest path from the top-left node to the bottom-right node, where "shortest" is defined in terms of minimizing the maximum edge weight along the path (the effort).

The algorithm maintains a 2D `effort` matrix that stores the minimum effort required to reach each cell from the starting cell (0, 0). Initially, all cells have an effort of `INT_MAX`, except for the starting cell, which has an effort of 0.

A min-heap `minHeap` is used to efficiently select the cell with the smallest current effort. The heap stores pairs of the form (effort, (row, col)).

The algorithm iteratively extracts the cell with the minimum effort from the heap.  For each neighbor of the current cell, it calculates the effort required to move to that neighbor. This effort is the maximum of the current cell's effort and the absolute height difference between the two cells.

If the calculated effort is less than the current effort recorded for the neighbor in the `effort` matrix, it means we've found a path to the neighbor with a lower effort. In this case, the neighbor's effort is updated in the `effort` matrix, and the neighbor is added to the min-heap. Crucially, before adding the neighbor, its previous entry in the minHeap is removed if present using `minHeap.erase({effort[dy][dx], {dy, dx}});`.  This step is important for correctness as Dijkstra's algorithm requires updating the priority of a node already in the heap.

The algorithm continues until the min-heap is empty, at which point the `effort` matrix contains the minimum effort required to reach each cell from the starting cell. The result is the effort value at the bottom-right cell, `effort[n-1][m-1]`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dijkstra's Algorithm:** The core algorithm used to find the shortest path.  The standard Dijkstra's algorithm finds the path with the minimum sum of edge weights, but here, we modify it to minimize the *maximum* edge weight along the path.
*   **Min-Heap (Priority Queue):**  Crucial for efficiently selecting the cell with the smallest current effort.  Using a `std::set` as a min-heap provides logarithmic time complexity for insertion, deletion, and finding the minimum element.
*   **Dynamic Programming:** The `effort` matrix effectively implements dynamic programming. `effort[i][j]` stores the minimum effort to reach cell (i, j), building up from the starting cell.
*   **Graph Representation:**  Implicitly representing the grid as a graph where cells are nodes and edges connect adjacent cells.
*   **Modifying Dijkstra for Minimax:** Adapting Dijkstra to solve a minimax (minimize the maximum) problem instead of a minimization problem. The key modification is in how the "distance" (effort) to a neighbor is calculated: `max(currEffort, abs(heights[dy][dx] - heights[nodeY][nodeX]))`.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**  O(M * N * log(M * N)), where M is the number of columns and N is the number of rows in the `heights` matrix. This is because, in the worst case, we might insert and extract each cell from the min-heap once.  Each heap operation takes O(log(M * N)) time. The inner loop iterates a constant number of times (4 directions).
*   **Space Complexity:** O(M * N).  The `effort` matrix and the min-heap can both potentially store up to M * N elements.

## 5. Important Code Patterns or Tricks Used

*   **Direction Arrays:** The `dr` and `dc` arrays are a common trick for efficiently iterating over the four neighboring cells of a given cell.
*   **Using `std::set` as a Priority Queue:** While `std::priority_queue` is the usual go-to for priority queues, `std::set` offers the `erase()` function by value, which is *crucial* for this Dijkstra implementation to update existing nodes in the heap. Note that this implementation does incur a slightly higher constant factor.  Using `priority_queue` would require a different approach (e.g., lazy deletion).
*   **Erasing from MinHeap Before Re-inserting:** The code `minHeap.erase({effort[dy][dx], {dy, dx}});` before updating `effort[dy][dx]` and inserting again is critical. If this step is omitted, the same cell may appear multiple times in the heap with different effort values, leading to incorrect results. Because the `std::set` is maintaining nodes ordered by the effort, removing the node before inserting is crucial to re-order the frontier correctly.
*   **Implicit Graph:** No explicit graph data structure is constructed. Instead, neighbors are calculated on the fly, saving memory.

## 6. Any Edge Cases Handled

*   **Empty Grid:** The code appears to handle an empty grid implicitly because it calculates `n` and `m` based on the input `heights`. If either `n` or `m` is zero, the algorithm would likely not proceed into the main loop, or if it did proceed, array access might be problematic.  However, LeetCode problem constraints usually guarantee a valid input grid.
*   **Single Cell Grid:** Works correctly if the grid has only one cell, as the `effort` matrix is initialized and the while loop would immediately terminate as all neighbours would be outside the bounds.
*   **Disconnections:** The algorithm correctly finds the minimum effort path even if the grid contains "difficult" terrain with significant height differences, because it uses Dijkstra's algorithm to explore all possible paths. Even if there is no *path*, the algorithm will correctly fill in the effort matrix such that accessing effort[n-1][m-1] will reflect that there exists no path. The function definition does not need to check if a valid path exists.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: minEffort
// URL: http://leetcode.com/problems/path-with-minimum-effort/description/
// Difficulty: medium
// Tags:
// Strategy:

class Solution {
  public:
    int minimumEffortPath(vector<vector<int>> &heights) {
        int n = (int)heights.size();
        int m = (int)heights[0].size();
        int dr[] = {0, -1, 0, +1};
        int dc[] = {-1, 0, +1, 0};
        // effort[y][x] is the min effort required to move from 0,0 to y,x along any path
        // a path's effort is the maximum of the absolute difference between any two consecutive nodes in it
        vector<vector<int>> effort(n, vector<int>(m, INT_MAX));
        set<pair<int, pair<int, int>>> minHeap;

        effort[0][0] = 0;
        minHeap.insert({0, {0, 0}});
        while (!minHeap.empty()) {
            auto elt = *(minHeap.begin());
            int currEffort = elt.first;
            int nodeY = elt.second.first;
            int nodeX = elt.second.second;
            minHeap.erase(elt);

            for (int index = 0; index < 4; index++) {
                int dy = nodeY + dr[index];
                int dx = nodeX + dc[index];

                if (dy >= 0 && dx >= 0 && dx < m && dy < n) {
                    int newCurrEffort = max(currEffort, abs(heights[dy][dx] - heights[nodeY][nodeX])); // effort value along the current path
                    if (effort[dy][dx] > newCurrEffort) {
                        minHeap.erase({effort[dy][dx], {dy, dx}});
                        // wont traverse back to the parent since the parent's effort would necessarily be <= currEffort
                        effort[dy][dx] = newCurrEffort;
                        minHeap.insert({effort[dy][dx], {dy, dx}});
                    }
                }
            }
        }

        return effort[n - 1][m - 1];
    }
};
```

---
*Documentation generated on 2025-08-02 15:58:48*
