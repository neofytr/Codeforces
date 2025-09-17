# fib

```markdown
## Documentation of Fibonacci Finding Easy Solution

This document analyzes a C++ solution for the "Fibonacci Finding (easy)" problem on HackerRank: [https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem](https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem).

### 1. Problem Description

The problem asks to calculate the nth Fibonacci number modulo (10^9 + 7), given the first two Fibonacci numbers (f(0) = a and f(1) = b) and the index n. The Fibonacci sequence is defined as:

*   f(0) = a
*   f(1) = b
*   f(r) = f(r - 1) + f(r - 2) for r >= 2

The input consists of a number of test cases `t`, and for each test case, three integers: `a`, `b`, and `n`. The task is to output f(n) modulo (10^9 + 7) for each test case.

### 2. Approach Explanation

The solution uses matrix exponentiation to efficiently calculate the nth Fibonacci number. The core idea is to represent the Fibonacci recurrence relation as a matrix multiplication:

```
| f(n+1) |   | 0  1 |   | f(n)   |
| f(n+2) | = | 1  1 | * | f(n+1) |
```

This can be generalized to:

```
| f(n)   |   | 0  1 |^(n-1)   | f(1)   |
| f(n+1) | = | 1  1 |         | f(0)   |
```

Then f(n+1) is calculated via matrix exponentiation and multiplication with initial values `a` and `b`.

1.  **Base Cases:** Handles the base cases for n = 0 and n = 1 directly, returning `a % MOD` and `b % MOD`, respectively.
2.  **Transformation Matrix:** Defines the transformation matrix `T = {{0, 1}, {1, 1}}`.
3.  **Matrix Exponentiation:** Uses the `exp` function to calculate `T^(n-1)` efficiently using binary exponentiation.  This avoids performing n-1 matrix multiplications directly.
4.  **Matrix Multiplication:** Multiplies the initial vector {a, b} with the result of the matrix exponentiation to get {f(n-1), f(n)}. The necessary element to calculate f(n) modulo MOD is taken from the product.
5.  **Modulo Arithmetic:** Applies the modulo operator (%) at each step of the matrix multiplication and exponentiation to prevent integer overflow and maintain the result within the desired range.

### 3. Key Insights and Algorithmic Techniques Used

*   **Matrix Exponentiation:**  This is the central technique.  It allows calculating the nth term of a linear recurrence in logarithmic time. The key idea is to represent the recurrence relation as a matrix multiplication, then use binary exponentiation to compute the nth power of the matrix.
*   **Binary Exponentiation (Exponentiation by Squaring):**  Used to efficiently compute `T^(n-1)`. It repeatedly squares the base matrix and multiplies it with the result only if the corresponding bit in the binary representation of the exponent is 1.
*   **Modulo Arithmetic:** Essential for preventing integer overflow when dealing with large Fibonacci numbers.  The modulo operator is applied after each multiplication and addition to keep the intermediate results within the `MOD` range.  This utilizes the property `(a * b) % MOD = ((a % MOD) * (b % MOD)) % MOD` and `(a + b) % MOD = ((a % MOD) + (b % MOD)) % MOD`.
*   **Recurrence Relation Representation:**  The crucial step is recognizing that the Fibonacci sequence can be expressed as a matrix multiplication. This transformation allows the use of the matrix exponentiation technique.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   `mul` (matrix multiplication): O(sz^3) where sz is matrix size.  In this case, O(2^3) = O(8), which is constant time.
    *   `exp` (matrix exponentiation): O(log n) matrix multiplications.  Since matrix multiplication is O(1), the exponentiation is O(log n).
    *   Main loop (processing test cases): O(t * log n), where t is the number of test cases and n is the input index.
    *   Therefore, the overall time complexity is **O(t log n)**.

*   **Space Complexity:**
    *   `mul` and `exp`: create new matrices. However, the matrix size is always 2x2, so the memory used is constant for each matrix multiplication.
    *   The space complexity is **O(1)** because only a constant amount of extra memory is used for storing matrices and intermediate results.

### 5. Important Code Patterns or Tricks Used

*   **`#define` macros:** These are used for brevity and readability.  `#define int long long` can prevent overflow issues, given constraints that fit into 64 bit int. `#define MOD (1000000000 + 7)` defines the modulo value.  `#define REP(var, mx) for (int var = 0; var < mx; var++)` provides a concise way to write loops. `#define MAT vector<vector<int>>` defines matrix type.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between the C and C++ standard input/output streams, and it unties `cin` from `cout`, leading to faster input/output operations. This is crucial for competitive programming where time limits are strict.
*   **Early Returns for Base Cases:** Handling `n = 0` and `n = 1` at the beginning of the `while(t--)` loop optimizes for commonly provided cases, preventing unnecessary calculations.

### 6. Any Edge Cases Handled

*   **n = 0 and n = 1:** The solution explicitly handles these cases directly with conditional statements.
*   **Modulo Arithmetic:**  The code applies the modulo operator (%) throughout the calculations to prevent integer overflow, especially during the matrix multiplication steps.  This ensures that the final result is within the specified range (0 to 10^9 + 6).

```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)
#define REP(var, mx) for (int var = 0; var < mx; var++)
#define MAT vector<vector<int>>

// Problem: fib
// URL: https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem
// Difficulty: medium
// Tags:
// Strategy:

MAT mul(const MAT &m1, const MAT &m2) {
    const int sz = m1.size();
    MAT res(sz, vector<int>(sz));
    REP(row, sz) REP(col, sz) {
        int elt = 0;
        REP(itr, sz) elt = (elt + ((m1[row][itr] % MOD) * (m2[itr][col] % MOD)) % MOD) % MOD;
        res[row][col] = elt;
    }
    return res;
}

MAT exp(MAT base, int pw) {
    const int sz = base.size();
    MAT res(sz, vector<int>(sz));
    REP(r, sz) res[r][r] = 1;

    while (pw) {
        if (pw & 1)
            res = mul(res, base);
        base = mul(base, base);
        pw >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int a, b, n;
        cin >> a >> b >> n;
        // f(0) = a and f(1) = b
        // f(r) = f(r - 1) + f(r - 2) for r >= 2
        // f(r + 2) = f(r + 1) + f(r) for r >= 0

        // { f(0) f(1) } * T^(n - 1) = { f(n - 1) f(n) }

        if (!n) {
            cout << a % MOD << endl;
            continue;
        }
        if (n == 1) {
            cout << b % MOD << endl;
            continue;
        }

        const MAT T = {{0, 1}, {1, 1}};
        const MAT res = exp(T, n - 1);
        cout << (((a % MOD) * res[1][0]) % MOD + ((b % MOD) * res[1][1]) % MOD) % MOD << endl;
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-17 13:21:03*
