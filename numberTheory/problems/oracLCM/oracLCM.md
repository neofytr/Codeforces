# oracLCM

```markdown
# Documentation of Competitive Programming Solution: oracLCM

This document analyzes a C++ solution to the "oracLCM" problem from Codeforces (http://codeforces.com/contest/1349/problem/A).

## 1. Problem Description (Inferred)

Given an array `arr` of `n` integers, we need to calculate a value `res` that is a product of powers of primes. For each prime factor `p` that appears in the prime factorization of at least `n-1` elements of `arr`, we take the *second smallest* power of `p` if `p` appears in all `n` elements, or the *smallest* power of `p` if `p` appears in exactly `n-1` elements of `arr`.  The problem asks for the product of `p^power` for each such prime `p`.

In other words, calculate the LCM of all subsets of `arr` of size `n-1`.

## 2. Approach Explanation

The solution employs the following steps:

1. **Prime Factorization Precomputation:** The code precomputes the smallest prime factor (SPF) for each number up to a defined maximum value (`MAX`). This allows for efficient prime factorization in subsequent steps.

2. **Prime Factorization of Array Elements:**  For each element in the input array `arr`, the code performs prime factorization using the precomputed SPF values. The powers of each prime factor are stored in an `unordered_map` called `prime`.  The keys of the `unordered_map` are the prime factors themselves, and the values are `multiset`s that store the powers to which that prime factor appears in the factorization of the input numbers.

3. **Calculating the Result:** The code iterates through the `prime` map. For each prime factor `p`, it checks the number of times the prime `p` appears in the factorizations.
    - If the prime `p` appears in all `n` numbers, the second smallest power from the `multiset` is used.
    - If the prime `p` appears in `n-1` numbers, the smallest power from the `multiset` is used.
    - If the prime `p` appears in less than `n-1` numbers, it's ignored.

4. **Calculating the Power:**  The `power` function is used to calculate p raised to the appropriate power.

5. **Multiplying the Results:**  The final result `res` is the product of all `p^power` values calculated in the previous steps.

## 3. Key Insights and Algorithmic Techniques Used

*   **Smallest Prime Factor (SPF) Sieve:** The code uses the Sieve of Eratosthenes to compute the smallest prime factor (SPF) of all numbers up to `MAX`. This is a standard technique for efficient prime factorization. By precomputing the SPF, the time complexity of factorizing each number becomes O(log n) on average, where n is the number being factorized.

*   **Prime Factorization:** The core of the solution is efficiently factorizing each input number into its prime factors and their corresponding powers.

*   **Data Structures (unordered_map and multiset):**  The `unordered_map<int, multiset<int>> prime` is a crucial data structure. The `unordered_map` stores prime factors as keys, and the `multiset` associated with each prime factor efficiently stores the powers to which that prime appears in the factorizations. `multiset` allows duplicate powers and ensures the powers are always sorted allowing easy access to the smallest and second smallest powers.

*   **LCM Property:**  The core insight into the problem lies in understanding that the LCM of a set of numbers can be computed by considering the highest power of each prime factor that appears in the factorization of any of the numbers. However, we are taking the LCM of all subsets of size n-1. So for each prime we check whether it appears in all the factorizations or n-1 of them. In the first case we take the second smallest power and in the second we take the smallest.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   SPF Sieve: O(MAX log log MAX)
    *   Prime Factorization of Array Elements: O(n * log(arr[i])), where `arr[i]` is the i-th element.  In the worst case, if all elements are close to MAX, this becomes O(n * log(MAX)).
    *   Iterating through the `prime` map: O(number of distinct prime factors * log(number of prime factors)). The log factor comes from inserting and finding elements in the `multiset`.
    *   Overall: Dominating term is likely O(MAX log log MAX) + O(n * log(MAX)) since MAX is usually quite small.
*   **Space Complexity:**
    *   `spf` vector: O(MAX)
    *   `prime` map: O(number of distinct prime factors * n) in the worst case, where the prime factors are the same across all n numbers. Can be simplified to O(number of distinct primes * n).

## 5. Important Code Patterns or Tricks Used

*   **SPF Sieve:**  A highly efficient and widely used method for prime factorization.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are a common optimization trick in competitive programming to speed up input/output by disabling synchronization between the C and C++ standard streams.
*   **Using `multiset` to efficiently keep track of prime powers:** This is a very useful trick in this problem to easily access the smallest and second smallest powers of the primes.
*   **Bitwise Operators:** Using `exp & 1` and `exp >>= 1` in the `power` function is a standard and efficient way to implement exponentiation by squaring.

## 6. Edge Cases Handled

*   The code implicitly handles the case where a prime factor does not appear in `n-1` or `n` of the input numbers by skipping it entirely.  This is the desired behavior according to the problem description.
*   The powers of primes are handled with `multiset`, which takes care of the cases when the powers can be zero.
*   There is an implicit assumption that the input numbers and the final answer fit within the range of `long long` integer type.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: oracLCM
// URL: http://codeforces.com/contest/1349/problem/A
// Difficulty: hard
// Tags: 
// Strategy: 

#define MAX (2 * 1000000)

int power(int base, int exp) {
    int res = 1;
    while(exp) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> spf(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            if (spf[j] == -1)
                spf[j] = r;
    
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)    
        cin >> val;

    unordered_map<int, multiset<int>> prime;
    for (int val : arr) {
        int x = val;
        while (x != 1) {
            int p = spf[x];
            int pw = 0;
            while(!(x % p))
                pw++, x /= p;

            prime[p].insert(pw);
        }
    }

    int res = 1;
    for (auto &[p, s] : prime)
        if (s.size() == n)
            res *= power(p, *(++s.begin()));
        else if (s.size() == n - 1)
            res *= power(p, *s.begin());

    cout << res << endl;
    return 0;
}
```

---
*Documentation generated on 2025-10-03 17:04:47*
