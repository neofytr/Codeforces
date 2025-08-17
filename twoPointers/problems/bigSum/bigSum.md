# bigSum

```markdown
# Problem: Minimum Segment Sum (Big Sum)

This problem (available at [https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B](https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/B)) asks to find the minimum length of a contiguous subsegment (subarray) of a given array such that the sum of elements in that subsegment is greater than or equal to a given target value 's'.  The elements in the input array are non-negative integers. If no such segment exists, the output should be -1.

## Approach Explanation

The solution uses a sliding window technique to efficiently find the shortest good segment. The algorithm maintains two pointers, `left` and `right`, representing the start and end of the current window.

1. **Initialization:**
   - `left` and `right` are initialized to 0.
   - `sum` is initialized to 0 to store the sum of elements within the current window.
   - `minLen` is initialized to `LLONG_MAX` to store the minimum length found so far.

2. **Sliding Window:**
   - The `while` loop iterates while the `left` pointer is within the bounds of the array (`left < n`).
   - Before expanding the window, the check `if (right < left)` is crucial. If the right pointer somehow fell behind the left, it's reset, ensuring the window is valid.
   - The inner `while` loop expands the window from the right until the `sum` of elements in the window is greater than or equal to `s` or the `right` pointer reaches the end of the array. `sum` is updated by adding the element at the `right` pointer, and `right` is incremented.
   - Once a "good" segment (sum >= s) is found, or the window can no longer be expanded, the algorithm checks if the current segment `[left, right - 1]` is a valid segment.  The length `right - left` is then compared with the current `minLen`, and `minLen` is updated if the current segment is shorter.
   - The algorithm then shrinks the window from the left by incrementing the `left` pointer and subtracting the element at the `left` position from the `sum`.

3. **Result:**
   - After the `while` loop finishes, if `minLen` is still `LLONG_MAX`, it means no good segment was found, and -1 is printed. Otherwise, `minLen` is printed as the length of the shortest good segment.

## Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The core technique is the sliding window algorithm. It efficiently explores all possible contiguous subsegments by expanding and shrinking the window.
*   **Two Pointers:** The `left` and `right` pointers define the sliding window.
*   **Monotonicity:** The algorithm exploits the fact that all array elements are non-negative.  As `right` increases, the window sum generally increases (or remains the same). This property allows us to efficiently find a "good" segment without needing to recompute the sum from scratch for each possible segment. If the array could have negative values, we could not shrink the window by subtracting the element at the `left` pointer, so this would no longer be efficient.
*   **Prefix Sum Optimization (Implicit):** While not explicitly creating a prefix sum array, the running `sum` variable effectively maintains the sum of the current window. This avoids recomputing the sum of the segment each time.

## Time and Space Complexity Analysis

*   **Time Complexity:** O(n). Both `left` and `right` pointers iterate through the array at most once.  Therefore, the overall time complexity is linear.
*   **Space Complexity:** O(1).  The algorithm uses a fixed amount of extra space for variables like `left`, `right`, `sum`, and `minLen`, regardless of the input size.

## Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are commonly used in competitive programming to speed up input/output operations by disabling synchronization between the C++ standard input/output streams and the C standard input/output streams. This is a standard performance optimization.
*   **`#define int long long`:** This redefines the `int` data type as `long long` to prevent integer overflow, which is crucial when dealing with potentially large sums.
*   **Initialization of `minLen`:** Initializing `minLen` to `LLONG_MAX` allows easy comparison and determination of whether a valid segment was found.
*   **Handling Edge Cases (`right < left`)** Resets the `right` pointer if it falls behind the `left` pointer.

## Edge Cases Handled

*   **No Good Segment:** If no segment with a sum greater than or equal to `s` exists, the algorithm correctly outputs -1. This is handled by checking if `minLen` remains `LLONG_MAX` after the loop.
*   **Empty Array or Zero Length segments are not possible:** Since the left pointer always iterates, all segments are greater than length 0.
*   **All non-negative elements:**  This is key to the sliding window technique's efficiency.

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

    // all array values are non-negative
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

        if (left <= right - 1) {
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
*Documentation generated on 2025-08-17 11:44:28*
