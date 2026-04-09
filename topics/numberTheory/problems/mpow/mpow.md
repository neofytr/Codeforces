# mpow

```markdown
# Matrix Power (MPOW) - SPOJ

## 1. Problem Description

This code solves the "[MPOW](https://www.spoj.com/problems/MPOW/)" problem on SPOJ (Sphere Online Judge). The problem asks us to compute the *n*-th power of a given square matrix and print the resulting matrix modulo (10<sup>9</sup> + 7).  The input consists of:

*   *T*: The number of test cases.
*   For each test case:
    *   *M*: The dimension of the square matrix (M x M).
    *   *N*: The power to which the matrix needs to be raised.
    *   The elements of the M x M matrix.

## 2. Approach Explanation

The core idea is to use the **exponentiation by squaring** technique (also known as binary exponentiation) to efficiently compute the matrix power.  This approach significantly reduces the number of matrix multiplications required compared to a naive, iterative method.  Instead of multiplying the matrix *N* times, we repeatedly square the matrix and only multiply it into the result when the corresponding bit in the binary representation of *N* is 1.

## 3. Key Insights and Algorithmic Techniques Used

*   **Matrix Multiplication:** The `mul` function performs matrix multiplication modulo (10<sup>9</sup> + 7).  It iterates through each element of the resulting matrix, computing the dot product of the corresponding row and column.  The modulo operation is applied after each multiplication and addition to prevent integer overflow.
*   **Exponentiation by Squaring (Binary Exponentiation):** The `exp` function implements the exponentiation by squaring algorithm.  It efficiently calculates `base^pow` by repeatedly squaring the `base` matrix and multiplying it into the result only when the corresponding bit in `pow` is set. This drastically reduces the number of matrix multiplications needed.
*   **Modulo Arithmetic:**  All calculations are performed modulo (10<sup>9</sup> + 7) to prevent integer overflow and ensure the result fits within the integer data type's range.
*   **Identity Matrix:** The `exp` function initializes the `res` matrix with the identity matrix. This is because any matrix raised to the power of 0 is the identity matrix.
*   **Bitwise Operators:** The `pow & 1` checks if the least significant bit of the power `pow` is 1. The `pow >>= 1` right-shifts `pow` by one bit, effectively dividing it by 2.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   `mul` function (Matrix Multiplication): O(M<sup>3</sup>)
    *   `exp` function (Matrix Exponentiation): O(M<sup>3</sup> * log N)  due to the binary exponentiation. The `mul` function is called O(log N) times.
    *   Overall (including input/output): O(T * M<sup>3</sup> * log N) where T is the number of test cases.
*   **Space Complexity:**
    *   `mul` function: O(M<sup>2</sup>) for storing the resulting matrix.
    *   `exp` function: O(M<sup>2</sup>) for storing the intermediate `res` and `base` matrices.
    *   Overall: O(M<sup>2</sup>) (dominated by the matrix storage)

## 5. Important Code Patterns or Tricks Used

*   **Macros:** The code uses macros like `REP(var, mx)` to simplify the loop syntax. This makes the code more concise and readable.
*   **Type Aliases:**  `Mat` is a type alias for `vector<vector<int>>`, making the code easier to understand and modify.
*   **Modulo Operator:**  The modulo operator (`%`) is consistently used throughout the calculations in `mul` to prevent integer overflow.
*   **ios_base::sync_with_stdio(false); cin.tie(NULL);:** These lines at the beginning of `main` are a standard optimization technique in C++ competitive programming to improve the input/output speed by decoupling the C and C++ standard input/output streams.
*   **`move(mat)`:** In the main function, `move(mat)` is used when calling `exp`. This potentially avoids an unnecessary copy of the large matrix, leading to a slight performance improvement, especially when `n` is large.

## 6. Edge Cases Handled

*   **pow < 0:** The code has a check `if (pow < 0) return Mat{};`.  Although not explicitly mentioned in the problem description of MPOW, handling negative powers can be useful in more general matrix exponentiation scenarios (which would involve matrix inversion, but this implementation returns an empty matrix in this case).
*   **pow == 0:** The code correctly handles the case where the power is 0 by returning the identity matrix. This is a crucial base case for the exponentiation by squaring algorithm.
*   **Modulo Arithmetic prevents overflow:** By consistently using modulo arithmetic, the code prevents integer overflows which can occur when dealing with large numbers during matrix multiplication.  The large matrix dimensions are also key to pushing calculations to potentially large intermediate values that need modulo to prevent problems.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mpow
// URL: https://www.spoj.com/problems/MPOW/
// Difficulty: medium
// Tags:
// Strategy:

#define Mat vector<vector<int>>
#define MOD (1000000000 + 7)
#define REP(var, mx) for (int var = 0; var < mx; var++)

Mat mul(const Mat &m1, const Mat &m2) {
    const int sz = m1.size();
    Mat res(sz, vector<int>(sz));

    REP(row, m)
    REP(col, m) {
        int elt = 0;
        for (int itr = 0; itr < sz; itr++)
            elt = (elt + ((m1[row][itr] % MOD) * (m2[itr][col] % MOD)) % MOD) % MOD;
        res[row][col] = elt;
    }
    return res;
}

Mat exp(Mat base, int pow) {
    const int sz = base.size();
    Mat res(sz, vector<int>(sz, 0));
    for (int r = 0; r < sz; r++)
        res[r][r] = 1; // identity matrix

    if (pow < 0)
        return Mat{};
    if (!pow)
        return res;
    while (pow) {
        if (pow & 1)
            res = mul(res, base);
        base = mul(base, base);
        pow >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> m >> n;

        Mat mat(m, vector<int>(m));
        REP(row, m) REP(col, m) cin >> mat[row][col];

        const Mat res = exp(move(mat), n);
        REP(row, m) {
            REP(col, m) cout << res[row][col] << " ";
            cout << endl;
        }
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-17 12:04:03*
