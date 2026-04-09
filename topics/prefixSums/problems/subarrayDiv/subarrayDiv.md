# subarrayDiv

```markdown
# Subarray Divisibility Problem

This document analyzes a C++ solution to the "Subarray Divisibility" problem, found on CSES Problem Set (https://cses.fi/problemset/task/1662). The problem asks to count the number of subarrays in a given array whose sum is divisible by a given number *n*.

## 1. Problem Description

Given an array `arr` of `n` integers, find the number of subarrays such that the sum of the elements in each subarray is divisible by `n`.

## 2. Approach Explanation

The solution employs the concept of prefix sums and remainders to efficiently count the desired subarrays.  The core idea is based on the following observations:

1.  **Subarray Sum:** The sum of a subarray `[l, r]` can be calculated as `prefix[r+1] - prefix[l]`, where `prefix[i]` is the sum of the first `i` elements of the array.
2.  **Divisibility by N:**  A subarray `[l, r]` has a sum divisible by `n` if `(prefix[r+1] - prefix[l]) % n == 0`.
3.  **Remainder Equality:**  The condition `(prefix[r+1] - prefix[l]) % n == 0` is equivalent to `prefix[r+1] % n == prefix[l] % n`. This means the remainders of the prefix sums at indices `r+1` and `l` must be equal for the subarray `[l,r]` to satisfy the condition.

Based on these observations, the algorithm works as follows:

1.  Calculate the prefix sum array `prefix`.  The `prefix[i]` element stores the sum of the first `i` elements of the original array, modulo `n`.
2.  Use a hash map `freq` (specifically an `unordered_map`) to store the frequency of each remainder encountered so far. `freq[rem]` stores the number of times the remainder `rem` has appeared in the prefix sum.  Initialize `freq[0] = 1` because the empty prefix (before the start of the array) has a sum of 0, and 0 is divisible by `n`.
3.  Iterate through the `prefix` array. For each `prefix[i+1]`, calculate its remainder `rem` when divided by `n`.
4.  Increment the count by `freq[rem]`. This is because `freq[rem]` represents the number of starting indices `l` such that `prefix[l] % n == rem`.  Thus, for each such `l`, the subarray `[l, i]` has a sum divisible by `n`.
5.  Increment `freq[rem]` to account for the newly encountered remainder.

## 3. Key Insights and Algorithmic Techniques Used

*   **Prefix Sums:** Efficiently calculating subarray sums using prefix sums is a standard technique in competitive programming.
*   **Modular Arithmetic:** The application of modular arithmetic (`% n`) is crucial for simplifying the divisibility check.  Instead of dealing with potentially very large prefix sums, we only need to track their remainders modulo `n`.
*   **Hashing (Unordered Map):**  The use of a hash map (`unordered_map`) allows for constant-time (average case) lookup of remainder frequencies. This is critical for achieving an efficient solution.
*   **Remainder Property:** The insight that `(a - b) % n == 0` if and only if `a % n == b % n` is the cornerstone of this approach.
*   **Custom Hash Function:** The code includes a `custom_hash` struct for the `unordered_map`.  This is intended to reduce the probability of hash collisions, potentially improving performance, especially with adversarial test cases.  It uses the `splitmix64` algorithm and a random seed.  However, this is often not strictly necessary, and the default hashing behavior of `unordered_map` is often sufficient.
*   **Handling Negative Remainders:** The code includes `((prefix[index - 1] + arr[index - 1]) % n + n) % n` to ensure remainders are non-negative.  In C++, the modulo operator `%` can return negative values when the dividend is negative.  Adding `n` and then taking the modulo again ensures the result is always in the range `[0, n-1]`. This is important for the correctness of the algorithm.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the number of elements in the array. This is because we iterate through the array once to calculate the prefix sums and once to count the subarrays. The `unordered_map` lookups and insertions take O(1) time on average.
*   **Space Complexity:** O(n) in the worst case.  The `prefix` vector stores `n+1` integers, and the `unordered_map` could potentially store up to `n` different remainders.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`**: This macro is commonly used in competitive programming to avoid integer overflow issues, especially when dealing with large sums.  It redefines `int` as `long long`.
*   **`ios_base::sync_with_stdio(false); cin.tie(nullptr);`**: These lines are used to speed up input/output operations by disabling synchronization between C++ streams and the C standard input/output library.
*   **Custom Hash Function:** As mentioned earlier, the `custom_hash` struct is a technique to reduce hash collisions in `unordered_map`.
*   **Non-Negative Remainders:** The `((prefix[index - 1] + arr[index - 1]) % n + n) % n` pattern is essential for dealing with potentially negative remainders in C++.
*   **Prefix Array Sizing:** The prefix array is sized to `n+1` so it can cover the case where no elements are included (the empty range from [0,0]).

## 6. Edge Cases Handled

*   **Empty Subarray:** The initialization `freq[0] = 1` implicitly handles the case where the empty subarray (sum 0) is divisible by `n`.
*   **Negative Numbers:** The code explicitly addresses the possibility of negative numbers in the input array by ensuring that all remainders are non-negative.
*   **Large Sums:** The use of `long long` data type helps avoid integer overflows when calculating sums of large numbers.

This documentation provides a comprehensive analysis of the provided C++ solution for the Subarray Divisibility problem. Understanding the concepts of prefix sums, modular arithmetic, and hashing are crucial for solving similar problems efficiently.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: subarraydiv
// url: https://cses.fi/problemset/task/1662
// difficulty: hard
// tags:
// strategy:

#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t fixed_random = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + fixed_random);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to count the number of subarrays where the sum of values is divisible by n
    // a subarray [l, r] is good iff the sum of it values is divisible by n
    // a subarray [l, r] is good iff rem(prefix[r + 1] - prefix[l], n) = 0
    //                           iff rem(prefix[r + 1], n) - rem(prefix[l], n) = 0
    //                           iff rem(prefix[r + 1], n) = prefix(l, n)

    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = ((prefix[index - 1] + arr[index - 1]) % n + n) % n;

    unordered_map<int, int, custom_hash> freq; // freq[r] is the number of subarrays until the current iteration which have the remainder r from n
    freq[0] = 1;
    int count = 0;
    for (int index = 0; index < n; index++) {
        int rem = prefix[index + 1];
        count += freq[rem];
        freq[rem]++;
    }
    cout << count << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-22 14:18:35*
