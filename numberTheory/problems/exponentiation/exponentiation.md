# exponentiation

```markdown
# Exponentiation

## 1. Problem Description

The problem, as inferred from the code and comments (specifically, the URL `https://cses.fi/problemset/task/1095`), is the "Exponentiation" problem on CSES.  It requires calculating `a^b mod m` for multiple test cases, where `a` and `b` are integers and `m` is a large prime number (10^9 + 7 in this case). The task is to efficiently compute `a^b` modulo `MOD` for given pairs of `a` and `b`.

## 2. Approach Explanation

The solution utilizes the *binary exponentiation* (or exponentiation by squaring) algorithm to efficiently compute `a^b mod m`. This approach reduces the number of multiplications needed compared to a naive iterative approach.

The main idea is to express the exponent `b` as a sum of powers of 2.  For example, if `b = 13`, then `13 = 8 + 4 + 1 = 2^3 + 2^2 + 2^0`.  Therefore, `a^13 = a^(2^3) * a^(2^2) * a^(2^0)`.  This allows us to calculate `a^b` by iteratively squaring the base and multiplying the result when the corresponding bit in the binary representation of `b` is set.  Taking the modulus at each step prevents integer overflow.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Exponentiation (Exponentiation by Squaring):**  This is the core algorithmic technique.  It leverages the binary representation of the exponent to reduce the number of multiplications. This technique is crucial for handling large exponents efficiently.
*   **Modular Arithmetic:** The code correctly uses the modulo operator `%` after each multiplication to prevent integer overflows and keep the results within the desired range. This is necessary because `a^b` can be a very large number even if `a` and `b` are relatively small.  The properties of modular arithmetic allow this efficient calculation: `(a * b) % m = ((a % m) * (b % m)) % m`.
*   **Bitwise Operators:** The code uses bitwise operators (`&` and `>>`) for efficient manipulation of the exponent's binary representation.  `exp & 1` checks if the least significant bit of `exp` is set (equivalent to `exp % 2 == 1`), and `exp >>= 1` right-shifts `exp` by one bit (equivalent to `exp = exp / 2`).

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The `pow` function performs a loop that iterates a maximum of `log2(b)` times, where `b` is the exponent. Each iteration involves a constant number of arithmetic operations (multiplication, modulo, bitwise operations). Therefore, the time complexity of the `pow` function is O(log b).  The main function iterates `n` times, calling `pow` in each iteration.  Thus, the overall time complexity is O(n log b), where `n` is the number of test cases and `b` is the maximum value of the exponent in any test case.

*   **Space Complexity:** The space complexity is O(1). The algorithm uses only a few integer variables to store intermediate results.  The recursive calls, if any, are tail-recursive and can be optimized by compilers to avoid stack overflow.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This preprocessor directive changes the default `int` type to `long long`.  This is a common practice in competitive programming to prevent integer overflow, as the constraints often require larger integer ranges.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  This is a standard optimization technique used to speed up input/output operations in C++.  It disables synchronization between the C and C++ standard input/output streams and unties `cin` from `cout`, allowing `cin` to operate independently.

*   **Pre-calculating Modulo:**  While not explicitly done, it's good practice to pre-calculate the modulo value if used frequently and doesn't change. While in this case, it is a constant, it is still good to remember if `MOD` was a variable that can change each test case.

## 6. Any Edge Cases Handled

*   **`base = base % MOD;`:** This line handles the case where the base `a` is initially larger than or equal to `MOD`. Taking the modulo before entering the loop ensures that all intermediate calculations are performed with numbers smaller than `MOD`, preventing potential overflows.
*  **Exponent is 0:** The algorithm correctly handles the case when the exponent `b` is 0. The loop terminates immediately, and the function returns 1, which is the correct result for `a^0`.
*   **Mod Operation:** Taking mod every time during calculations ensures no overflows and the algorithm will still work with large numbers.

```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// Problem: exponentiation
// URL: https://cses.fi/problemset/task/1095
// Difficulty: easy
// Tags: 
// Strategy: 

int pow(int base, int exp) {
    int res = 1;
    base = base % MOD;
    while(exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, a, b;
    cin >> n;
    while(n--) {
        cin >> a >> b;
        cout << pow(a, b) << endl;
    }    
    return 0;
}
```

---
*Documentation generated on 2025-10-01 23:13:50*
