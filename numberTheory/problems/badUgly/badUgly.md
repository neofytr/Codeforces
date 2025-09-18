# badUgly

```markdown
# Codeforces Problem 1326A - badUgly: Solution Analysis

This document provides a comprehensive analysis of the provided C++ code, which solves the Codeforces problem 1326A, titled "badUgly."

## 1. Problem Description

The problem (available at [https://codeforces.com/problemset/problem/1326/A](https://codeforces.com/problemset/problem/1326/A)) asks to find an n-digit number that is not divisible by any of its digits. If no such number exists, output -1.

## 2. Approach Explanation

The code implements a simple and effective strategy:

*   **Handle the base case (n = 1):** If `n` is 1, no single-digit number satisfies the condition (since any single digit number is divisible by itself). Thus, the code outputs `-1`.

*   **Construct a valid number for n > 1:** If `n` is greater than 1, the code generates a number consisting of the digit `2` followed by `n-1` instances of the digit `3`. This number works because:

    *   The number is guaranteed to contain the digits 2 and 3.
    *   The sum of digits will be (2 + 3*(n-1)) = (3n - 1). This sum is not guaranteed to be divisible by 3.
    *   The digits of this number are all 2's and 3's. We need to check if the number is divisible by 2 or 3. Since the number will not always be divisible by 2 or 3, then we can ensure that is not divisible by its digits.

    Specifically, concatenating a '2' followed by `n-1` '3's gives a number that is *unlikely* to be divisible by either 2 or 3. If the number constructed is divisible by 2, then its last digit must be divisible by 2, therefore it must contain the digit '2'.  if the number is divisible by 3, then the sum of its digits must be divisible by 3.
    To prove the solution is correct, we can see if an n-digit number composed of `n-1` 2's and 1 '3' is divisible by any of it's digits, which would require that it be divisible by 2.  Any such number must end in '2'.  For n = 2, the number would be '32' which is divisible by 2.
    If instead the number if built of one 2 and `n-1` 3's, the divisibility by 2 requires that the final digit be '2'. If the number ends in 2, we can say for n=2, the number '32' is divisible by 2. If not, then the constructed number is of the form "23333...", where it is unlikely to be divisible by 2 or 3.

## 3. Key Insights and Algorithmic Techniques Used

*   **Construction:** The core idea is to *construct* a valid number directly instead of searching or testing.  This approach leverages domain knowledge (divisibility rules) to quickly create a valid solution.
*   **Greedy approach:** Appending the digit 3 greedily after the initial 2 generally provides an answer.
*   **Edge Case Handling:** The special case of `n = 1` is explicitly handled because no solution is possible in that case.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The code iterates `t` times, where `t` is the number of test cases. Inside the loop, it prints `n` digits. Therefore, the time complexity is O(t * n).

*   **Space Complexity:** The code uses a constant amount of extra space, regardless of the input size `n` or `t`. Thus, the space complexity is O(1).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a common optimization technique in competitive programming to disable synchronization between C++ streams and the standard C input/output streams. It significantly speeds up input and output operations.
*   **`#define int long long`:** This redefines the `int` data type to `long long`. This is a safeguard to prevent integer overflow issues, especially when dealing with large numbers. The use of `int32_t main()` reflects that we should write `main` as if `int` were still 32 bits, even though it now stores 64-bit numbers.

## 6. Any Edge Cases Handled

*   The code explicitly handles the edge case where `n = 1`.  This is crucial because no 1-digit number is not divisible by itself, so the program must output `-1` in this case. Other edge cases (e.g., n=0) aren't tested and implicitly fail since the input is strictly positive.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: badUgly
// URL: https://codeforces.com/problemset/problem/1326/A
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1)
            cout << -1 << endl;
        else {
            cout << 2;
            for (int r = 1; r <= n - 1; r++)
                cout << 3;
            cout << endl;
        }
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-18 20:51:50*
