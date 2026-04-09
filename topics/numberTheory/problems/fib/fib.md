# fib

```markdown
## Documentation of Fibonacci Finding (HackerRank) Solution

This document analyzes a C++ solution to the "Fibonacci Finding (easy)" problem on HackerRank, found at [https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem](https://www.hackerrank.com/challenges/fibonacci-finding-easy/problem).

### 1. Problem Description

The problem asks to calculate the n-th Fibonacci number given the first two Fibonacci numbers `a` and `b`.  Specifically, given `f(0) = a`, `f(1) = b`, and `f(r) = f(r-1) + f(r-2)` for `r >= 2`, we need to compute `f(n)` modulo `10^9 + 7`.  The value of `n`, `a` and `b` are given as inputs.  The problem involves multiple test cases.

### 2. Approach Explanation

The solution utilizes the matrix exponentiation method to calculate the n-th Fibonacci number efficiently. This method leverages the following matrix representation of the Fibonacci sequence:

```
| f(n+1) |   =   | 0  1 | ^ n * | f(1) |
| f(n)   |       | 1  1 |       | f(0) |
```

Here `f(0) = a` and `f(1) = b`. Therefore to obtain `f(n)`, we need to calculate the n-th power of the transformation matrix `T = {{0, 1}, {1, 1}}`.  Since we already have `f(0)` and `f(1)`, we can adjust the transformation to only compute T^(n-1) and multiply the result by the initial vector `{{a,b}}`.

The steps are:

1.  **Input:** Read the number of test cases `t`, and for each case, read `a`, `b`, and `n`.
2.  **Base Cases:** Handle `n = 0` and `n = 1` directly, outputting `a % MOD` and `b % MOD` respectively.
3.  **Matrix Exponentiation:** Calculate `T^(n-1)` using the `exp` function, which employs the binary exponentiation technique.
4.  **Matrix Multiplication:** Multiply the row vector `{{a, b}}` with the result of the exponentiation using the `mul` function.
5.  **Output:** Extract the element at `[0][1]` from the resulting matrix. This element represents f(n), which is then outputted modulo `MOD`.

### 3. Key Insights and Algorithmic Techniques Used

*   **Matrix Exponentiation:** The core idea is to represent the Fibonacci recurrence relation using a matrix, enabling us to calculate f(n) in logarithmic time complexity instead of the linear time complexity of a naive iterative/recursive implementation.  This works because repeated application of the recurrence relation can be expressed as repeated multiplication of the matrix.

*   **Binary Exponentiation:**  The `exp` function efficiently computes the power of the matrix by repeatedly squaring the base and multiplying it with the result based on the bits of the exponent. This significantly reduces the number of matrix multiplications required.

*   **Modular Arithmetic:** The code performs all calculations modulo `MOD (10^9 + 7)` to prevent integer overflow.  Crucially, the modulo operation is applied *during* the intermediate calculations within the matrix multiplication, not just at the final result. This ensures correctness.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   The `mul` function performs matrix multiplication in O(k * mxRow * mxCol) which is O(1) since the matrices are of fixed small size.
    *   The `exp` function, due to binary exponentiation, performs matrix multiplications O(log n) times. Thus, the `exp` function has a time complexity of O(log n).
    *   The main loop iterates `t` times. Inside the loop, most operations are O(1), and the dominant part is the call to `exp`.
    *   Therefore, the overall time complexity is O(t * log n).

*   **Space Complexity:**
    *   The `mul` and `exp` functions create new matrices, but their sizes are constant.
    *   The rest of the variables used are also of constant size.
    *   Therefore, the overall space complexity is O(1).

### 5. Important Code Patterns or Tricks Used

*   **`#define` macros:** The code uses `#define` macros for common operations like loops (`REP`) and the data type (`int` to `long long`), improving readability and brevity.  However, excessive use of macros can sometimes hinder debugging.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between C++ streams and the C standard input/output, which can significantly improve the input/output performance, especially for competitive programming problems with large inputs.
*   **Modular Arithmetic:** The use of modulo operator `% MOD` at *each step* of the calculation within the `mul` function is critical for preventing overflow and ensuring correctness.
*   **Data Type (`long long`):**  The use of `long long` (`int` is redefined as `long long`) is necessary to avoid potential integer overflows during calculations, especially when dealing with large Fibonacci numbers and multiplications within the matrix operations.

### 6. Edge Cases Handled

*   **n = 0 and n = 1:** The code explicitly handles the cases where `n` is 0 or 1, providing the correct initial values of the Fibonacci sequence. These are the base cases and are handled before the general matrix exponentiation. These base case checks prevent unnecessary calculations and potential issues when `n` is very small.
*   **Modular Arithmetic:**  The modulo operation addresses the potential overflow issue, preventing the output from being incorrect.
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

// multiplication of m1 and m2
// its assumed that these matrices are multiplicable
MAT mul(const MAT &m1, const MAT &m2) {
    const int mxRow = m1.size();
    const int mxCol = m2[0].size();
    const int k = m2.size();
    MAT res(mxRow, vector<int>(mxCol));
    REP(row, mxRow) REP(col, mxCol) {
        int elt = 0;
        REP(itr, k) elt = (elt + ((m1[row][itr] % MOD) * (m2[itr][col] % MOD)) % MOD) % MOD;
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
        const MAT r1 = {{a, b}};
        const MAT res = exp(T, n - 1);
        return mul(r1, res)[0][1];
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-17 16:43:21*
