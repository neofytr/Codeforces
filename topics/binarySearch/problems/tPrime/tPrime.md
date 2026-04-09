# tPrime

```markdown
## Documentation for T-Prime Solution

This document describes a solution to the "T-primes" problem on Codeforces (problemset/problem/230/B).

### 1. Problem Description (Inferred)

The problem asks us to determine whether a given positive integer is a T-prime.  A positive integer is considered a T-prime if it has exactly three distinct positive divisors.  The input consists of an integer `n`, followed by `n` integers. For each of the `n` integers, the program should output "YES" if the integer is a T-prime, and "NO" otherwise.

**Problem URL:** [https://codeforces.com/problemset/problem/230/B](https://codeforces.com/problemset/problem/230/B)

### 2. Approach Explanation

The solution is based on the following observations:

1.  A number has exactly three divisors if and only if it is the square of a prime number.  For example, if `p` is prime, then `p^2` has divisors `1`, `p`, and `p^2`.  Conversely, suppose `n` has three divisors: `1`, `d`, and `n`. Then `n/d` is also a divisor. Since there are only three distinct divisors, `d = n/d`, which implies `n = d^2`. Now, if `d` were not prime, it would have a divisor `k` (where `1 < k < d`), implying that `k` is also a divisor of `n` (as `k` divides `d`, and `d` divides `n`, `k` divides `n`).  But this would mean `n` has more than three divisors. Thus `d` must be prime.

2.  Therefore, to determine if a number `val` is a T-prime, we first check if it's a perfect square. If not, it can't be a T-prime.

3.  If `val` *is* a perfect square, let `sqroot` be its square root.  We then check if `sqroot` is a prime number.  If it is, then `val` is a T-prime.

### 3. Key Insights and Algorithmic Techniques Used

*   **Number Theory:** The core idea is based on the divisor properties of numbers.  The insight that T-primes are squares of prime numbers is crucial.
*   **Square Root Check:** Checking if a number is a perfect square using `sqroot * sqroot == val` is a standard technique.
*   **Primality Test Optimization:** The primality test only iterates up to the square root of the number being checked (`sqrt(x)`).  This is because if a number `x` has a divisor greater than its square root, it must also have a divisor smaller than its square root.  Therefore, if no divisor is found up to the square root, the number is prime.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   The outer loop iterates `n` times.
    *   The square root calculation takes O(1) time.
    *   The primality test (inner loop) iterates up to the square root of `sqroot`.  So, if the largest number is `M`, the square root would be `sqrt(M)`, and we iterate to the square root of that, which is `M^(1/4)`. This makes the overall primality test O(M^(1/4)).
    *   Therefore, the overall time complexity is O(n * M^(1/4)).

*   **Space Complexity:**
    *   The `arr` vector stores `n` integers, contributing O(n) space.
    *   Other variables use constant space.
    *   Therefore, the overall space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique in C++ to speed up input/output operations by disabling synchronization between the C and C++ standard streams and unlinking `cin` from `cout`.
*   **Integer Square Root:** The `sqrt()` function returns a double. It's crucial to cast the result to an integer and then multiply it by itself to ensure an exact comparison.  `sqroot * sqroot != val` ensures that we are actually working with perfect squares.
*   **Iterating only up to square root for primality test.**

### 6. Edge Cases Handled

*   **`val == 1`:** The code explicitly handles the case when the input number is 1, as 1 only has one divisor (itself) and is therefore not a T-prime.
*   **Non-Perfect Squares:** The code correctly identifies and rejects numbers that are not perfect squares. This is essential because only perfect squares can potentially be T-primes.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <system_error>
#include <vector>
using namespace std;

#define int long long

// Problem: tPrime
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

    // we call a positive integer T-prime iff it has exactly three distinct positive divisors
    for (int val : arr) {
        if (val == 1) {
            cout << "NO\n";
            continue;
        }

        // now val has two divisors, 1 and itself and both are distinct (since val != 1)
        // if it has exactly one more divisor, we are done
        int left = 2;
        int right = val - 1;

        // if it has exactly one divisor in this range, we are done
        // but, if it has a divisor r, then it also has a divisor val / r
        // for them to be the same r * r = val
        // i.e, val is a perfect square

        // if val isn't a perfect square, it will have an even number of divisors, so it can't be a T-prime
        // if val is a perfect square, such that val = r * r, its a T-prime only when r is a prime number

        int sqroot = sqrt(val);
        if (sqroot * sqroot != val) {
            cout << "NO\n";
            continue;
        }

        // now sqroot needs to be a prime
        int x = sqroot;
        bool cond = false;
        for (int i = 2; i <= sqrt(x); i++) {
            int q = x / i;
            if (i * q == x) {
                cond = true;
                break;
            }
        }

        if (cond) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
```

---
*Documentation generated on 2025-08-10 20:04:23*
