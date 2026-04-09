# divideAndEqualize

```markdown
# Code Documentation: Divide and Equalize Problem

This document analyzes a C++ solution to the "Divide and Equalize" problem found on Codeforces (https://codeforces.com/problemset/problem/1881/d).

## 1. Problem Description (Inferred)

The "Divide and Equalize" problem asks if an array of integers can be made equal by repeatedly dividing elements by their prime factors and distributing these factors among the array elements. More formally:

Given an array `arr` of `n` positive integers, determine if it's possible to transform the array such that all elements become equal after a series of operations.  In each operation, you can choose an element `arr[i]` and a prime factor `p` of `arr[i]`.  Divide `arr[i]` by `p` and multiply another element `arr[j]` by `p`.

## 2. Approach Explanation

The solution employs a prime factorization approach to determine if equalization is possible.  The core idea is:

1. **Prime Factorization:** For each number in the array, decompose it into its prime factors.
2. **Frequency Counting:** Count the frequency of each prime factor across all elements in the array.
3. **Divisibility Check:** If the count of *every* prime factor is divisible by `n` (the array size), then it's possible to redistribute the prime factors to make all elements equal.  Otherwise, it's not possible.

The intuition behind this is that if a prime factor `p` appears a total of `cnt` times across all numbers, and `cnt` is divisible by `n`, we can distribute the `p` factors evenly among the `n` elements, making them equal (each will have `cnt / n` factors of `p`).

## 3. Key Insights and Algorithmic Techniques Used

*   **Prime Factorization:** The core of the solution relies on efficiently finding the prime factors of each number.  The solution uses a precomputed `leastprime` array to optimize this process.
*   **Precomputed Least Prime Factor:** The `leastprime` array stores the smallest prime factor for each number from 2 up to a maximum value (`max`). This is a standard optimization for repeated prime factorization.  For example, `leastprime[12] = 2`, `leastprime[15] = 3`.
*   **Frequency Counting with HashMap:** An `unordered_map` (`mp`) is used to store the frequency of each prime factor. This provides efficient lookup and updates for the count of each prime factor.
*   **Divisibility Check:** The final step involves checking if the count of each prime factor is divisible by `n`. This directly determines if equalization is possible.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   **Prime Sieve (leastprime calculation):** O(max log log max). The Sieve of Eratosthenes has this well-known complexity.
    *   **Factorization and Counting:** The factorization of each number `x` takes O(log x) on average because in each step we divide `x` by its smallest prime factor. Considering that we do this for all `n` numbers, the total complexity would be O(n log X) where X is the max value of a number in the array.
    *   **Divisibility Check:** O(number of distinct prime factors), which is at most O(log max) in practice.
    *   **Overall:** Dominated by the prime sieve and factorization steps, which are O(max log log max + n log X), simplified as O(n log X) since `max` is a constant.

*   **Space Complexity:**
    *   **`leastprime` array:** O(max)
    *   **`mp` (unordered_map):** In the worst case, all numbers in the array can be distinct primes, leading to O(n) space for the map. However, it's limited by the number of primes less than or equal to max, hence space usage is less than O(max) in reality, and it usually scales as O(log max).

## 5. Important Code Patterns or Tricks Used

*   **Precomputation:** The `leastprime` array precomputes the smallest prime factor for all numbers up to `max`, allowing for efficient prime factorization in the `solve` function.  This is a common strategy for optimizing solutions when prime factorization is needed multiple times.
*   **Using smallest prime factor for factorization:**  By repeatedly dividing by the smallest prime factor, we avoid having to explicitly iterate and check for possible prime factors from the array elements itself.
*   **`unordered_map` for frequency counting:** `unordered_map` provides efficient (average O(1)) lookup and insertion for frequency counting, making the frequency calculation step relatively fast.
*   **`ios_base::sync_with_stdio(false); cin.tie(nullptr);`:** These lines are used to disable synchronization between C++ streams and the C standard input/output library, potentially speeding up input/output operations.

## 6. Edge Cases Handled

*   **Handling `x == 1` in the factorization loop:** The `while (x != 1)` loop ensures that the factorization process terminates correctly when a number has been completely factored.
*   **Implicit Handling of Zeroes or Negatives:** The problem statement likely implied that numbers are positive.  If there were zeroes or negative numbers, the logic would need modification to handle those cases.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: divideandequalize
// url: https://codeforces.com/problemset/problem/1881/d
// difficulty: medium
// tags:
// strategy:

bool solve(const vector<int> &arr, const vector<int> &leastprime) {
    const int n = arr.size();
    unordered_map<int, int> mp;

    for (int x : arr) {
        while (x != 1) {
            int p = leastprime[x];
            mp[p]++;
            x /= p;
        }
    }

    for (auto &[p, cnt] : mp)
        if (cnt % n != 0)
            return false;

    return true;
}

#define max 1000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> leastprime(max + 1, -1);
    for (int r = 2; r <= max; r++)
        for (int j = r; j <= max; j += r)
            if (leastprime[j] == -1)
                leastprime[j] = r;

    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;
        cout << (solve(arr, leastprime) ? "yes" : "no");
        cout << "\n";
    }

    return 0;
}
```

---
*Documentation generated on 2025-09-21 11:53:17*
