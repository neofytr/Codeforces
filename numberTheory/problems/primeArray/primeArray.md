# primeArray

```markdown
# Prime Array Solution Analysis

This document analyzes a C++ solution for the "Prime Array" problem found on HackerEarth: [https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/prime-array-5e448ef6/](https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/prime-array-5e448ef6/).

## 1. Problem Description (Inferred)

Given an array of integers, the task is to find the number of triplets that can be formed such that the triplet contains one prime number and two '1's.  The order of elements in the triplets does *not* matter, i.e., {1, prime, 1} is equivalent to {1, 1, prime}.

## 2. Approach Explanation

The solution takes the following steps:

1.  **Sieve of Eratosthenes:**  Pre-computes a boolean array `isPrime` to identify prime numbers up to a certain limit (`MAX = 100000`). This is an efficient way to determine primality for multiple numbers within a specified range.
2.  **Input Processing:** Reads the number of test cases `t`, and for each test case:
    *   Reads the array size `n`.
    *   Reads the array elements into the `arr` vector.
3.  **Counting Ones and Primes:** Iterates through the array and counts the number of '1's (`ones`) and prime numbers (`primes`).
4.  **Calculating Triplet Count:**  Calculates the number of valid triplets using the combination formula.  Since the triplet must have one prime and two ones, the number of possible triplets is `primes * (ones * (ones - 1) / 2)`.  This calculates the number of ways to choose one prime from `primes` and two '1's from `ones`. The division by 2 accounts for combinations since order doesn't matter.
5.  **Output:** Prints the calculated triplet count for each test case.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sieve of Eratosthenes:** This is a fundamental algorithm for efficiently generating a list of prime numbers up to a given limit.  Its efficiency is crucial for solving problems where primality testing is a frequent operation.  It is a classic example of dynamic programming.
*   **Combinations:** The problem requires finding the number of ways to choose elements from a set without regard to order.  The formula `n * (n - 1) / 2` calculates the number of ways to choose 2 elements from a set of `n` elements (n choose 2).
*   **Preprocessing:** Computing primes in advance (preprocessing step) avoids repeated primality tests for each array element, which enhances efficiency significantly.
*   **Counting and Combination:** The solution effectively combines counting specific elements (1s and primes) within the array with a combinatorial argument to find the total count of valid triplets.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sieve of Eratosthenes: O(N log log N), where N is `MAX` (100000).
    *   Input and array processing: O(N) for each test case, where N is the size of the array.  Since the sieve is run once and the array is processed `t` times the overall complexity is O(MAX log log MAX + t\*n).
    *   Calculating triplet count: O(1)
    *   Overall, the time complexity is dominated by the sieve and the array processing, which can be expressed as O(MAX log log MAX + t * n), where t is the number of test cases and n is the array size.
*   **Space Complexity:**
    *   `isPrime` vector: O(MAX)
    *   `arr` vector: O(n)
    *   Overall, the space complexity is O(MAX + n).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: These lines optimize input/output operations by disabling synchronization between C++ streams and the standard C streams, and by unlinking `cin` from `cout`. This can significantly improve performance, especially in competitive programming.
*   **`#define int long long`**: This preprocessor directive redefines the `int` type to `long long`.  This is a common practice in competitive programming to prevent integer overflow issues, especially when dealing with larger numbers.
*   **Range-based for loop:** Using `for (int &val : arr)` allows for directly modifying the array elements while iterating. `for (const int val : arr)` allows for reading the values without any unintentional side-effects.
*   **Ternary Operator:**  The use of ternary operator for computing the count of valid triplets, `const int two = (primes >= 1 && ones >= 2) ? primes * (((ones) * (ones - 1)) / 2) : 0;` makes the code compact and easy to read.

## 6. Edge Cases Handled

*   **`primes >= 1 && ones >= 2`**: The code explicitly checks if there are at least one prime number and at least two '1's in the array. If this condition is not met, the number of possible triplets is 0, which is correctly handled.
*   **Integer Overflow:**  Using `long long` as the integer type mitigates potential integer overflow issues when calculating `ones * (ones - 1) / 2`, especially when `ones` is large.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: primeArray
// URL: https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/prime-array-5e448ef6/
// Difficulty: easy
// Tags:
// Strategy:

#define MAX 100000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<bool> isPrime(MAX + 1, true);
    for (int r = 2; r <= MAX; r++)
        if (isPrime[r])
            for (int j = 2 * r; j <= MAX; j += r)
                isPrime[j] = false;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int ones = 0;
        int primes = 0;
        for (const int val : arr)
            if (val == 1)
                ones++;
            else if (isPrime[val])
                primes++;

        // choose one prime and two ones
        const int two = (primes >= 1 && ones >= 2) ? primes * (((ones) * (ones - 1)) / 2) : 0;
        cout << two << endl;
    }
    return 0;
}
```

---
*Documentation generated on 2025-09-16 09:40:30*
