# tprimes

```markdown
# Codeforces Problem 230B: T-primes - Solution Analysis

This document analyzes a C++ solution to the Codeforces problem 230B: T-primes, available at [https://codeforces.com/problemset/problem/230/B](https://codeforces.com/problemset/problem/230/B).

## 1. Problem Description

The problem asks to determine, for each given number `x` in an input array, whether it's a "T-prime". A T-prime is a number that has exactly three distinct positive divisors. For example, 4 is a T-prime (divisors: 1, 2, 4), while 9 is also a T-prime (divisors: 1, 3, 9). 6 is not a T-prime (divisors: 1, 2, 3, 6).  The input consists of `n` numbers, and the program needs to output "YES" if a number is a T-prime and "NO" otherwise.

## 2. Approach Explanation

The key idea is that a number `x` has exactly three divisors if and only if it is the square of a prime number.  Here's the reasoning:

*   If `x` is a prime number, its divisors are 1 and itself, so it only has two divisors.
*   If `x` is a composite number (not prime and not 1) and can be factored into two distinct primes `p` and `q`, then its divisors are 1, `p`, `q`, and `x`, so it has four divisors. In general, composite numbers will have more than three divisors.
*   If `x = p^2` where `p` is a prime number, then its divisors are 1, `p`, and `p^2` (which is `x`), totaling three divisors.
*   If `x = p^k` where `p` is prime and `k > 2`, it will have more than three divisors (1, p, p^2, ..., p^k).
*   If `x` has more than one prime factor (e.g., `x = p^a * q^b`), it will also have more than three divisors.

Therefore, the solution first generates a list of primes up to a certain limit (1000000 in this case) using the Sieve of Eratosthenes. Then, for each input number `val`, it checks:

1.  If `val` is 1, it's not a T-prime.
2.  If `val` is a perfect square. If not, it's not a T-prime.
3.  If the square root of `val` is a prime number (according to the precomputed prime list).  If so, `val` is a T-prime.

## 3. Key Insights and Algorithmic Techniques Used

*   **T-primes and Squares of Primes:** The crucial insight is the mathematical property that a number has exactly three divisors if and only if it's the square of a prime. This transforms the problem from counting divisors to checking for primality of the square root.
*   **Sieve of Eratosthenes:**  The Sieve of Eratosthenes is an efficient algorithm for generating a list of prime numbers up to a given limit. This is precomputed to quickly check if the square root of a number is prime.
*   **Optimization with Square Root:** The code optimizes the process by first checking if the input number is a perfect square. This avoids unnecessary primality checks if the number is not a perfect square, as the square root has to be integer for our condition.
*   **Precomputation:**  The prime numbers are precomputed using the sieve and stored in a boolean array. This allows for constant-time primality checks during the main loop.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sieve of Eratosthenes: O(N log log N), where N is the upper limit for generating primes (1000000 in this case).
    *   Checking each input number: O(1) (dominated by the square root calculation and array access which is effectively constant time).
    *   Overall, the time complexity is dominated by the sieve: O(N log log N) + O(n), where n is the number of input values to check and N is the sieve upper bound. As `N` is fixed, it reduces to `O(n)`. Since n is likely to be bigger than `N log log N`, it is `O(n)` effectively after the sieve. However, you can see it as precomputation taking `O(N log log N)`.
*   **Space Complexity:**
    *   `primes` array: O(N), where N is the upper limit for prime generation (1000000).
    *   `arr` vector: O(n), where n is the number of input values.
    *   Overall: O(N + n). As `N` is fixed, it boils down to `O(n)`, same reasoning as with time complexity.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large numbers. The problem likely involves large inputs.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique in C++ to speed up input/output by disabling synchronization with the standard C input/output streams.
*   **Boolean Array for Prime Numbers:** The `primes` array serves as a lookup table, providing a fast way to determine if a number is prime.
*   **Direct Square Root Check:**  `sq * sq != val` is a concise way to determine if `val` is a perfect square.

## 6. Any Edge Cases Handled

*   **Input Value 1:** The code explicitly handles the case where the input number is 1, which is not considered a T-prime.
*   **Non-Perfect Squares:** The code checks if the input is a perfect square. This is crucial, as the square root must be an integer for the number to be a potential T-prime.
*   **Implicitly, Prime Generation Limit:** The Sieve of Eratosthenes implementation is limited to `1000000`. This indirectly limits the input values such that the square root of the largest possible input needs to be less than or equal to `1000000`, or the maximum possible input will be (1000000)^2 which is 10^12. Considering we're using `long long` which has a maximum limit near 10^18, it doesn't limit the maximum input value. It limits the maximum value we can determine primality, as we cannot go outside the bound of the precomputed `primes` array.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: tprimes
// URL: https://codeforces.com/problemset/problem/230/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> primes(1000000 + 1, true);
    for (int r = 2; r <= 1000000; r++)
        if (primes[r]) {
            for (int j = 2 * r; j <= 1000000; j += r)
                primes[j] = false;
        }

    for (const int val : arr) {
        if (val == 1) {
            cout << "NO\n";
            continue;
        }
        const int sq = sqrt(val);
        if (sq * sq != val) {
            cout << "NO\n";
            continue;
        }
        if (primes[sq])
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-12 18:28:21*
