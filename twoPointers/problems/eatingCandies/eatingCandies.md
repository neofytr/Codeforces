# eatingCandies

```markdown
# Solution Documentation: Eating Candies

This document provides a comprehensive analysis of the provided C++ code solution for the "Eating Candies" problem, which can be found on Codeforces (problem F of contest 1669) at [https://codeforces.com/contest/1669/problem/F](https://codeforces.com/contest/1669/problem/F).

## 1. Problem Description (Inferred)

Given an array `arr` of `n` integers representing the sizes of candies, Alice starts eating candies from the left and Bob starts eating candies from the right simultaneously.  In each step, Alice eats one candy from the left end, and Bob eats some candies from the right end such that the total weight of the candies eaten by Bob does not exceed the total weight of candies eaten by Alice.

The goal is to find the maximum number of candies that can be eaten by both Alice and Bob combined such that at some point the total weight of candies eaten by Alice is equal to the total weight of candies eaten by Bob.

## 2. Approach Explanation

The solution uses a two-pointer approach to efficiently find the maximum number of candies that can be eaten by both Alice and Bob while maintaining the condition that their eaten candy weights are equal at some point.

The algorithm works as follows:

1.  Initialize two pointers `l` (left) and `r` (right) to the start and end of the array, respectively. Also, initialize `sum` to 0. The `sum` variable accumulates the weight of candies eaten by Alice. The variable `maxi` is initialized to 0 and stores the maximum number of candies eaten by both.
2.  Iterate while `l < r`. In each step:
    *   Alice eats candy `arr[l]`, so add `arr[l]` to `sum`.
    *   Bob compensates by eating candies from the right as long as the difference between Alice's `sum` and Bob's current candy is positive, i.e., `sum - arr[r] >= 0`. Note that Bob stops if `l>r`, or Bob needs to eat a candy that makes the total weight of Bob's eaten candy is greater than the total weight of Alice's eaten candy.
    *   Check if `l <= r` and `sum == 0`. If both are true, then it means weights of the candies eaten by Alice and Bob are equal at this point and update the maximum number of candies eaten so far using `maxi = max(maxi, l + 1 + n - r - 1)`. `l + 1` is the number of candies eaten by Alice and `n - r - 1` is the number of candies eaten by Bob.
    *   Increment `l`. This makes Alice eat the next candy and begins the search for next equality.

## 3. Key Insights and Algorithmic Techniques Used

*   **Two-Pointer Technique:**  This is the core algorithmic technique used. The `l` and `r` pointers efficiently explore the possible candy combinations for Alice and Bob, respectively.
*   **Greedy Approach:** Bob chooses to eat candies from the right until his total weight is as close to Alice's weight as possible without exceeding it.  This ensures we are considering valid configurations.
*   **Prefix Sum Optimization (Implicit):** While not explicitly using a prefix sum array, the variable `sum` acts as the current total weight of Alice's candies, enabling calculations in O(1) rather than O(l) for each step.
*   **Maintaining Invariant:**  The key invariant is that `sum` always represents Alice's total candy weight, and Bob eats just enough candies to not exceed this weight.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n). The outer `while` loop runs at most `n` times, and the inner `while` loop also runs at most `n` times in total across all iterations of the outer loop. Therefore, the overall time complexity is O(n).
*   **Space Complexity:** O(n). The `arr` vector stores `n` integers. The rest of the variables use constant extra space.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**:  This optimization disables synchronization between the C and C++ standard streams, significantly improving input/output performance, especially for problems with large input sizes.
*   **`#define int long long`**: This redefines `int` as `long long` to prevent integer overflow in cases where the sum of candy weights might exceed the maximum value of a standard `int`. This can prevent runtime errors.
*   **In-place modification of the sum:** The code cleverly reuses the `sum` variable to calculate both Alice's total weight and the difference when subtracting Bob's candies.

## 6. Any Edge Cases Handled

*   **Empty Array:** The code should function correctly even with an empty input array because the loop condition `l < r` will be immediately false if `n <= 1`, resulting in `maxi` remaining 0.
*   **All Zeroes:** If all candies have weight 0, then Alice can only eat until the middle and Bob also eat until the middle. Then it is possible to satisfy the condition and have `sum == 0`. This case is also correctly handled.
*   **Arrays with only one Element:** In that case the `l<r` loop isn't executed and 0 will be printed, which is the desired outcome.
*   **Arrays with Equal sums for multiple positions:**  The code makes the sum of candies be equal and it can find all of them, so it finds the maximum number of candies eaten.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: eatingCandies
// URL: https://codeforces.com/contest/1669/problem/F
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int maxi = 0;
        int l = 0, r = n - 1;
        int sum = 0;
        while (l < r) {
            // alice eats a candy
            sum += arr[l];
            // bob compensates for it
            while (l <= r && sum - arr[r] >= 0)
                sum -= arr[r--];
            if (l <= r && !sum)
                maxi = max(maxi, l + 1 + n - r - 1);
            l++;
        }
        cout << maxi << endl;
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-21 21:33:34*
