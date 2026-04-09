# excitingBets

```markdown
# Competitive Programming Solution Documentation

This document provides a comprehensive analysis of the provided C++ code, focusing on the algorithmic techniques and problem-solving strategies employed.

## 1. Problem Description (Exciting Bets)

Based on the code and the comment `// Problem: excitingBets // URL: https://codeforces.com/problemset/problem/1543/A`, the problem is likely "Exciting Bets" from Codeforces (problem 1543A).  Given two integers `a` and `b`, the goal is to maximize their greatest common divisor (GCD) after possibly adding the same integer to both `a` and `b`. The problem asks us to find the *maximum possible GCD* and the *minimum number of moves* required to achieve that maximum GCD.

## 2. Approach Explanation

The core idea behind the solution lies in understanding the properties of the GCD.

*   **GCD Invariance:**  `gcd(a, b) = gcd(a, b + k) = gcd(a + k, b) = gcd(a + k, b + k)` for any integer *k*.  This means that adding a constant to both `a` and `b` doesn't change their GCD, only their values.

*   **Difference Matters:** The key observation is that `gcd(a + k, b + k)` is a divisor of `(a + k) - (b + k) = a - b`.  Therefore, the maximum possible GCD is `|a - b|` (the absolute difference between `a` and `b`).  This is because the greatest common divisor of any two numbers can be at most their difference.

*   **Finding the Minimum Moves:** To achieve this maximum GCD (which is `l = |a - b|`), we need to find the smallest `k` such that both `a + k` and `b + k` are divisible by `l`.  Equivalently, we want to find the smallest `k` such that `(a + k) % l == 0` and `(b + k) % l == 0`. This is equivalent to finding a value to add to `min(a, b)` (call it `B`) such that `(B + k) % l == 0`.  This `k` is simply the remainder when `B` is divided by `l`, or its complement: `min(B % l, l - (B % l))`.

## 3. Key Insights and Algorithmic Techniques Used

*   **GCD Properties:**  The core insight revolves around the property of the GCD remaining invariant when a constant is added to both numbers.  This allows us to reduce the problem to finding the maximum possible GCD, which is the absolute difference between the original numbers.

*   **Modulo Arithmetic:** Modulo arithmetic is used to calculate the minimum number of moves needed to make both numbers divisible by their difference.

*   **Maximization and Minimization:** The problem requires maximizing the GCD and minimizing the number of moves.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(1) - The code performs a constant number of arithmetic operations. The `max` and `min` functions take constant time.
*   **Space Complexity:** O(1) - The code uses a constant amount of extra space to store variables.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization is crucial in competitive programming to improve the input/output speed of the program, preventing synchronization between C's `stdio` and C++'s `iostream`.
*   **`#define int long long`:** This macro redefines `int` as `long long` to prevent integer overflow, especially important when dealing with potentially large numbers. This can avoid unexpected runtime errors.
*   **Using `min(B % l, l - (B % l))` for optimal move calculation:** The solution computes the remainder `B % l` which tells us how much we need to increment B to make it divisible by l. However, we also need to consider the case where we are "closer" to reaching a multiple of l from *below* B by decrementation than we are from above. Thus the `min` allows us to choose the *minimum* increment/decrement that yields a multiple of `l`.

## 6. Edge Cases Handled

*   **Equal Numbers:** The code correctly handles the case when `a == b`. In this case, the maximum possible GCD is simply `a` (or `b`), and no moves are needed.  The output is `0 0`.

*   **Zero Difference:** While not explicitly handled, the code functions correctly when the difference `l = A - B` is zero since the logic is only entered if A != B. The problem constraints probably disallow this case, but the code would fail with division by zero. A check for (A == B) first neatly deals with this implicit case.

## Summary

The provided code efficiently solves the "Exciting Bets" problem by leveraging GCD properties and modulo arithmetic. The solution is well-optimized for performance, employs important competitive programming techniques, and handles the base case correctly. The core insight lies in recognizing that the maximum achievable GCD is the absolute difference between the two numbers and then minimizing the moves required to attain this GCD.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: excitingBets
// URL: https://codeforces.com/problemset/problem/1543/A
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;

        int A = max(a, b);
        int B = min(a, b);

        if (A == B)
            cout << "0 0\n";
        else {
            int l = A - B;
            int r = B % l;

            cout << l << " " << min(r, l - r) << endl;
        }
    }    
    return 0;
}
```

---
*Documentation generated on 2025-09-30 12:08:53*
