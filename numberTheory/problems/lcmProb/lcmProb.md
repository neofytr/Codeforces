# lcmProb

```markdown
# Codeforces Problem 1389A - LCM Problem Documentation

This document analyzes the provided C++ solution for Codeforces problem 1389A, titled "LCM Problem". The problem URL is: [https://codeforces.com/problemset/problem/1389/A](https://codeforces.com/problemset/problem/1389/A).

## 1. Problem Description (Inferred)

Given two integers `l` and `r`, find two integers `x` and `y` such that:

*   `l <= x < y <= r`
*   `lcm(x, y)` is in the range `[l, r]`.

If no such `x` and `y` exist, output "-1 -1".

## 2. Approach Explanation

The solution leverages a key property: if `y = 2 * x`, then `lcm(x, y) = 2 * x = y`. Therefore, we need to find an `x` such that `l <= x` and `2 * x <= r`. If such an `x` exists, then `x` and `2 * x` are a valid solution because `l <= x < 2 * x <= r`, and `lcm(x, 2 * x) = 2 * x` which is within the range `[l, r]`.  If `2 * l > r`, it means that no such `x` can exist because even if we choose the smallest possible `x = l`, then `2 * x` is greater than `r`, violating the condition `2 * x <= r`.

## 3. Key Insights and Algorithmic Techniques Used

The core insight is understanding the relationship between a number and its double concerning their Least Common Multiple (LCM).  The algorithm uses the simple condition `y = 2x` to guarantee that the LCM is equal to `y`. This transforms the problem from finding two numbers that satisfy LCM constraints to finding one number `x` such that `l <= x` and `2x <= r`. This simplification allows for a direct check and solution.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(1) per test case. The solution only performs a constant number of arithmetic operations and comparisons. Since there are `t` test cases, the overall time complexity is O(t).

*   **Space Complexity:** O(1). The solution uses a constant amount of extra space, regardless of the input values.

## 5. Important Code Patterns or Tricks Used

*   **Fast I/O:** `ios_base::sync_with_stdio(false); cin.tie(NULL);` This optimization disables synchronization between C++ streams and the standard C library, which can significantly improve the input/output performance, especially in problems with a large number of input/output operations.
*   **`#define int long long`:** This redefines the `int` type to `long long`. This is a common practice in competitive programming to avoid integer overflow issues when dealing with large numbers.

## 6. Edge Cases Handled

The solution effectively handles the edge case where no solution exists.  If `2 * l > r`, the code outputs "-1 -1", indicating that it's not possible to find `x` and `y` within the given constraints satisfying the problem requirements. In particular, if the input values are such that choosing the smallest possible x, i.e., l, leads to 2*l exceeding r, the code correctly outputs -1 -1 because no value of `x` in the range `[l, r]` would satisfy `2x <= r`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: lcmProb
// URL: https://codeforces.com/problemset/problem/1389/A
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;

        if (2 * l > r)
            cout << -1 << " " << -1 << endl;
        else 
            cout << l << " " << 2 * l << endl;
    }    
    return 0;
}
```

---
*Documentation generated on 2025-09-30 10:44:23*
