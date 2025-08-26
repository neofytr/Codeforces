# flippingGame

```markdown
## Documentation: Flipping Game Solution

This document provides a comprehensive analysis of the provided C++ code, which solves the "Flipping Game" problem on Codeforces (problem set 327/A).

### 1. Problem Description

The "Flipping Game" problem (available at [https://codeforces.com/problemset/problem/327/A](https://codeforces.com/problemset/problem/327/A)) presents an array of 0s and 1s. The goal is to find the maximum number of 1s that can be obtained after flipping a subsegment (contiguous part) of the array. Flipping a subsegment means changing all 0s to 1s and all 1s to 0s within that subsegment.

### 2. Approach Explanation

The solution's core idea revolves around efficiently calculating the maximum increase in the number of 1s that can be achieved by flipping a subsegment. It avoids brute-force enumeration of all possible subsegments and instead uses prefix sums and dynamic programming (or a Kadane's algorithm-like approach) for optimization.

Here's a breakdown of the approach:

1. **Calculate the initial number of 1s:** The code first counts the total number of 1s (`total`) present in the original array. This value acts as a baseline.

2. **Prefix Sum of Zeros:** A `prefix` array is constructed. `prefix[r]` stores the number of zeros from index 0 up to (and including) index `r-1` in the original array `arr`. This allows for quick calculation of the number of zeros within any subarray.

3. **Transformation and Kadane's Algorithm Variant:** The key optimization lies in transforming the problem into a maximum subarray sum problem.  The code calculates `del[r] = 2 * prefix[r] - r` where `prefix[r]` represents zeros up to index `r-1` as mentioned above.  The problem then boils down to finding `max(del[j + 1] - del[i])` for all valid `i` and `j` (where i <= j) and summing the `total` number of initial ones from the array. This calculation helps to determine the maximum increase in the number of ones that can be achieved by flipping the interval from `i` to `j`.  This is then solved with an efficient single pass, updating a `miniDel` variable (minimum value seen so far) and calculating the `maxi` (the maximal change).

4. **Final Result:** The code then adds the `maxi` (maximum gain from flipping a segment) to the initial number of 1s (`total`) to obtain the final answer.

### 3. Key Insights and Algorithmic Techniques Used

*   **Prefix Sums:** Prefix sums provide an efficient way to compute the sum of elements within any subarray in O(1) time. Here, they are used to determine the number of zeros within a subsegment.

*   **Problem Transformation:** The problem is cleverly transformed from directly maximizing the number of 1s after flipping a subsegment to finding the maximum difference between two transformed values based on prefix sums (`del[j + 1] - del[i]`). This transformation makes it suitable for an efficient single-pass solution.

*   **Kadane's Algorithm Variant:** The calculation of `maxi` using `miniDel` is essentially a variant of Kadane's algorithm, which is commonly used to find the maximum sum subarray in linear time. By keeping track of the minimum `del` value seen so far (`miniDel`), the code efficiently finds the maximum difference `del[j + 1] - miniDel`. This is similar to finding the maximal difference in a stream of numbers.

*   **Mathematical Optimization:** The code correctly identifies the formula to calculate the increase in 1s: `total + zeroes(i, j) - (j - i + 1 - zeroes(i, j))`. This simplifies to `total + (2 * prefix[j + 1] - (j + 1)) - (2 * prefix[i] - i)`, which directly relates to `del[j + 1] - del[i]`.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Calculating the initial number of 1s: O(n)
    *   Calculating the prefix sum: O(n)
    *   Calculating `del` array: O(n)
    *   Finding the maximum difference using Kadane's algorithm variant: O(n)
    *   Therefore, the overall time complexity is **O(n)**.

*   **Space Complexity:**
    *   `arr`: O(n)
    *   `prefix`: O(n)
    *   `del`: O(n)
    *   Other variables: O(1)
    *   Therefore, the overall space complexity is **O(n)**.

### 5. Important Code Patterns or Tricks Used

*   **Prefix Sum Technique:** The efficient pre-computation of prefix sums is a crucial pattern in many problems involving subarray sums or related calculations.

*   **Kadane's Algorithm Adaptation:** The application of a Kadane's-like approach (keeping track of a minimum seen so far) to find the maximal difference in a transformed array is an effective optimization.

*   **Clear Variable Names:** Although it could be more descriptive, the code uses relatively clear variable names which helps with readability ( `total`, `prefix`, `del`, `miniDel`, `maxi` ).

### 6. Any Edge Cases Handled

*   The code implicitly handles the case where all elements are 1s. In this case, no flipping will increase the number of 1s, and the algorithm will correctly return the initial number of 1s (because `maxi` would be 0).

*   The code handles the edge case where all elements are zeros. Flipping any segment will increase the count of ones by the segment size.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: flippingGame
// URL: https://codeforces.com/problemset/problem/327/A
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

    int total = 0;
    for (const int val : arr)
        if (val)
            total++;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] = prefix[r - 1] + (!arr[r - 1]);
    // for any (i, j) where 0 <= i <= j < n, the number of ones in the array will be total + (numOfZerosIn(i, j) - numOfOnes(i, j))
    // ans(i, j) = total + zeroes(i, j) - (j - i + 1 - zeroes(i, j))
    //           = (total - 1) + 2 * zeroes(i, j) + (i - j)
    //           = (total - 1) + 2 *(prefix[j + 1] - prefix[i]) + (i - j)
    //           = total + (2 * prefix[j + 1] - (j + 1)) - (2 * prefix[i] - i)

    // let del[r] = 2*prefix[r] - r for 0 <= r <= n
    // so,
    // ans(i, j) = total + del[j + 1] - del[i] for 0 <= i <= j < n

    // we have to find max(ans(i, j) for 0 <= i <= j < n)

    vector<int> del(n + 1, 0);
    for (int r = 0; r <= n; r++)
        del[r] = 2 * prefix[r] - r;

    int miniDel = del[0];
    int maxi = LLONG_MIN;
    for (int j = 0; j < n; j++) {
        maxi = max(maxi, del[j + 1] - miniDel);
        miniDel = min(miniDel, del[j]);
    }
    cout << maxi + total << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-26 17:19:22*
