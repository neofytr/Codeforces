# longJumps

```markdown
# Long Jumps Problem Analysis and Documentation

## 1. Problem Description

Based on the code and comments, the problem is likely [Long Jumps](https://codeforces.com/problemset/problem/1472/C) from Codeforces.

**Problem Statement (Inferred):**

Given an array `arr` of `n` positive integers, starting from index 1.  At each index `i`, you can jump `arr[i]` positions forward. The score obtained by starting at index `i` is the sum of all the values of `arr` visited during the jumps, including the starting position. The goal is to find the maximum possible score that can be obtained by starting at any index from 1 to `n`. If a jump leads to an index greater than `n`, the process stops, and no further values are added to the score.

## 2. Approach Explanation

The solution uses a Dynamic Programming (DP) approach with a Depth-First Search (DFS) structure for calculating the maximum possible score for each starting position.

1.  **Initialization:**
    *   An array `arr` of size `n+1` stores the input jump lengths. The index 0 is unused.
    *   A DP array `dp` of size `n+1` is initialized with `-1` to indicate that the maximum score for each starting index hasn't been computed yet.  `dp[i]` represents the maximum score achievable when starting at index `i`.

2.  **DFS with Memoization (dfs function):**
    *   The `dfs(node, arr, dp)` function recursively calculates the maximum score starting from `node`.
    *   **Base Case:** If `node > n`, it means we've jumped beyond the array bounds, so the score is 0.
    *   **Memoization:** If `dp[node]` is not `-1`, it means the score for starting at `node` has already been computed, so return `dp[node]`.
    *   **Recursive Step:** Otherwise, calculate the score by adding the value at the current node (`arr[node]`) to the maximum score achievable from the next jump, which is `dfs(node + arr[node], arr, dp)`. Store the result in `dp[node]` and return it.

3.  **Main Loop (solve function):**
    *   Iterate through all possible starting indices `node` from 1 to `n`.
    *   For each `node`, call `dfs(node, arr, dp)` to compute the maximum score starting from that node.
    *   Keep track of the overall maximum score encountered.

4.  **Handling Multiple Test Cases (main function):**
    *   The `main` function reads the number of test cases `t` and calls the `solve` function for each test case.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming (Memoization):** The core idea is to avoid redundant calculations. The `dp` array stores the results of already computed subproblems (maximum score starting from a particular index). This significantly improves efficiency compared to a purely recursive approach.
*   **Depth-First Search (DFS):** The `dfs` function explores the possible jump sequences recursively. The recursive calls effectively trace different paths based on the jump lengths.
*   **Top-Down Approach:**  The DP is implemented using a top-down (memoization) approach, where we start from the initial problem and break it down into smaller subproblems as needed.
*   **Maximization:** The algorithm ensures that it tracks the absolute maximum score from all possible starting points.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(N), where N is the size of the array `arr`. The `dfs` function visits each node at most once due to memoization.  The main loop iterates through each starting node from 1 to N, each call to `dfs` takes O(1) amortized time. Therefore, the overall time complexity is O(N).
*   **Space Complexity:** O(N), mainly due to the `arr` and `dp` vectors, both of size `n+1`.  The recursion depth of the `dfs` function is also at most N in the worst case.

## 5. Important Code Patterns or Tricks Used

*   **Memoization:** The `dp` array initialized with `-1` is a classic memoization technique to indicate that a subproblem hasn't been solved yet.
*   **Base Case Handling:**  The `node > n` check prevents accessing array elements out of bounds and serves as a stopping condition for the recursion.
*   **Using `long long`:** Using `long long` data type for storing the score and jump lengths is crucial because the score could become large, potentially exceeding the range of `int`.  The problem statement likely implies constraints where the cumulative score might overflow `int`.
*   **Unused Index 0:** The index 0 of the `arr` and `dp` vectors is deliberately unused to simplify the logic, since the problem's array indices start from 1. This avoids the need to constantly subtract 1 from indices.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization to speed up input/output operations in C++ by decoupling the C++ standard input/output stream from the C standard input/output stream.

## 6. Edge Cases Handled

*   **Jumping out of bounds:** The `node > n` condition in the `dfs` function explicitly handles the case where a jump leads to an index outside the array's bounds. This prevents errors and ensures correct score calculation.
*   **Empty array/Zero sized array:** Implicitly handled, If n=0 then for loop for node will not execute and default value of maxi will remain LLONG_MIN.
*   **All zeros case:** If all elements of the array `arr` are zero, the code will still function correctly.
*   **Large values:** Using `long long` prevents integer overflows.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: longJumps
// URL: https://codeforces.com/problemset/problem/1472/C
// Difficulty: easy
// Tags:
// Strategy:

long long dfs(int node, vector<long long> &arr, vector<long long> &dp) {
    int n = (int)arr.size() - 1;
    if (node > n) {
        return 0;
    }
    if (dp[node] != -1) {
        return dp[node];
    }

    return dp[node] = arr[node] + dfs(node + arr[node], arr, dp);
}

void solve() {
    int n;
    cin >> n;

    vector<long long> arr(n + 1);
    vector<long long> dp(n + 1, -1);
    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
    }

    // dp[r] is the maximum score possible with starting index r
    long long maxi = LLONG_MIN;
    for (int node = 1; node <= n; node++) {
        maxi = max(maxi, dfs(node, arr, dp));
    }

    cout << maxi << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

---
*Documentation generated on 2025-07-28 17:42:17*
