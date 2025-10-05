# inversionSort

```markdown
# Documentation for Inversion Sort Problem (SPOJ INVESORT)

This document provides a comprehensive analysis of the provided C++ code, which solves the Inversion Sort problem on SPOJ (https://www.spoj.com/problems/INVESORT/).

## 1. Problem Description

The Inversion Sort problem (INVESORT on SPOJ) involves transforming one string into another by a series of "inversion" operations.  An inversion operation reverses a substring within the string. The goal is to find the minimum number of inversion operations required to transform a given source string `src` into a target string `dst`.  The strings consist of characters, and their length is at most 10. The input consists of pairs of source and destination strings, and the program outputs the minimum number of inversions required to transform the source string into the destination string for each pair. The input ends when both `src` and `dst` are "*".

## 2. Approach Explanation

The code employs a **bidirectional Breadth-First Search (BFS)** algorithm to find the shortest sequence of inversions.

1. **Precompute Inversion Operations:** All possible inversion operations (defined by the starting and ending indices `l` and `r`) are precomputed and stored in the `all_ops` vector. Since string length is at most 10, this precomputation is feasible. Specifically, all substrings of length 2 to 10 are considered.

2. **Bidirectional BFS:** The algorithm performs two simultaneous BFS searches:
   - **Forward Search:** Starts from the source string `src` and explores the state space by applying inversion operations.  The distance from `src` to each visited string is stored in `dist1`.
   - **Backward Search:** Starts from the target string `dst` and explores the state space by applying inversion operations. The distance from `dst` to each visited string is stored in `dist2`.

3. **Meeting in the Middle:** The BFS searches continue until a string `t` is found that has been visited by both the forward and backward searches.  If such a string is found, the total distance (number of inversions) is `dist1[t] + dist2[t]`.

4. **Optimization:** The code uses the `if (q1.size() > q2.size())` optimization to always expand the smaller queue. This significantly improves performance, as it reduces the number of states explored.

5. **Unreachable:** If the queues become empty before any intersection is found, it means that the target string is unreachable from the source string via inversion operations (although that shouldn't happen given the problem constraints). In that case, -1 is returned (though this case is unlikely to occur based on the problem).

## 3. Key Insights and Algorithmic Techniques Used

*   **Bidirectional BFS:** The most important technique used is bidirectional BFS. Standard BFS would be too slow because the state space grows exponentially with the number of inversion operations. Bidirectional BFS significantly reduces the search space by exploring from both ends, allowing the searches to meet much faster.
*   **Precomputation:** Precomputing all possible inversion operations avoids redundant calculations within the BFS loop, improving performance.
*   **State Space Representation:** Strings themselves are used as states in the BFS search space. This is feasible due to the small string length (max 10).
*   **Hashing (unordered_map):** The `unordered_map` is used to efficiently store and retrieve distances from the source and target strings to intermediate states. This is crucial for determining if a state has already been visited.
*   **Queue for BFS:** The `queue` data structure is used to maintain the order of exploration in the BFS algorithm.
*   **String Inversion:** The `invert` function efficiently reverses a portion of the input string.
*   **Optimization: Expanding from smaller queue:** Swapping `q1` and `q2` ensures that the smaller queue is always expanded in each iteration. This optimization reduces the overall computation.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Precomputation of inversion operations: O(n^3), where n is the maximum string length (10). This is because we iterate through all possible substring lengths and starting positions. Although it is technically `O(n^3)`, `n` is small, making the term negligible in total runtime.
    *   BFS: The time complexity of BFS is O(V + E), where V is the number of possible string states, and E is the number of edges (transitions) between states. In this case:
        *   V = Number of distinct strings of length at most 10, which is relatively small given the characters involved
        *   E = V * (number of possible inversions). The number of possible inversions is the size of `all_ops`, which is bounded by a constant value derived in the precomputation. Bidirectional BFS reduces this complexity significantly.  Worst-case is still difficult to analyze precisely but is substantially better than a single directional BFS.

*   **Space Complexity:**
    *   `all_ops`: O(n^3), representing all possible substrings. Again, `n` is small, so O(1) effectively.
    *   `dist1`, `dist2`: O(V), where V is the number of possible string states, as these store distances to all visited states.
    *   `q1`, `q2`: O(V), as these queues can hold at most all possible states during the BFS traversal.
    Overall, the space complexity is primarily determined by the number of possible string states that are stored by the `dist` maps and queues. Since string length is capped at 10, the constant overheads dominate.

## 5. Important Code Patterns or Tricks Used

*   **Bidirectional BFS:** This is the core trick. By searching from both ends, the number of states explored is significantly reduced compared to a single-directional BFS.
*   **Precomputed Operations:**  Avoiding redundant calculations by storing all inversion operations beforehand.
*   **String-based State Representation:** Leveraging strings directly as states makes the code concise, but is practical only due to the small problem size.
*   **`unordered_map` for efficient distance lookups:** Using hash maps provides fast access for determining the distance to a given state and whether it has been visited.
*   **Queue Optimization:** Expanding the smaller queue in the bidirectional BFS speeds up convergence.

## 6. Edge Cases Handled

*   **Source equals Destination:** The code explicitly checks if `src == dst` and returns 0 immediately in that case.
*   **Unreachable States (Implicit):** Though unlikely due to the problem constraints, the code would return -1 if the target string were unreachable (which shouldn't happen given all possible substrings from lengths 2 to 10 are considered).
*   **Termination Condition:** The input loop correctly terminates when both `src` and `dst` are equal to "*".
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: inversionSort
// URL: https://www.spoj.com/problems/INVESORT/
// Difficulty: hard
// Tags: 
// Strategy: 

string invert(string &str, int l, int r) {
    string cp = str;
    for (int i = l, j = r; i <= r, j >= l; i++, j--)
        cp[i] = str[j];
    return cp;
}

vector<pair<int,int>> all_ops;

int bfs_bidirectional(string src, string dst) {
    if (src == dst) return 0;

    unordered_map<string, int> dist1, dist2;
    queue<string> q1, q2;

    dist1[src] = 0;
    dist2[dst] = 0;
    q1.push(src);
    q2.push(dst);

    while (!q1.empty() && !q2.empty()) {
        if (q1.size() > q2.size()) {
            swap(q1, q2);
            swap(dist1, dist2);
        }

        int sz = q1.size();
        while (sz--) {
            string s = q1.front(); q1.pop();
            int d = dist1[s];

            for (auto [l, r] : all_ops) {
                string t = invert(s, l, r);
                if (!dist1.count(t)) {
                    dist1[t] = d + 1;
                    if (dist2.count(t))
                        return dist1[t] + dist2[t];
                    q1.push(t);
                }
            }
        }
    }
    return -1; // unreachable
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int len = 2; len <= 10; len++)
        for (int l = 0; l <= 10 - len; l++) {
            int r = l + len - 1;
            all_ops.push_back({l, r});
        }

    string src, dst;
    while(cin >> src >> dst) {
        if (src == "*" && dst == "*")
            break;

        cout << bfs_bidirectional(src, dst) << "\n";
    }
    return 0;
}

```

---
*Documentation generated on 2025-10-05 11:01:00*
