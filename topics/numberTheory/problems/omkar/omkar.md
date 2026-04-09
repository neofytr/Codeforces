# omkar

```markdown
# Code Documentation: Omkar and Last Class of Math (Codeforces 1372B)

This document provides a detailed analysis of the provided C++ code solution for the "Omkar and Last Class of Math" problem on Codeforces (problem 1372B, available at [https://codeforces.com/problemset/problem/1372/B](https://codeforces.com/problemset/problem/1372/B)).

## 1. Problem Description (Inferred)

The problem asks us to find two integers, `a` and `b`, such that `a + b = n` and the least common multiple (LCM) of `a` and `b` is minimized.  More specifically, the goal is to decompose a given integer `n` into two numbers such that one of those numbers equals the biggest possible factor of `n` which is less than `n` itself.

## 2. Approach Explanation

The solution iterates through all possible divisors of `n` up to the square root of `n`. For each divisor `r`, it checks if `r` divides `n`. If it does, then both `r` and `n / r` are divisors of `n`.

For each divisor `r`, the solution considers two possible values for `a`: `r` and `n / r`. It then calculates the corresponding value of `b` as `n - a`.  The problem aims to minimize the LCM(a, b). It uses the fact that, given a + b = n, maximizing one of a or b minimizes the LCM, because the LCM becomes a multiple of `n` for smaller `a` and `b`. Therefore, the code is minimizing the minimum between a and b which is equivalent to maximizing the other.

The variable `mini` stores the largest possible divisor of `n` that's less than `n`. Then it prints `mini` and `n - mini`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Divisor Iteration:** The code efficiently finds all divisors of `n` by iterating only up to the square root of `n`. This optimization significantly reduces the time complexity.
*   **LCM and GCD Relationship:** Although not explicitly calculated in the code, the approach relies on the implicit relationship between LCM and GCD. Given `a` and `b`, LCM(a, b) = (a * b) / GCD(a, b).  The key idea is to maximize a divisor, and therefore to maximize `min(a,b)` which maximizes the GCD, hence minimizes the LCM. By extension, the logic implicitly aims to make one number a large factor of `n` so that the LCM(a,b) is small.
*   **Optimization:**  The problem is tackled by finding the smallest divisor greater than 1 and subtracting that divisor from N to generate the two terms. Iterating over square root of n is more efficient that searching every integer from 1 to n.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The loop iterates up to the square root of `n`.  Therefore, the time complexity is O(sqrt(n)) for each test case. The `gcd` function, although included in the code, is not used within the main logic which dictates that the overall time complexity is `O(t * sqrt(n))`, where `t` is the number of test cases.
*   **Space Complexity:** The code uses a few integer variables. Therefore, the space complexity is O(1), i.e., constant space.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This preprocessor directive changes the default `int` data type to `long long`. This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large numbers. This is important for the problem, where the numbers could be up to 10^9, and multiplying them can exceed the range of a standard `int`.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to speed up input/output operations by disabling synchronization between the C++ standard input/output streams and the C standard input/output streams. This can significantly improve the execution time of the code, especially when dealing with large input datasets.
*   **Iterating to Square Root:** The iteration only proceeds up to `sqrt(n)` because for every divisor `i <= sqrt(n)`, the quotient `n/i >= sqrt(n)`. This optimizes the process of finding divisors.

## 6. Any Edge Cases Handled

*   The loop `for (int r = 1; r * r <= n; r++)` correctly handles the case when `n` is a perfect square. If `n` is a perfect square, the divisor `sqrt(n)` will be considered only once.

## Summary

The code provides an efficient solution for the "Omkar and Last Class of Math" problem. It leverages the properties of divisors and the relationship between LCM and GCD to find the optimal decomposition of `n`. The code is well-optimized and avoids potential integer overflow issues by using `long long` and optimizing I/O.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: omkar
// URL: https://codeforces.com/problemset/problem/1372/B
// Difficulty: medium
// Tags:
// Strategy:

int gcd(const int a, const int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int mini = LLONG_MAX;
        for (int r = 1; r * r <= n; r++) {
            if (!(n % r)) {
                int divOne = r;
                int divTwo = n / r;

                if (n - r >= 1)
                    mini = min(mini, n - r);
                if (n - n / r >= 1)
                    mini = min(mini, n - n / r);
            }
        }
        cout << mini << " " << n - mini << endl;
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-19 15:21:51*
