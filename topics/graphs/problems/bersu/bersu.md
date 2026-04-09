# bersu

```markdown
## Documentation: Codeforces Problem 489B - Bersu Ball

This document provides a comprehensive analysis of the provided C++ solution for Codeforces problem 489B - Bersu Ball (https://codeforces.com/problemset/problem/489/B).

### 1. Problem Description (Inferred)

The problem asks to find the maximum number of pairs that can be formed between boys and girls, subject to the constraint that the absolute difference in their skill levels is at most 1.  Given two lists, one representing the skill levels of boys and the other representing the skill levels of girls, the goal is to maximize the number of pairs such that `|boy_skill - girl_skill| <= 1`.  Each boy and each girl can be part of at most one pair.

### 2. Approach Explanation

The solution employs a greedy approach after sorting both the boys' and girls' skill levels.  The core idea is to iterate through both sorted lists simultaneously, attempting to form pairs whenever possible.

*   **Sorting:** Sorting both lists allows us to efficiently find suitable partners.
*   **Greedy Pairing:** While iterating through the lists, if the absolute difference between the current boy's and girl's skill levels is less than or equal to 1, a pair is formed, and both pointers are incremented.  If the boy's skill is greater than the girl's, it means that the current boy cannot be paired with the current girl (their difference is greater than 1 and positive). Therefore, we advance the girl pointer to potentially find a more suitable match for the boy. Conversely, if the boy's skill is lower than the girl's, we advance the boy pointer. This ensures we always attempt to find the closest possible match.
*   **Termination:** The iteration continues until either all boys or all girls have been considered.

### 3. Key Insights and Algorithmic Techniques Used

*   **Greedy Algorithm:** The core strategy is a greedy approach.  At each step, the algorithm makes the locally optimal choice (forming a pair if the difference is within the allowed range) without backtracking. This approach happens to lead to the globally optimal solution.
*   **Sorting:** Sorting is crucial for the greedy approach to work correctly. Without sorting, the algorithm would need to compare each boy with each girl, leading to a much higher time complexity.
*   **Two-Pointer Technique:**  The simultaneous iteration through the sorted lists using two pointers (one for boys and one for girls) is a classic two-pointer technique. This enables efficient matching and reduces the overall computational cost.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the `boys` array: O(n log n)
    *   Sorting the `girls` array: O(m log m)
    *   Iterating through the arrays: O(n + m)
    Therefore, the overall time complexity is dominated by the sorting steps:  **O(n log n + m log m)**, where 'n' is the number of boys and 'm' is the number of girls.

*   **Space Complexity:**
    *   `boys` vector: O(n)
    *   `girls` vector: O(m)
    Therefore, the overall space complexity is **O(n + m)**.

### 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique used in competitive programming to speed up input/output operations by disabling synchronization between C++ streams and the C stdio library.
*   **Range-based for loop:** The `for (int &val : boys)` syntax is a concise way to iterate over the elements of a vector, allowing modification of the original elements directly.
*   **`abs()` function:** The `abs()` function is used to calculate the absolute difference between the skill levels, which is a key part of the matching condition.

### 6. Edge Cases Handled

*   **Empty Input:** The code implicitly handles the case where either the `boys` or `girls` array is empty. In such cases, the `while` loop will not execute, and the `pair` variable will remain 0, which is the correct result.
*   **No Possible Pairs:** If there are no boys and girls whose skill levels differ by at most 1, the `pair` variable will remain 0 after the `while` loop, indicating that no pairs can be formed.
*   **Duplicate Skill Levels:** The code correctly handles duplicate skill levels. Because the difference must be at most 1, several boys and girls can potentially match even if they have the same skill level. The algorithm will pair these up appropriately.

### Summary

The provided solution effectively solves the Bersu Ball problem using a greedy approach combined with sorting and the two-pointer technique.  The code is well-structured, easy to understand, and optimized for performance. The time and space complexity are reasonable for the given problem constraints.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: bersu
// URL: https://codeforces.com/problemset/problem/489/B
// Difficulty: medium
// Tags:
// Strategy:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> boys(n);
    for (int &val : boys)
        cin >> val;
    int m;
    cin >> m;
    vector<int> girls(m);
    for (int &val : girls)
        cin >> val;

    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    int boy = 0;
    int girl = 0;
    int pair = 0;
    while (boy < n && girl < m) {
        if (abs(boys[boy] - girls[girl]) <= 1) {
            pair++;
            boy++;
            girl++;
            continue;
        }

        if (boys[boy] > girls[girl]) {
            // to make a pair, we need to move the girl pointer forward
            girl++;
        } else {
            boy++;
        }
    }
    cout << pair << endl;
    return 0;
}
```

---
*Documentation generated on 2025-07-30 12:05:24*
