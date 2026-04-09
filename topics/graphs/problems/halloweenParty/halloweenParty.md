# halloweenParty

```markdown
# Halloween Party Problem Analysis

## 1. Problem Description

Based on the code and the embedded URL comment (`https://web.archive.org/web/20200930162803/http://www.devskill.com/CodingProblems/ViewProblem/60`), the problem is likely a grid traversal problem. We are given a grid (city) of size `n x m` where each cell contains a digit (0 or 1).  The goal is to find the minimum distance (cost) to travel from the top-left cell (0, 0) to the bottom-right cell (n-1, m-1). The cost to move between adjacent cells is 0 if the cell values are the same, and 1 if the cell values are different.  The URL mentioned confirms this, describing a "Halloween Party" problem about finding the minimum cost to travel through a city grid.

## 2. Approach Explanation

The code implements a 0-1 BFS (Breadth-First Search) to solve this shortest path problem.  The main idea is to treat the grid as a graph where each cell is a node, and the edges between adjacent cells have weights of either 0 or 1, depending on whether the cell values are the same or different.

The standard BFS algorithm is modified to handle different edge weights.  Instead of using a standard queue, a deque (double-ended queue) is used.  When encountering an edge with weight 0, the new node is added to the *front* of the deque.  When encountering an edge with weight 1, the new node is added to the *back* of the deque. This prioritizes nodes reachable with smaller costs, as they will be explored first. This ensures that we're always exploring the nodes with the shortest distance first, maintaining the BFS property despite the variable edge weights.

## 3. Key Insights and Algorithmic Techniques Used

*   **0-1 BFS:** This is the core algorithmic technique.  It's a clever modification of BFS to handle graphs where edge weights are restricted to 0 and 1. Using a deque allows us to efficiently explore nodes with lower costs first, leading to the shortest path.
*   **Graph Representation:** The problem is effectively solved by representing the grid as a graph. Understanding this transformation is crucial.
*   **Distance Tracking:** The `dist` matrix keeps track of the minimum distance from the starting cell (0, 0) to each cell in the grid. It's initialized with `LLONG_MAX` to represent infinity, ensuring that any valid path found will update the distance.
*   **Direction Arrays:** `dr` and `dc` arrays provide a concise and readable way to iterate through the four possible directions (up, left, down, right) from each cell.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n * m), where n is the number of rows and m is the number of columns in the grid. Each cell is visited and processed at most once.  The deque operations (push_front, push_back, pop_front) take O(1) time.
*   **Space Complexity:** O(n * m) primarily due to the `city` grid and the `dist` matrix which store the city layout and minimum distances to each cell, respectively. The `deque` can, in the worst case, contain all the nodes in the grid, further contributing to the space complexity.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is used to avoid integer overflow issues, especially when dealing with larger grids. It redefines the `int` type to be `long long`.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  These lines are used to speed up input/output operations by disabling synchronization between the C and C++ standard streams and un-tying `cin` from `cout`. This can significantly improve the execution time, particularly for problems with large input sizes.
*   **Character to Integer Conversion:** The line `city[row][col] = str[col] - '0';` efficiently converts a character representing a digit ('0' or '1') to its integer equivalent.
*   **`auto [r, c] = que.front();`:** This is structured binding (available since C++17), providing a more readable and concise way to access the row and column values from the pair at the front of the queue.
*   **Using `deque` for 0-1 BFS:** Employing a `deque` and pushing zero-weight edges to the front and one-weight edges to the back is the quintessential trick for 0-1 BFS.

## 6. Edge Cases Handled

*   **Validating Neighboring Cells:** The code includes checks `nr >= 0 && nc >= 0 && nr < n && nc < m` to ensure that the neighboring cells being accessed are within the bounds of the grid, preventing out-of-bounds errors.
*   **LLONG_MAX Initialization:** Initializing `dist` with `LLONG_MAX` effectively handles the case where a cell is unreachable. If `dist[n-1][m-1]` remains `LLONG_MAX` after the BFS, it would indicate no path exists, although this scenario isn't explicitly checked but the initialized value ensures proper comparison.
*   **Starting and Ending values are the same:** The program implicitly handles cases where the value in the top-left cell `city[0][0]` and the bottom-right cell `city[n-1][m-1]` are the same. The BFS will explore the grid correctly, finding the optimal path regardless of the starting/ending cell values.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: halloweenParty
// URL: https://web.archive.org/web/20200930162803/http://www.devskill.com/CodingProblems/ViewProblem/60
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    for (int r = 1; r <= t; r++) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> city(n, vector<int>(m));
        for (int row = 0; row < n; row++) {
            string str;
            cin >> str;
            for (int col = 0; col < m; col++)
                city[row][col] = str[col] - '0';
        }

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, -1, 0, 1};

        deque<pair<int, int>> que;
        vector<vector<int>> dist(n, vector<int>(m, LLONG_MAX));

        que.push_front({0, 0});
        dist[0][0] = 0;
        while(!que.empty()) {
            auto [r, c] = que.front();
            que.pop_front();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nc >= 0 && nr < n && nc < m) {
                    int w = (city[nr][nc] == city[r][c] ? 0 : 1);
                    if (dist[nr][nc] > dist[r][c] + w) {
                        dist[nr][nc] = dist[r][c] + w;
                        if (!w) que.push_front({nr, nc});
                        else que.push_back({nr, nc});
                    }
                }
                    
            }
        }

        cout << "Case " << r << ": " << dist[n - 1][m - 1] << endl;
    }    
    return 0;
}
```

---
*Documentation generated on 2025-10-05 10:07:58*
