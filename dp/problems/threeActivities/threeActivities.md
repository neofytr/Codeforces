# threeActivities

```markdown
# Competitive Programming Solution Documentation

This document provides a comprehensive analysis of the provided C++ solution for the "threeActivities" problem on Codeforces (URL: https://codeforces.com/problemset/problem/1914/D).

## 1. Problem Description

The problem, inferred from the code and comments, likely presents a scenario where there are `n` participants and three activities: skiing, movies, and board games. Each participant has a score for each activity. The goal is to select three participants, one for each activity, such that:

*   No participant is selected for more than one activity.
*   The sum of their scores is maximized.

## 2. Approach Explanation

The solution employs a brute-force approach, optimized by considering only the top 3 participants for each activity.  It first reads the scores for each activity into separate vectors, associating each score with its original index (participant number).  Then, for each activity, it sorts the participants by their scores in descending order and selects the top 3. Finally, it iterates through all possible combinations of selecting one participant from the top 3 of each activity, checking if the selected participants are distinct.  If they are, it calculates the total score and updates the maximum score found so far.

## 3. Key Insights and Algorithmic Techniques Used

*   **Greedy Optimization:** The key optimization is to only consider the top 3 performers in each activity. This significantly reduces the search space while still guaranteeing finding the optimal solution.  This is based on the intuition that the optimal combination is likely to involve high-scoring participants.
*   **Brute Force with Pruning:** The code essentially does a brute force search over all possible combinations of the top 3 participants for each activity.  The pruning comes from not considering all `n^3` possible combinations.
*   **Storing Indices:**  The code correctly stores the original indices of the scores using `pair<int, int>` to keep track of which participant corresponds to which score, which is crucial for checking for duplicates.
*   **Lambda Function for Reusability:** The `getTop` function is implemented as a lambda, promoting code reusability and readability.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting each activity's scores takes O(n log n) time, done three times for a total of O(3n log n) = O(n log n).
    *   Selecting the top 3 takes O(1).
    *   Iterating through all combinations of the top 3 participants for each activity takes O(3 * 3 * 3) = O(1).
    *   The overall time complexity is dominated by the sorting step, thus the total time complexity is O(n log n) for each test case. For 't' test cases, the complexity becomes O(t * n log n).

*   **Space Complexity:**
    *   The vectors `ski`, `movie`, and `board` each require O(n) space.
    *   The `topSki`, `topMovie`, and `topBoard` vectors each require O(1) space (at most 3 elements).
    *   The overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`ios::sync_with_stdio(false); cin.tie(nullptr);`**: This is a standard trick in competitive programming to speed up input/output operations by disabling synchronization between the C and C++ standard input/output streams.
*   **`#define int long long`**: This defines the `int` type as `long long` to avoid integer overflow issues, especially important when dealing with larger input values or sums.
*   **Lambda Function:** Using a lambda function (`getTop`) improves code readability and reusability.
*   **`greater<>()` in `sort()`**: This ensures that the vector is sorted in descending order.
*   **`pair<int,int>`**: This ensures that values are paired with their original positions to prevent same member participating in multiple events.

## 6. Edge Cases Handled

*   **`min(3LL, (int)arr.size())`**: This handles the edge case where `n < 3`. If there are fewer than 3 participants for an activity, it selects all participants for that activity. Although `n` can be very small, the problem statement does not impose any lower limit.

## Additional Comments

The solution is well-structured and easy to understand. The comments provide a good overview of the problem and the strategy used. The use of `long long` for integers is a good practice to prevent potential overflow issues. The solution could be further optimized if the problem required handling an extremely large number of test cases by precomputing top performers across multiple runs if data structure used for storing top performers allows for efficient manipulation and indexing. However, for the given constraints, the current solution is efficient and correct.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: threeActivities
// URL: https://codeforces.com/problemset/problem/1914/D
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> ski(n), movie(n), board(n);

        for (int i = 0; i < n; i++)
            cin >> ski[i].first, ski[i].second = i;
        for (int i = 0; i < n; i++)
            cin >> movie[i].first, movie[i].second = i;
        for (int i = 0; i < n; i++)
            cin >> board[i].first, board[i].second = i;

        auto getTop = [&](vector<pair<int, int>> &arr) {
            sort(arr.begin(), arr.end(), greater<>());
            vector<pair<int, int>> top;
            for (int i = 0; i < min(3LL, (int)arr.size()); i++)
                top.push_back(arr[i]);
            return top;
        };

        auto topSki = getTop(ski);
        auto topMovie = getTop(movie);
        auto topBoard = getTop(board);

        int best = 0;
        for (auto [sval, si] : topSki) {
            for (auto [mval, mi] : topMovie) {
                for (auto [bval, bi] : topBoard) {
                    if (si != mi && mi != bi && si != bi) {
                        best = max(best, sval + mval + bval);
                    }
                }
            }
        }
        cout << best << "\n";
    }
}

```

---
*Documentation generated on 2025-08-30 08:45:48*
