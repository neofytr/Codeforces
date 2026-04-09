# divisors

```markdown
# Problem: Divisors (Kattis)

**Problem URL:** [https://open.kattis.com/problems/divisors](https://open.kattis.com/problems/divisors)

**Problem Description:**

Given two integers *n* and *k*, where 0 ≤ *k* ≤ *n* ≤ 431, determine the number of divisors of the binomial coefficient  *nCk*  (n choose k).

**Approach Explanation:**

The core idea is to efficiently compute the prime factorization of *nCk*.  Since *nCk* = n! / (k! * (n-k)!), we can determine the prime factorization of *nCk* by subtracting the prime factorizations of k! and (n-k)! from the prime factorization of n!.

The code precomputes and stores the prime factorizations of *r*! for 2 ≤ *r* ≤ 431 in a vector of unordered maps, `pf`. `pf[r]` stores the prime factorization of *r*!.  This precomputation avoids redundant calculations within the main loop.

For each input *n* and *k*, the code calculates the prime factorization of *nCk* by subtracting the exponents of each prime factor in `pf[k]` and `pf[n-k]` from the corresponding exponents in `pf[n]`. Specifically, the exponent of a prime `p` in the prime factorization of *nCk* is given by:

`exponent(p, nCk) = exponent(p, n!) - exponent(p, k!) - exponent(p, (n-k)!)`

Finally, the number of divisors of *nCk* is computed by taking the product of (exponent + 1) for each prime factor in its prime factorization.

**Key Insights and Algorithmic Techniques Used:**

1. **Prime Factorization:** The fundamental concept is decomposing numbers into their prime factors.  Understanding how to efficiently calculate and store prime factorizations is crucial.

2. **Precomputation:** The prime factorizations of factorials are precomputed and stored.  This significantly reduces the time complexity for each query by avoiding repeated prime factorization calculations.  This is a standard dynamic programming technique.

3. **Binomial Coefficient Prime Factorization:** The key insight is to compute the prime factorization of  *nCk*  using the prime factorizations of factorials:  *nCk* = n! / (k! * (n-k)!). This is done by subtracting the exponents of prime factors.

4. **Number of Divisors:**  The number of divisors of a number with prime factorization p1^e1 * p2^e2 * ... * pn^en is given by (e1 + 1) * (e2 + 1) * ... * (en + 1).

**Time and Space Complexity Analysis:**

*   **Precomputation (Time):** O(MAXN * sqrt(MAXN)), where MAXN = 431.  The outer loop iterates from 3 to MAXN.  The inner loop iterates up to the square root of `r` for prime factorization. This is because to prime factorize a number `x`, we only need to check divisors up to `sqrt(x)`.
*   **Precomputation (Space):** O(MAXN * P), where P is the maximum number of distinct prime factors a number <= MAXN! can have, P = O(MAXN). This is because each `pf[r]` can store up to `r` prime factors. Therefore, overall space complexity is approximately O(MAXN^2).
*   **Query (Time):** O(P), where P is the number of distinct prime factors in n! or k! or (n-k)!.  Since the values of n,k are limited to 431, the number of primes considered is bounded. This is because we iterate through the prime factors present in `pf[n]`.
*   **Overall:** Due to the precomputation, the query time is quite efficient, and the dominating factor is the precomputation time.

**Important Code Patterns or Tricks Used:**

1.  **`#define int long long`:** This ensures that integer variables have a larger range, preventing potential overflow issues when calculating the number of divisors (especially since the exponents can be relatively large).

2.  **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimizes input/output operations by disabling synchronization between the C and C++ standard streams and unlinking `cin` from `cout`. This is a standard trick for improving performance in competitive programming.

3.  **`unordered_map<int, int>`:**  Using an unordered map to store the prime factorization allows for efficient access and modification of the exponents of prime factors.

4.  **Iterating through Prime Factors:** The code efficiently iterates through the prime factors present in `pf[n]` to compute the result. This is optimized because we only consider prime factors that are actually present in the prime factorization of n!.

**Edge Cases Handled:**

*   **0 ≤ k ≤ n ≤ 431:** The problem statement specifies the constraints, and the code is designed to handle values within this range. The precomputed factorials also limit it to these ranges.
*   The code correctly handles cases where k = 0 or k = n, as the corresponding `pf` values will be used to correctly compute the final result.

**Learning Points:**

*   This problem demonstrates the power of precomputation in solving problems that involve repeated calculations.
*   Understanding prime factorization and its applications is essential for many competitive programming problems.
*   Efficient data structures (like unordered maps) can significantly improve performance.
*   Paying attention to potential overflow issues is crucial, especially when dealing with factorials and exponents.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: divisors
// URL: https://open.kattis.com/problems/divisors
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 0 <= k <= n <= 431

    // pf[r] contains the prime factor map of r! for 2 <= r <= 431
    vector<unordered_map<int, int>> pf(432);
    pf[2][2] = 1;

    for (int r = 3; r <= 431; r++){ 
        int x = r;
        for (int d = 2; d * d <= x; d++)
            while(!(x % d))
                pf[r][d]++, x /= d;
        if (x > 1) pf[r][x]++;

        for (auto [p, cnt] : pf[r - 1])
            pf[r][p] += cnt;
    }
    
    int n, k;
    while(cin >> n >> k) {
        int res = 1;
        for (auto &[p, cnt] : pf[n]) {
            int left = cnt - pf[k][p] - pf[n - k][p];
            res *= (left + 1);
        }
        cout << res << endl;
    }    
    return 0;
}

```

---
*Documentation generated on 2025-10-01 19:12:21*
