# rudeSubstring

```markdown
## Code Documentation: Finding the Longest Rude Substring

This document analyzes a C++ solution to the "rudeSubstring" problem from the Codeforces Educational Round (see URL below). The problem asks to find the longest substring of a given string whose "rudeness" (defined as the number of 'a'...'b' pairs) does not exceed a given limit.

**1. Problem Description:**

The problem, available at [https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G](https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G), can be summarized as follows:

Given a string `str` of length `n` consisting only of characters 'a' and 'b', and an integer `c`, find the length of the longest substring of `str` whose "rudeness" is at most `c`.  The rudeness of a substring is defined as the number of pairs `(i, j)` such that `i < j` and `str[i] = 'a'` and `str[j] = 'b'`.

**2. Approach Explanation:**

The solution uses a sliding window approach to efficiently find the longest good substring. The core idea is:

1.  **Maintain a sliding window `[l, r]`:** The window represents a substring of `str`.
2.  **Expand the window (increment `r`):**  As we expand the window to the right, we update the `rudeness` count by considering the newly added character. If the added character is 'b', we increment the `rudeness` by the number of 'a' characters currently present in the window to the left of `r`.
3.  **Shrink the window (increment `l`):** If the `rudeness` of the current window exceeds `c`, we shrink the window from the left (increment `l`) until the `rudeness` becomes less than or equal to `c`. During shrinking, we need to reduce the `rudeness` count accordingly based on whether the character being removed (`str[l]`) is 'a' or 'b'. If `str[l]` is 'a', we decrease the rudeness by the current count of 'b's in the window.
4.  **Track the maximum length:**  At each step, after ensuring that the current window `[l, r]` is "good" (rudeness <= `c`), we update the maximum length found so far.

**3. Key Insights and Algorithmic Techniques Used:**

*   **Sliding Window Technique:** This is the fundamental technique used to efficiently process the string by maintaining a window of variable size and sliding it through the string.
*   **Subsegment Monotonicity:** The "good" property (rudeness <= `c`) is subsegment monotonic. This means that if a segment is "good", all its subsegments are also "good". This property is implicitly used by the shrinking window.
*   **Efficient Rudeness Calculation:** The rudeness is calculated incrementally as the window expands and shrinks.  When a 'b' is added, the count of 'a's in the window is directly added to the rudeness. Similarly, when an 'a' is removed, the count of 'b's is subtracted from the rudeness. This avoids recalculating the rudeness from scratch for each window.

**4. Time and Space Complexity Analysis:**

*   **Time Complexity: O(n)**  The outer loop iterates through the string once (O(n)). The inner `while` loop (shrinking the window) can, in the worst case, iterate through all elements of the string as well. However, since `l` only ever increases, the total number of iterations of the `while` loop across all outer loop iterations is at most `n`. Therefore, the overall time complexity is O(n).
*   **Space Complexity: O(1)**  The solution uses a constant amount of extra space for variables like `l`, `r`, `countA`, `countB`, `rudeness`, and `maxi`. Therefore, the space complexity is O(1).

**5. Important Code Patterns or Tricks Used:**

*   **Incremental Rudeness Update:** Instead of recomputing the rudeness of the current window from scratch, the code efficiently updates the rudeness as the window expands and shrinks. This greatly improves performance.
*   **Using `#define int long long`:** This is a common trick in competitive programming to avoid integer overflow issues when dealing with potentially large input values.

**6. Edge Cases Handled:**

*   **Empty String:** If the input string is empty, the code implicitly handles this by returning 0 because the `for` loop will not execute.
*   **c = 0:**  If c is 0, only substrings with no 'a' followed by 'b' are considered "good".
*   **String with only 'a's or 'b's:** These cases are correctly handled as the `rudeness` will remain 0 and the maximum length will be the length of the string.
*   **c sufficiently large:** When 'c' is sufficiently large such that the total rudeness of the whole string doesn't exceed `c`. The program returns the string length.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rudeSubstring
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    cin >> n >> c;

    string str;
    cin >> str;

    // rudeness of a string of length k is the number of pairs (i, j) where 0 <= i < j < k for which
    // str[i] = a and str[j] = b

    // a segment [l, r] of the string str is said to be good iff it's rudeness <= c
    // this good property is subsegment monotonic since, if it's true for some segment, it's true for all
    // it's subsegments too

    // for each index 0 <= r < n, we find the maximum length segment [l, r] for l <= r such that its good
    // we then take the maximum of these maximums for each 0 <= r < n to find the maximum length segment of str that is good

    int l = 0, countA = 0, countB = 0;
    int rudeness = 0, maxi = 0;

    for (int r = 0; r < n; r++) {
        if (str[r] == 'a') {
            countA++;
        } else { // 'b'
            countB++;
            rudeness += countA;
        }

        while (l <= r && rudeness > c) {
            if (str[l] == 'a') {
                countA--;
                rudeness -= countB;
            } else if (str[l] == 'b') {
                countB--;
            }
            l++;
        }

        if (r >= l)
            maxi = max(maxi, r - l + 1);
    }
    cout << maxi << "\n";
}
```

---
*Documentation generated on 2025-08-21 09:04:54*
