# blackWhiteStripe

```markdown
# Documentation for Black and White Stripe Problem

This document analyzes a C++ solution for the "Black and White Stripe" problem, likely from a competitive programming contest. The problem URL is given as https://codeforces.com/contest/1690/problem/D.

## 1. Problem Description (Inferred)

Given a string `str` of length `n` consisting of characters 'B' (black) and 'W' (white), and an integer `k`, find a substring of length `k` with the minimum number of 'W' characters.  The goal is to output this minimum number of 'W's.

## 2. Approach Explanation

The solution uses a sliding window approach to efficiently find the substring of length `k` with the minimum number of 'W' characters. It iterates through the string using a sliding window of size `k`.  For each window, it counts the number of 'W' characters and updates the minimum count found so far.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The core idea is the sliding window technique. This allows us to maintain a window of size `k` and update the count of 'W's efficiently as the window slides across the string.  Instead of recalculating the 'W' count for each substring of length `k`, we incrementally update it by adding the new character entering the window and removing the character leaving the window.

*   **Prefix Sum (Implicit):** While not explicitly using a prefix sum array, the count variable essentially acts as a dynamic prefix sum within the sliding window. We only update this `count` based on the characters entering or exiting the window, avoiding recomputation from scratch.

*   **Minimum Tracking:** The `mini` variable is used to track the minimum number of 'W's found so far.  It's initialized to a large value (`LLONG_MAX`) and updated whenever a window with a lower 'W' count is encountered.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The solution iterates through the string once using a sliding window.  The `l` pointer increments at most `n` times. Therefore, the time complexity is O(n).

*   **Space Complexity:** The solution uses a constant amount of extra space for variables like `l`, `count`, `mini`, `n`, `k`, and `str`. Therefore, the space complexity is O(1).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a common optimization technique used in competitive programming to speed up input/output operations by disabling synchronization between C++ streams and the standard C library's streams.

*   **`#define int long long`**: This macro redefines `int` as `long long` to avoid potential integer overflow issues, particularly when dealing with larger input values or intermediate calculations.

*   **`LLONG_MAX`**: Using `LLONG_MAX` to initialize `mini` ensures that the first encountered count of 'W's will always be smaller. This prevents incorrect initialization of the minimum.

## 6. Any Edge Cases Handled

*   The code implicitly handles the edge case where `k` is larger than `n`. In this situation, the inner `while` loop will not execute, and the condition `r - l + 1 == k` will only be satisfied when the entire string has been processed, which effectively considers the entire string as the window. The logic remains correct in this scenario.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: blackWhiteStripe
// URL: https://codeforces.com/contest/1690/problem/D
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string str;
        cin >> str;

        int l = 0;
        int count = 0;
        int mini = LLONG_MAX;
        for (int r = 0; r < n; r++) {
            if (str[r] == 'W')
                count++;
            while ((r - l + 1) > k) {
                if (str[l] == 'W')
                    count--;
                l++;
            }

            if (r - l + 1 == k) {
                mini = min(count, mini);
            }
        }

        cout << mini << endl;
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-22 18:14:51*
