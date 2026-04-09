# bigSum

```markdown
## Problem: Finding the Shortest Subarray with Sum at Least S

This program solves the problem of finding the shortest subarray (contiguous segment) within a given array of positive integers such that the sum of the elements in the subarray is at least a given target value `S`.

**Problem URL:** [https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B](https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B)

**Input:**

*   `n`: The number of elements in the array.
*   `s`: The target sum.
*   `arr`: An array of `n` positive integers. It is guaranteed that each array element is greater or equal to 1.

**Output:**

*   The length of the shortest subarray whose sum is at least `S`. If no such subarray exists, output `-1`.

## Approach Explanation

The program employs a **sliding window** technique to efficiently find the shortest subarray. The core idea is to maintain a window defined by two pointers, `left` and `right`, and iteratively adjust the window's size to find the smallest valid subarray.

The algorithm works as follows:

1.  **Initialization:** Initialize `left` and `right` pointers to 0, `sum` to 0, and `minLen` to `LLONG_MAX`.  `minLen` will store the minimum length found so far.
2.  **Sliding Window:** Iterate using the `left` pointer, moving it from 0 to `n-1`.
    *   **Expand Window:** While the current window's sum (`sum`) is less than `S` and the `right` pointer is within the array bounds, expand the window by incrementing `right` and adding the corresponding element `arr[right]` to the `sum`.
    *   **Check if Good Segment:** If the `sum` is now greater than or equal to `S`, the current window `[left, right - 1]` represents a valid subarray (a "good segment").  Update `minLen` with the minimum of the current `minLen` and the length of the current window (`right - left`).
    *   **Shrink Window:**  After finding a valid segment starting at `left`, we shrink the window to find potentially smaller segments starting at the same `left`. Remove the element at the `left` from `sum` and increment the `left` pointer.
3.  **Handle No Solution:** After the loop finishes, if `minLen` remains `LLONG_MAX`, it means no valid subarray was found. Output `-1`. Otherwise, output the value of `minLen`.

## Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The sliding window technique is crucial for efficiently searching for subarrays that satisfy a certain condition. It avoids redundant calculations by reusing information from previously explored subarrays.
*   **Two Pointers:** The use of `left` and `right` pointers to define the window boundaries is a common pattern in sliding window algorithms.
*   **Prefix Sum (Implicit):** While not explicitly calculated, the `sum` variable effectively maintains a running sum of the elements within the current window, which is related to the idea of prefix sums.

## Time and Space Complexity Analysis

*   **Time Complexity:** O(n). Each element of the array is visited at most twice: once by the `right` pointer and once by the `left` pointer. The `while` loops inside the main loop do not increase the complexity beyond O(n) because `right` and `left` both move from 0 to n.
*   **Space Complexity:** O(1). The algorithm uses a constant amount of extra space for variables like `left`, `right`, `sum`, and `minLen`.

## Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between the C++ standard input/output streams and the C standard input/output streams. It can significantly improve the performance of I/O-bound programs, especially in competitive programming environments.
*   **`LLONG_MAX` Initialization:** Initializing `minLen` to the maximum possible value of a long long integer (`LLONG_MAX`) allows us to easily track the minimum length found so far.
*   **Positive Integers**: The problem guarantees positive integers. This allows us to advance the right pointer even if the sum already exceeds the target value `S` because we know all numbers are at least 1, so by moving the left pointer, we are guaranteed to reduce the sum.

## Edge Cases Handled

*   **No Solution:** The program handles the case where no subarray satisfies the condition by checking if `minLen` remains `LLONG_MAX` after the loop and outputting `-1` accordingly.
*   **Empty Input (n=0):**  The code implicitly handles the case where `n` is 0.  The outer `while` loop won't execute, and since `minLen` remains `LLONG_MAX`, the code correctly outputs `-1`.
*   **S = 0:** The code will correctly compute the smallest substring length of 0 in this case.
*   **S < 0:** The problem statement implies that `S` is non-negative. If `S` were negative, the entire array would be a solution, and the code would return `n`.
```

## Original Code
```cpp
#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: bigSum
// URL: https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all array values are >= 1
    // a segment [l,r] where 0 <= l <= r < n is good iff its sum is atleast s
    // we are to find the shortest good segment

    // we find the shortest good segment starting at index r for every 0 <= r < n and then
    // take the minimum of all of them

    int minLen = LLONG_MAX;
    int left = 0;
    int right = 0;
    int sum = 0;
    while (left < n) {
        if (right < left)
            right = left;
        while (right < n && sum < s)
            sum += arr[right++]; // if the current sum is less than s, add the current right ptr element

        if (sum >= s) {
            // [left, right - 1] is a good segment
            minLen = min(minLen, right - left);
            sum -= arr[left];
        }
        left++;
    }

    if (minLen == LLONG_MAX)
        cout << -1 << endl;
    else
        cout << minLen << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-17 11:52:14*
