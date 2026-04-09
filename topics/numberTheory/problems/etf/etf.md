# etf

```markdown
# Problem: Euler Totient Function (ETF)

## 1. Problem Description

The problem, originating from SPOJ ([https://www.spoj.com/problems/ETF/](https://www.spoj.com/problems/ETF/)), asks us to compute the Euler Totient Function (ETF), also known as phi function, for multiple input numbers. Given an integer *n*,  φ(*n*) is the number of integers between 1 and *n* inclusive that are relatively prime to *n*.  The input consists of *t* test cases, where in each test case we are given an integer *n*, and we have to output φ(*n*). The constraints imply that 1 <= n <= 1,000,000.

## 2. Approach Explanation

The provided code uses a sieve-like approach to precompute the Euler Totient Function for all numbers up to `MAX = 1000000`.  This is an efficient way to handle multiple queries for the same range of input values. Specifically:

1.  **Precomputation:**  An array `phi` of size `MAX + 1` is initialized. Initially, `phi[i]` is set to `i` for all `i` from 1 to `MAX`.
2.  **Sieve:** The code then iterates from 2 to `MAX`. For each number `r`, if `phi[r] == r` (which implies that `r` is prime), it iterates through all multiples of `r` (starting from `r` itself) and updates the `phi` values. The update rule is `phi[j] -= phi[j] / r`. This update is based on the following property of the Euler Totient Function:

    If `p` is a prime factor of `n`, then φ(*n*) = φ(*n*/p) \* (p-1) OR  φ(*n*) = *n* \* (1 - 1/*p*).
    In our code φ(*j*) becomes φ(*j*) * (1 - 1/r) which is achieved by doing φ(*j*) -= φ(*j*)/r
3.  **Query Handling:** After the `phi` array is precomputed, the code reads the number of test cases `t`. For each test case, it reads an integer `n` and prints the precomputed value `phi[n]`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Euler Totient Function Property:** The core of the solution lies in understanding the property of the Euler Totient Function related to prime factorization. If *n* = *p*<sub>1</sub><sup>a1</sup> \* *p*<sub>2</sub><sup>a2</sup> \* ... \* *p*<sub>k</sub><sup>ak</sup>, where *p*<sub>i</sub> are distinct primes, then φ(*n*) = *n* \* (1 - 1/*p*<sub>1</sub>) \* (1 - 1/*p*<sub>2</sub>) \* ... \* (1 - 1/*p*<sub>k</sub>).  The code efficiently calculates this by iterating through primes and applying the reduction to their multiples.
*   **Sieve of Eratosthenes Adaptation:** The code employs a sieve-like approach similar to the Sieve of Eratosthenes. Instead of marking composite numbers, it updates the `phi` values for the multiples of each prime.
*   **Precomputation:** Precomputing the `phi` array allows us to answer multiple queries efficiently in O(1) time each after the initial precomputation, which is critical given the test case input.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   **Precomputation:** The precomputation takes O(*n* log log *n*) time, where *n* is `MAX`. This is due to the outer loop iterating from 2 to *n*, and the inner loop iterating through multiples of each number. The overall complexity of the sieve is known to be O(*n* log log *n*).
    *   **Query Handling:** Each query takes O(1) time because we simply look up the precomputed value.
    *   **Overall:** The total time complexity is dominated by the precomputation step, so it is O(*n* log log *n*) + *O(t)*, where *n* is MAX and *t* is number of test cases.  Since *n* is fixed, we can consider the time complexity to be O(*n* log log *n*) for precomputation and O(*t*) for query processing.

*   **Space Complexity:**
    *   The code uses an array `phi` of size `MAX + 1` to store the precomputed Euler Totient Function values. Therefore, the space complexity is O(`MAX`), which is O(n).

## 5. Important Code Patterns or Tricks Used

*   **Sieve-like precomputation:** Efficiently precomputing values for multiple queries. This is a crucial technique when dealing with a large number of queries that can be answered using precomputed data.
*   **Using prime numbers as the basis for computation:** Iterating from 2 to MAX and then skipping multiples of each number that is not prime optimizes the calculations. The condition `phi[r] == r` efficiently identifies primes.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimization disables synchronization between C++ streams and C streams, and disables tying of `cin` and `cout`, resulting in faster input/output.

## 6. Any Edge Cases Handled

*   The code implicitly handles the case where *n* = 1.  Initially, `phi[1]` is set to 1, which is the correct value of the Euler Totient Function for 1.

This documentation explains the provided C++ code's approach to solving the Euler Totient Function problem on SPOJ. It details the algorithm's core ideas, complexity, and significant coding practices.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: etf
// URL: https://www.spoj.com/problems/ETF/
// Difficulty: easy
// Tags: 
// Strategy: 

#define MAX 1000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    vector<int> phi(MAX + 1);
    for (int r = 1; r <= MAX; r++)
        phi[r] = r;

    for (int r = 2; r <= MAX; r++)
        if (phi[r] == r) // prime
            for (int j = r; j <= MAX; j += r)
                phi[j] -= phi[j] / r;

    while(t--) {
        int n;
        cin >> n;
        cout << phi[n] << endl;
    }    
    return 0;
}
```

---
*Documentation generated on 2025-10-02 18:42:32*
