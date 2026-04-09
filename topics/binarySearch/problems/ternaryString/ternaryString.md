# ternaryString

```markdown
# Code Documentation: Ternary String Problem

## 1. Problem Description

The code solves the "Ternary String" problem (identified by the URL: [https://codeforces.com/problemset/problem/1354/B](https://codeforces.com/problemset/problem/1354/B)). The problem asks to find the length of the shortest contiguous substring of a given string `s` consisting of digits '1', '2', and '3', such that the substring contains at least one occurrence of each of the digits '1', '2', and '3'. If no such substring exists, the output should be 0.

## 2. Approach Explanation

The solution employs a sliding window technique to efficiently find the shortest substring that satisfies the given condition.  The core idea is:

1.  **Initialization:**  Initialize two pointers, `left` and `right`, representing the start and end of the sliding window. Also, initialize counters `countOne`, `countTwo`, and `countThree` to track the occurrences of '1', '2', and '3' within the current window. Initialize `mini` to `LLONG_MAX` to store the minimum substring length found so far.

2.  **Expanding the Window:** The `right` pointer is incremented to expand the window until the window contains at least one occurrence of each digit ('1', '2', '3').

3.  **Shrinking the Window:** Once the window contains all three digits, the `left` pointer is incremented to shrink the window. As the `left` pointer moves, the corresponding count of the digit at `str[left]` is decremented.  The minimum length `mini` is updated with the current window size (`right - left`) at each valid window.

4.  **Iteration:** Steps 2 and 3 are repeated until the `left` pointer reaches the end of the string.

5.  **Result:** If `mini` remains `LLONG_MAX` after the entire process, it means no valid substring was found, and the output is 0. Otherwise, the output is the value of `mini`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The sliding window technique is crucial for efficiently searching for the shortest substring. It avoids redundant computations by reusing information from the previous window.  It is useful when the problem requires analyzing contiguous substrings.
*   **Frequency Counting:** The `countOne`, `countTwo`, and `countThree` variables maintain the frequencies of each digit within the current window. This allows for quick checking of whether the window satisfies the condition of containing at least one of each digit.
*   **Minimum Tracking:**  The `mini` variable is used to keep track of the minimum length of a valid substring encountered so far.  Initializing it with a large value (`LLONG_MAX`) ensures that the first valid substring's length will always be smaller.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the length of the input string.  Both `left` and `right` pointers traverse the string at most once.
*   **Space Complexity:** O(1). The solution uses a constant amount of extra space for variables like `left`, `right`, `countOne`, `countTwo`, `countThree`, and `mini`.

## 5. Important Code Patterns or Tricks Used

*   **`#include <bits/stdc++.h>`:** Includes most standard C++ headers, which can be convenient, but generally considered bad practice in professional settings because of increased compile times and potential for namespace pollution.
*   **`#define int long long`:**  This redefines `int` to `long long`, allowing for a larger range of integer values. This is a common practice in competitive programming to prevent integer overflow issues.  It's crucial to include `int32_t main()` instead of `int main()` to prevent a compilation error.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines optimize input/output by disabling synchronization between the C and C++ standard input/output streams and unlinking `cin` from `cout`, which can significantly improve the execution time.

## 6. Edge Cases Handled

*   **No Valid Substring:** The code handles the case where no substring contains all three digits by initializing `mini` to `LLONG_MAX` and checking if it remains unchanged after the sliding window process. If `mini` is still `LLONG_MAX`, the output is 0.
*   **Empty String:** While not explicitly checked, the code should technically handle the empty string case correctly. The `while` loops will not execute, and `mini` will remain `LLONG_MAX`, resulting in an output of 0. However, adding an explicit check for an empty string at the beginning can improve code clarity.

```cpp
if (str.empty()) {
    cout << 0 << endl;
    return;
}
```

This clarifies the intention and handles a potential edge case more explicitly.

* **Minimum Possible Length:** The code correctly finds the *shortest* such substring, not just any substring containing all digits.  The shrinking of the window is critical for this.
```

## Original Code
```cpp
#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define int long long

// Problem: ternaryString
// URL: Not provided
// Difficulty: https://codeforces.com/problemset/problem/1354/B
// Tags:
// Strategy:

void solve() {
    string str;
    cin >> str;

    int n = (int)str.length();
    // we are to find the length of the shortest contiguous substring of s that contains 1, 2, 3 atleast once
    int left = 0;
    int right = 0;
    int countOne = 0;
    int countTwo = 0;
    int countThree = 0;

    int mini = LLONG_MAX;
    while (left < n) {
        while (right < n && (!countOne || !countTwo || !countThree)) {
            if (str[right] == '1')
                countOne++;
            else if (str[right] == '2')
                countTwo++;
            else
                countThree++;
            right++;
        }

        if (countOne && countTwo && countThree) {
            mini = min(mini, right - left);
        }
        if (str[left] == '1')
            countOne--;
        else if (str[left] == '2')
            countTwo--;
        else
            countThree--;
        left++;
    }

    if (mini == LLONG_MAX)
        cout << 0 << endl;
    else
        cout << mini << endl;
    return;
}

int32_t main() {
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
*Documentation generated on 2025-08-11 07:27:49*
