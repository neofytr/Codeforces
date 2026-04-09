# theyAreEverywhere

```markdown
# Code Documentation: Codeforces Problem 701C - They Are Everywhere

This document provides a comprehensive analysis of the C++ code provided for solving the Codeforces problem "They Are Everywhere" (https://codeforces.com/problemset/problem/701/C).

## 1. Problem Description

The problem asks us to find the shortest substring of a given string that contains all the unique characters present in the string. The input consists of an integer `n` representing the length of the string, followed by the string `str` itself. The goal is to find the minimum length of a substring of `str` that contains all the distinct characters that appear in `str`.

## 2. Approach Explanation

The code utilizes a sliding window approach to find the minimum length substring containing all unique characters.  Here's the breakdown:

1.  **Calculate Unique Characters:**  First, it calculates the number of distinct characters present in the input string `str` using an `unordered_map` called `freq` to store the frequency of each character. The size of this map gives us the number of unique characters (`uniqueCount`).

2.  **Sliding Window:**  A sliding window is maintained using two pointers, `l` (left) and `r` (right). The window expands from left to right.

3.  **Maintain Running Frequencies:** Another `unordered_map` called `runningFreq` stores the frequency of each character within the current window. `runningUniqueCount` tracks the number of unique characters currently present within the window.

4.  **Expand Window:** As the right pointer `r` moves, `runningFreq` is updated. If a new unique character is encountered, `runningUniqueCount` is incremented.

5.  **Contract Window:** While the window contains all the unique characters (`runningUniqueCount == uniqueCount`), the left pointer `l` is moved to the right to shrink the window.  The `runningFreq` is updated accordingly, and if a character's frequency within the window drops to zero, `runningUniqueCount` is decremented.

6.  **Update Minimum Length:** Inside the `while` loop where the window is contracted, after the left pointer has moved and `runningUniqueCount` decreased, the algorithm checks if the previous window `[l-1, r]` was a "good" window (i.e., contained all the distinct characters of the original string). If it was, then `r - l + 2` is a candidate for minimum length and updates the `mini` variable. This is done because the `l` pointer has already been advanced, so we need to consider the substring up to the *previous* `l` value.

7.  **Handle Edge Cases:** Finally, if `mini` remains `LLONG_MAX`, which means no valid substring was found, it's set to 0.

## 3. Key Insights and Algorithmic Techniques

*   **Sliding Window:**  The core technique is the sliding window algorithm.  This is suitable because the problem asks for a substring (contiguous portion of a string) satisfying a certain condition (containing all unique characters). The sliding window efficiently explores all possible substrings without redundant calculations.
*   **Frequency Counting:** The use of `unordered_map` (hash table) to count character frequencies is crucial for determining the unique characters in the string and maintaining their counts within the window efficiently.
*   **Monotonicity:** The "goodness" property of a substring (containing all unique characters) exhibits a form of super-segment monotonicity. If a substring `[l, r]` is good, then any substring `[l', r']` where `l' <= l` and `r' >= r` is also good. This allows the sliding window to shrink until the goodness condition is no longer met.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the length of the string. The left and right pointers each traverse the string at most once. The operations within the loops (unordered map access, increment/decrement) take constant time on average.
*   **Space Complexity:** O(k), where k is the number of unique characters in the string. This is due to the `freq` and `runningFreq` unordered maps. In the worst case, k can be equal to the size of the character set (e.g., 26 for lowercase English letters), which can still be considered constant space in many contexts.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimization disables synchronization between C++ streams and the C standard streams, and unties `cin` from `cout`, which significantly improves input/output performance in competitive programming.
*   **`#define int long long`**: Using this macro is common in competitive programming to prevent integer overflow issues, especially when dealing with large inputs.
*   **Using `unordered_map` for frequency counting**: `unordered_map` provides fast lookups (average O(1)), which is crucial for efficiently tracking character frequencies in the string and the current window.
*   **Initialization of `mini` to `LLONG_MAX`**: Initializing the minimum length to the maximum possible value ensures that any valid length encountered will be smaller and update `mini`.

## 6. Edge Cases Handled

*   **Empty String (Implicitly):** If the input string is empty, `uniqueCount` will be 0, and the algorithm will correctly return 0, although this isn't explicitly handled.
*   **String with No Valid Substring:** If the input string does not contain all the unique characters at once, the variable `mini` will remain `LLONG_MAX` which is then changed to `0` before printing. For example, the test case would fail if `mini` would not reset to `0` given an input of `"aabbcc"` with desired result of `6`, where only segments like `aabbcc` will contain all of the characters in the input string.
*   **Single Character String**: If the input string consists of only one distinct character, the algorithm returns the length of string.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: theyAreEverywhere
// URL: https://codeforces.com/problemset/problem/701/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string str;
    cin >> str;

    unordered_map<char, int> freq;
    for (char c : str)
        freq[c]++;
    int uniqueCount = static_cast<int>(freq.size());

    // a segment [l, r] is good iff it contains uniqueCount unique characters
    // the goodness property is super-segment monotonic

    unordered_map<char, int> runningFreq;
    int mini = LLONG_MAX;
    int runningUniqueCount = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (!runningFreq[str[r]]) {
            runningUniqueCount++;
        }
        runningFreq[str[r]]++;
        while (l <= r && runningUniqueCount == uniqueCount) {
            if (!(--runningFreq[str[l++]]))
                runningUniqueCount--;
        }
        if (l > 0) {
            int tmp = runningUniqueCount;
            if (!runningFreq[str[l - 1]])
                tmp++;
            if (tmp == uniqueCount) // the minimum length good segment ending at r is [l - 1, r]
                mini = min(mini, r - l + 2);
        }
    }

    if (mini == LLONG_MIN)
        mini = 0;
    cout << mini << endl;

    return 0;
}
```

---
*Documentation generated on 2025-08-21 21:14:46*
