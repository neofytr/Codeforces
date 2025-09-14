# primeNumber

```markdown
## Documentation: Codeforces Problem 359C - Prime Number

This document provides a comprehensive analysis of the provided C++ code, which solves Codeforces problem 359C - Prime Number (https://codeforces.com/contest/359/problem/C).

### 1. Problem Description (Inferred)

Given an array `arr` of `n` integers and an integer `x`, the problem requires finding the smallest integer `k` such that `x^k` divides the sum of `x^(s - arr[i])` for all `i` from `0` to `n-1`, where `s` is the sum of all elements in the array `arr`. More formally:  Find minimum `k` such that  `x^k | sum(x^(s-arr[i]))` for `i=0` to `n-1`. The answer to the problem is then `x^k modulo 1000000007`.

### 2. Approach Explanation

The solution adopts the following approach:

1. **Calculate the sum (s) of all elements in the array `arr`.**  This value `s` is crucial for determining the exponents in the summation.

2. **Create a frequency map (`mp`)**. The map stores the frequency of each value `s - arr[i]`.  Essentially, `mp[exponent]` represents how many times the term `x^exponent` appears in the overall summation `sum(x^(s-arr[i]))`.

3. **Normalize the Exponents:** The core idea is to find the minimum exponent `k` such that `x^k` divides the overall sum.  This is done by iterating through the exponents from the smallest to the largest. If `mp[curr]` (frequency of `x^curr`) is divisible by `x`, then we can reduce the power `curr` by 1 by increasing the power `curr+1`. So `mp[curr]` is divided by `x`, and added to `mp[curr+1]`.  The process continues until `mp[curr]` is not divisible by `x`.

4. **Determine the Minimum Exponent (k):** After the normalization process, the lowest exponent `curr` whose frequency (`mp[curr]`) is non-zero corresponds to the minimum exponent `k` we're looking for. The final answer is `x^k modulo 1000000007`.

### 3. Key Insights and Algorithmic Techniques Used

*   **Exponent Analysis:** The problem is solved by carefully analyzing the exponents involved in the summation. Understanding how the frequency of each exponent contributes to the divisibility condition is key.

*   **Frequency Map (Unordered Map):** Using an unordered map to store the frequencies of the exponents allows for efficient counting and manipulation of these frequencies.

*   **Normalization:** The normalization process is crucial for finding the smallest exponent. It simulates the process of factoring out powers of `x` from the overall sum. This is essentially performing a carry operation in base `x`.

*   **Modular Exponentiation:** The `pw` function implements modular exponentiation using the "exponentiation by squaring" technique. This efficiently calculates `a^b modulo MOD` in logarithmic time.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Calculating the sum: O(n)
    *   Creating the frequency map: O(n)
    *   Normalizing the exponents: O(max(arr[i])) in the worst case. In practice, this will be much smaller than max(arr[i]), since we can stop the process early. Because the value increases by `1` in each loop, and in worst case it could loop until `s-arr[0]`, it's `O(s - min(arr[i]))` or `O(sum(arr))`.

    The dominant factor is `O(n + sum(arr))`.

*   **Space Complexity:**
    *   Array `arr`: O(n)
    *   Frequency map `mp`: O(n) in the worst-case, as it can potentially store up to `n` distinct exponents.

    Thus, the overall space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:**  This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with multiplication operations.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  This optimization disables synchronization between C++ streams and the standard C input/output streams, potentially improving input/output performance.

*   **Modular Arithmetic:** The code consistently uses the modulo operator (`%`) to prevent integer overflow and ensure that the results remain within the specified range.

*   **Exponentiation by Squaring:** The `pw` function efficiently calculates powers using the exponentiation by squaring method, reducing the time complexity from O(b) to O(log b).

### 6. Edge Cases Handled

*   The code implicitly handles the case where the exponentiation function is called with `b = 0`, returning 1, which is correct.
*   The modular arithmetic prevents overflow, which would occur for larger values.

```
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: primeNumber
// URL: https://codeforces.com/contest/359/problem/C
// Difficulty: hard
// Tags:
// Strategy:

#define MOD 1000000007

int pw(const int a, const int b) {
    if (!b)
        return 1;
    const int r = pw(a, b / 2);
    if (b & 1)
        return (((r * r) % MOD) * a) % MOD;
    return (r * r) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    int s = 0;
    for (int &val : arr)
        cin >> val, s += val;
    // arr is non-decreasing

    unordered_map<int, int> mp;
    for (int r = 0; r < n; r++)
        mp[s - arr[r]]++;

    int curr = s - arr[n - 1]; // this is the minimum power
    while (!(mp[curr] % x)) {
        mp[curr + 1] += mp[curr] / x;
        mp[curr] = 0;
        curr++;
    }

    cout << pw(x, curr) << endl;

    return 0;
}
```

---
*Documentation generated on 2025-09-14 11:18:47*
