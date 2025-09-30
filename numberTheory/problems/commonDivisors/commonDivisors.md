# commonDivisors

```markdown
# Codeforces Problem 1203C - Common Divisors: Solution Documentation

## 1. Problem Description

The problem ([Codeforces 1203C - Common Divisors](https://vjudge.net/problem/CodeForces-1203C)) asks us to find the number of common divisors of a given array of integers.  Specifically, given an array `arr` of `n` integers, we need to calculate the number of integers that divide *all* the elements of `arr`.

## 2. Approach Explanation

The solution calculates the number of common divisors by following these steps:

1.  **Find the Greatest Common Divisor (GCD):**  Implicitly, the code calculates the GCD of all numbers in the array, but it doesn't use the traditional `gcd` function. Instead, it calculates the prime factorization of a smaller number and makes sure that prime factorization is applicable to all the numbers in the array.
2.  **Prime Factorization of (implicit) GCD:** The code factors the numbers in the input array to find their common prime factors and the minimum powers of those factors that divide all numbers. The `primes` unordered map stores the prime factors and their minimum exponents.
3.  **Calculate Number of Divisors:** Given the prime factorization of the (implicit) GCD, the number of divisors is calculated using the formula: if `GCD = p1^e1 * p2^e2 * ... * pk^ek`, then the number of divisors is `(e1 + 1) * (e2 + 1) * ... * (ek + 1)`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Prime Factorization:** The core idea is to find the prime factorization of the GCD (implicitly) to easily calculate the number of divisors. The code iterates through possible prime factors up to the square root of `mini`.
*   **Finding Minimum Exponents:** The code iteratively factors each number in the input array using the prime factors found initially. For each prime factor, it determines the *minimum* exponent across all numbers in the input array. This ensures that the prime factors and their exponents are common to all numbers, meaning we are effectively finding the prime factorization of their GCD.
*   **Number of Divisors Formula:**  The formula `(e1 + 1) * (e2 + 1) * ... * (ek + 1)` is a standard number theory result that directly relates the prime factorization of a number to the total count of its divisors.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Finding the minimum among `n` numbers takes O(n).
    *   Prime factorization of `mini` (the minimum value) takes O(sqrt(mini)).
    *   Iterating through the array and updating the prime factor counts takes O(n * number of prime factors of mini). The number of prime factors is generally `O(log mini)`, so we can approximate the cost to O(n * log mini)
    *   Calculating the final result (number of divisors) takes O(number of prime factors of mini), approximately O(log mini).

    Therefore, the overall time complexity is O(n + sqrt(mini) + n * log(mini)). In practice, the `n * log(mini)` portion will likely dominate.

*   **Space Complexity:**
    *   `arr` takes O(n) space.
    *   `primes` stores the prime factors of the GCD, which can be at most O(log mini).
    *   Other variables take constant space.

    Therefore, the overall space complexity is O(n + log mini).

## 5. Important Code Patterns or Tricks Used

*   **Implicit GCD:** The code doesn't explicitly calculate the GCD using the `gcd` function (e.g., from `<numeric>`). Instead, it efficiently determines common prime factors and minimum exponents across all numbers, effectively achieving the same result (prime factorization of the GCD) without direct GCD calculations.  This can be more efficient when dealing with large numbers, as it avoids repeated GCD calls.
*   **`unordered_map` for Prime Factors:** The `unordered_map` provides fast lookups and updates for prime factors and their counts. Using an `unordered_map` (or `map`) is very common to handle primes and their frequencies
*   **Optimization with Square Root:**  The prime factorization loop only iterates up to the square root of the minimum value.  This is a standard optimization technique for prime factorization.
*   **The use of `while(!(mini % r))`:** This concisely extracts the highest power of prime `r` that divides `mini`. This can be extended to larger numbers by repeated division.

## 6. Edge Cases Handled

*   **`mini > 1` After Factorization:** If after dividing `mini` by all primes up to its square root, `mini` is still greater than 1, then it must be a prime number itself.  The code correctly handles this by adding it to the `primes` map.

```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: commonDivisors
// URL: https://vjudge.net/problem/CodeForces-1203C
// Difficulty: easy
// Tags: 
// Strategy: 

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define MAX (1000000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    int mini = LLONG_MAX;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val, mini = min(val, mini);


    unordered_map<int, int> primes;
    for (int r = 2; r * r <= mini; r++)
        while(!(mini % r))
            primes[r]++, mini /= r;
    if (mini > 1) primes[mini]++;

    for (int val : arr)
        for (auto &[p, cnt] : primes) {
            int ncnt = 0;
            while (!(val % p))
                ncnt++, val /= p;
            cnt = min(cnt, ncnt);
        }

    int res = 1;
    for (auto &[p, cnt] : primes)
        res *= (cnt + 1);
    cout << res << endl;
    return 0;
}
```

---
*Documentation generated on 2025-09-30 10:19:22*
