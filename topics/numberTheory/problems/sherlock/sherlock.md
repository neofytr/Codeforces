# sherlock

```markdown
## Problem Documentation: Codeforces Problem 776B - Sherlock and his girlfriend

This document provides a comprehensive analysis of the provided C++ code, which solves Codeforces problem 776B, "Sherlock and his girlfriend" (https://codeforces.com/problemset/problem/776/B).

### 1. Problem Description (Inferred)

The problem asks to color the integers from 2 to *n* + 1 using at most two colors such that no two integers *x* and *y* that are both prime are colored the same color. The goal is to minimize the number of colors used. The output should first be the minimum number of colors used, followed by a space-separated list of the colors assigned to the integers from 2 to *n* + 1.

### 2. Approach Explanation

The code employs the following approach:

1.  **Sieve of Eratosthenes:**  It uses the Sieve of Eratosthenes to find all prime numbers within the range [2, *n* + 1]. This is the most efficient way to find primes within a given range.

2.  **Coloring Strategy:**
    *   If *n* is less than or equal to 1, it means we only need to color the numbers 2 which is prime. Thus, only one color (1) is needed. In general, if there are no composite numbers in the range, one color suffices. The code explicitly checks if the vector `primes` is empty after sieving. If empty, every number in range is prime and we can color them all with `1`.
    *   If *n* is greater than 1, it uses two colors. All prime numbers are assigned color 1. Then, the composite numbers are assigned color 2 to break any prime pair.

3.  **Composite number coloring:** composite numbers are colored with color 2.

### 3. Key Insights and Algorithmic Techniques Used

*   **Sieve of Eratosthenes:** The foundation of the solution is the efficient Sieve of Eratosthenes algorithm.  This allows for quickly determining primality for all numbers up to *n* + 1. The complexity of the Sieve of Eratosthenes is O(*n* log log *n*).

*   **Optimal Coloring:** The insight is that if *n* > 1, it's always possible to color with two colors. You can always color all primes with color 1.

*   **Reducing to Primality Test:** The problem reduces to efficiently testing the primality of each number in the range [2, *n* + 1].

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sieve of Eratosthenes: O(*n* log log *n*)
    *   The composite coloring is O(*n*), as it iterates over at most *n* numbers to find those divisible by any prime
    *   Printing the colors: O(*n*)

    Therefore, the overall time complexity is **O(*n* log log *n*)**.

*   **Space Complexity:**
    *   `isPrime` vector: O(*n*)
    *   `primes` vector: O(π(*n*)), where π(*n*) is the prime-counting function (the number of primes less than or equal to *n*). In general π(*n*) is O(*n*/log(*n*)).
    *   `div` vector : O(*n*)

    Therefore, the overall space complexity is **O(*n*)**.

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is a common practice in competitive programming to avoid integer overflow issues when dealing with potentially large input values. It changes the default `int` type to `long long`.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines optimize input/output operations by disabling synchronization between the C and C++ standard input/output streams and unlinking `cin` from `cout`.  This can significantly improve the execution time of the program, especially when dealing with large input.

*   **Vector Usage:** Vectors are used efficiently for storing prime numbers and marking numbers as prime or composite.

### 6. Edge Cases Handled

*   **n <= 1 (All Primes):** The code handles the case where *n* is equal to 1.  In this case, all the numbers in the range [2, n+1] are primes. So, only one color is sufficient. This is explicitly checked for with `if (primes.empty())`

```
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: sherlock
// URL: https://codeforces.com/problemset/problem/776/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<bool> isPrime(n + 2, true);
    vector<int> primes;
    for (int r = 2; r * r <= n + 1; r++)
        if (isPrime[r]) {
            primes.push_back(r);
            for (int j = r * r; j <= n + 1; j += r)
                isPrime[j] = false;
        }

    if (primes.empty()) {
        cout << 1 << endl;
        for (int r = 2; r <= n + 1; r++)
            cout << 1 << " ";
        cout << endl;
    } else {
        cout << 2 << endl;
        vector<int> div(n + 2, false);
        for (const int p : primes)
            for (int r = 2 * p; r <= n + 1; r += p)
                div[r] = true;

        for (int r = 2; r <= n + 1; r++)
            if (isPrime[r])
                cout << 1 << " ";
            else if (div[r])
                cout << 2 << " ";
            else
                cout << 1 << " ";
        cout << endl;
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-21 10:26:44*
