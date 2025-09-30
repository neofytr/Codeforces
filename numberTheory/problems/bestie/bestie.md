# bestie

```markdown
## Competitive Programming Solution Documentation

This document analyzes a C++ solution to a competitive programming problem, identified by the URL: [https://codeforces.com/problemset/problem/1732/A](https://codeforces.com/problemset/problem/1732/A). The problem is named "bestie" and has a medium difficulty rating.

### 1. Problem Description (Inferred)

Given an array `arr` of `n` integers (indexed from 1 to n), we need to determine the minimum number of operations to make the greatest common divisor (GCD) of the elements `arr[1]`, `arr[2]`, ..., `arr[n]` equal to 1.  The allowed operation is to increment a single element `arr[i]` by 1, where `1 <= i <= n`. We are given `t` test cases.

### 2. Approach Explanation

The solution computes the GCD of the array elements from index 1 to n. If the GCD is already 1, no operations are needed. Otherwise, the solution attempts to reduce the GCD to 1 using at most three increment operations.  The strategy revolves around strategically incrementing the last few elements to potentially make the overall GCD equal to 1.

Specifically, it checks the following:

1.  **GCD is 1:** If the GCD of all elements is already 1, the answer is 0.
2.  **Increment last element:** If the GCD of the array elements, including `n`, is 1, then incrementing `arr[n]` will make the GCD 1. The answer is 1.
3.  **Increment second last element:** If the GCD of the array elements, including `n-1`, is 1, then incrementing `arr[n-1]` will make the GCD 1. The answer is 2.
4.  **Increment both last elements:** If neither of the above conditions is met, incrementing both `arr[n]` and `arr[n-1]` cannot guarantee GCD = 1. However, as we only have up to 3 moves to use, the GCD of all elements *must* be 1 when we apply moves on the last two elements of the array. If GCD(g, n) != 1 and GCD(g, n-1) != 1, incrementing arr[n-1] and arr[n] leads to GCD(g,n-1) == 1 and GCD(g,n) == 1. Thus, we increment n-1 and n and we can say for sure the GCD will be 1. The answer is 3.

### 3. Key Insights and Algorithmic Techniques Used

*   **Greatest Common Divisor (GCD):** The core of the solution relies on efficiently computing the GCD. The Euclidean algorithm (`gcd(a, b)`) is used for this purpose.
*   **Iterative Reduction:** The solution doesn't try to find the optimal elements to increment. Instead, it focuses on incrementing the last few elements and checking if the GCD becomes 1.  This is based on the observation that modifying the last elements has the most immediate impact on changing the GCD.
*   **Greedy Approach:**  The logic essentially tests cases greedily, starting with the fewest possible increment operations (1) and increasing the number of operations until GCD becomes 1 or the maximum allowed operations (3) are reached.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   `gcd(a, b)`: O(log min(a, b))
    *   `solve(arr)`:  The loop to calculate the initial GCD iterates `n` times, with each `gcd` call taking O(log min(a, b)). The following `gcd` calls are O(log min(a, b)). The dominant factor is the loop in `solve` function. Therefore the complexity is `O(n log(max_arr))`.
    *   The main loop runs `t` times, so the overall time complexity is `O(t * n * log(max_arr))`, where `max_arr` is the maximum value in the array.
*   **Space Complexity:**
    *   `arr`: O(n)
    *   The other variables use constant space.
    *   Therefore, the overall space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This ensures that the integer type can handle larger numbers, preventing potential integer overflow issues, which is very important in competitive programming.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a common optimization technique in C++ to speed up input/output by disabling synchronization between the C and C++ standard streams.

### 6. Any Edge Cases Handled

*   **GCD is already 1:** The code explicitly checks if the initial GCD is 1 and returns 0 in that case, which is a crucial edge case.
*   The code implicitly handles the case where `n = 1`. In this case, `gcd(arr[1],1)` will be called.

```
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: bestie
// URL: https://codeforces.com/problemset/problem/1732/A
// Difficulty: medium
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int solve(vector<int> &arr) {
    int n = (int)arr.size() - 1;

    int g = 0;
    for (int r = 1; r <= n; r++)
        g = gcd(g, arr[r]);

    if (g == 1)
        return 0;

    if (gcd(g, n) == 1)
        return 1;

    if (gcd(g, n - 1) == 1)
        return 2;
    return 3; 
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<int> arr(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> arr[r];

        cout << solve(arr) << endl;
    }    
    return 0;
}
```

---
*Documentation generated on 2025-09-30 11:45:50*
