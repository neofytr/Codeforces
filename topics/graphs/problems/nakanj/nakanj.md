# nakanj

```markdown
## Documentation of Competitive Programming Solution for NAKANJ Problem

This document analyzes a C++ solution to the NAKANJ problem on SPOJ ([https://www.spoj.com/problems/NAKANJ/](https://www.spoj.com/problems/NAKANJ/)). The problem asks for the minimum number of knight moves to reach a destination square from a source square on a standard 8x8 chessboard.

### 1. Problem Description

Given two chess squares represented in algebraic notation (e.g., "a1", "h8"), determine the minimum number of knight moves required to reach the destination square from the source square.

### 2. Approach Explanation

The solution employs a Breadth-First Search (BFS) algorithm to find the shortest path (in terms of knight moves) on the chessboard.  The chessboard is represented as a graph where each square is a node, and an edge exists between two squares if a knight can move directly from one to the other.  BFS guarantees finding the shortest path in an unweighted graph.

The core idea is as follows:

1.  **Represent the chessboard:** The 8x8 chessboard is represented as a linear array of size 64 (8 rows * 8 columns).  A mapping function `idx(row, col)` converts row and column indices to a single index within this array.
2.  **Convert input to indices:**  The input squares (e.g., "a1") are converted to 0-based row and column indices. These indices are then converted to the corresponding array index using the `idx` function.
3.  **BFS Traversal:** A queue is used to perform BFS. The source square is enqueued and marked as visited with a distance of 0.
4.  **Knight moves:** The code iterates through all possible knight moves from the current square.
5.  **Validity check:**  For each possible move, the `valid` function checks if the new square is within the bounds of the chessboard.
6.  **Update distance:** If a valid and unvisited neighbor is found, its distance is updated (current distance + 1), it's marked as visited, and enqueued.
7.  **Result:** The algorithm terminates when the destination square is reached (implicitly - BFS explores all reachable squares). The distance to the destination square represents the minimum number of knight moves.

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):**  BFS is the fundamental algorithm. Its guarantee to find shortest paths in unweighted graphs is crucial for this problem.
*   **Graph Representation:**  The chessboard is implicitly treated as a graph. Each square is a node, and knight moves define the edges.
*   **Linear Indexing:**  The `idx(row, col)` function provides a compact representation of the 2D chessboard in a 1D array. This simplifies graph traversal.
*   **Predefined Knight Move Offsets:** The `dr` and `dc` arrays store the 8 possible row and column offsets for a knight's move. This allows for concise and efficient exploration of neighbor squares.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(N), where N is the number of squares on the chessboard (8x8 = 64).  In the worst case, BFS might visit every square on the board. The constant factor comes from iterating through the knight moves (8 possible moves for each square).  Therefore, the time complexity can be expressed as O(8 * 64) = O(64).
*   **Space Complexity:** O(N), where N is the number of squares on the chessboard. This is due to the `vis` (visited) and `dist` (distance) vectors, which each store information for all squares.  The queue could, in the worst-case, also contain all nodes.

### 5. Important Code Patterns or Tricks Used

*   **`#define` Macros:**  The code uses macros (e.g., `#define int long long`, `#define NROWS 8`, `#define NCOLS 8`, `#define idx(row, col) (row * NCOLS + col)`) for code conciseness.  While these can be useful, they can also make debugging more difficult and impact readability if overused.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This disables synchronization between C and C++ streams and unties `cin` and `cout`, resulting in faster I/O operations.  This is a common optimization in competitive programming.
*   **Representing chess board position by row and col:** Representing the chess board positions with rows and cols make the code more organized and easier to follow the logic.
*   **Using arrays to store knight move offsets:** Using `dr` and `dc` arrays to store the knight move offsets simplifies the code by allowing to programatically generate all possible knight moves.

### 6. Any Edge Cases Handled

*   **`valid(row, col)` function:**  This function ensures that the knight doesn't move off the board, handling the edge cases where a knight's move would result in an invalid square.
*   **Implicit Handling of Same Source and Destination:** If the source and destination are the same, the algorithm will correctly compute a distance of 0 due to initialization `dist[src] = 0`.
*   **Input conversion:** Convert the string chess board position to integer indices correctly with proper offset handling.

This analysis provides a complete understanding of the solution, its algorithmic foundation, and its implementation details.  It highlights the key insights and learning points that can be applied to other graph traversal problems.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: nakanj
// URL: https://www.spoj.com/problems/NAKANJ/
// Difficulty: medium
// Tags: 
// Strategy: 

#define NROWS 8
#define NCOLS 8

#define idx(row, col) (row * NCOLS + col)

bool valid(int row, int col) {
    return (row >= 0 && col >= 0 && row < NROWS && col < NCOLS);
}

void solve() {
    string srcstr, dststr;
    cin >> srcstr >> dststr;

    // convert chess notation ('a1', 'h8') to 0-based row, col indices
    int src_row = srcstr[1] - '1';
    int src_col = srcstr[0] - 'a';
    int dst_row = dststr[1] - '1';
    int dst_col = dststr[0] - 'a';

    int src = idx(src_row, src_col);
    int dst = idx(dst_row, dst_col);

    queue<int> que;
    vector<bool> vis(NROWS * NCOLS, false);
    vector<int> dist(NROWS * NCOLS, LLONG_MAX);

    vis[src] = true;
    dist[src] = 0;
    que.push(src);

    // knight move offsets
    int dr[8] = {2, 2, -2, -2, 1, -1, 1, -1};
    int dc[8] = {1, -1, 1, -1, 2, 2, -2, -2};

    while(!que.empty()) {
        int x = que.front();
        que.pop();

        int r = x / NCOLS;
        int c = x % NCOLS;

        for (int i = 0; i < 8; i++) {
            int nrow = r + dr[i];
            int ncol = c + dc[i];
            int id = idx(nrow, ncol);
            if (valid(nrow, ncol) && !vis[id]) {
                dist[id] = dist[x] + 1;
                vis[id] = true;
                que.push(id);
            }
        }
    }

    cout << dist[dst] << endl;
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
*Documentation generated on 2025-10-04 14:15:49*
