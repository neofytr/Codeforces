# rangeUpdate

```markdown
# Range Update Problem Documentation

## 1. Problem Description

The problem is a **Range Update** problem. Given an array of integers and a series of update queries, each query specifies a range `[l, r]` (inclusive, 0-indexed) and a value `x`. The task is to add `x` to all elements within the specified range for each query. After processing all queries, the final updated array should be printed. The problem URL is not explicitly provided, but the comment `// Problem: rangeUpdate` indicates the problem name, implying a task where ranges of an array need to be efficiently updated.

## 2. Approach Explanation

The solution utilizes the **difference array** technique to efficiently handle range updates. Instead of directly updating the original array for each query, an auxiliary array `update` (of size `n+1`) is used to store the differences.

Here's a breakdown:

1.  **Initialization:** An `update` array is initialized with all values set to 0.

2.  **Query Processing:** For each update query `(l, r, x)`:
    *   `update[l]` is incremented by `x`. This marks the start of the range where `x` needs to be added.
    *   `update[r + 1]` is decremented by `x`. This cancels out the addition of `x` beyond the end of the range.  It is *crucial* that `r+1` is a valid index, which is why the `update` array is of size `n+1`.

3.  **Propagating Updates:** After processing all queries, the `update` array represents the differences between consecutive elements of the *final* array. To obtain the actual updated array:
    *   `arr[0]` is directly updated by adding `update[0]`.
    *   For each subsequent element `arr[i]` (where `i > 0`), `update[i]` is updated by adding `update[i - 1]`. This cumulatively sums the updates.
    *   Finally, `arr[i]` is updated by adding the cumulative `update[i]`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Difference Array:** This is the core technique. Instead of directly updating the array, the difference array stores the changes between consecutive elements. Range updates then become point updates on the difference array. This significantly improves efficiency. The key idea is that adding `x` to range `[l, r]` is equivalent to adding `x` at index `l` and subtracting `x` at index `r+1` of the difference array.  The `update` array is essentially the difference array here.
*   **Prefix Sum (Cumulative Sum):** After processing all the updates on the difference array, a prefix sum operation is performed to reconstruct the final updated array.  The propagation of updates is effectively calculating the prefix sum of the `update` array.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Initialization of `arr`: O(n)
    *   Initialization of `update`: O(n)
    *   Query processing: O(q) where `q` is the number of queries. Each query involves two constant-time operations.
    *   Propagating updates (prefix sum): O(n)
    *   Therefore, the overall time complexity is **O(n + q)**.

*   **Space Complexity:**
    *   `arr`: O(n)
    *   `update`: O(n)
    *   Therefore, the overall space complexity is **O(n)**.

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This redefines the `int` data type as `long long`, which is useful for handling larger integer values and preventing potential integer overflow issues, especially in competitive programming where constraints can be tight.  This is important because range updates can quickly increase the values of array elements.  It is declared before the `main` function.  Note: It is crucial to ensure that you use `int32_t main()` if you use this macro.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique used in C++ to speed up input/output operations. It disables synchronization between the C and C++ standard input/output streams and unties `cin` from `cout`, preventing unnecessary flushes.

*   **0-based Indexing:** The code clearly states that the input range indices `l` and `r` are 0-based.

## 6. Any Edge Cases Handled

*   The code implicitly handles the case where `r` is the last element of the array. Since `update` is of size `n+1`, `update[r + 1]` will be a valid index even when `r = n - 1`. This ensures that the update is correctly cancelled beyond the last element.
*   The code handles the case when the array is initially all zeros or contains negative numbers since it directly adds the updates to the existing array elements.
* The `update` array initialization to 0 handles the case when the number of update queries is zero. It ensures that the array `arr` remains unchanged after the updates are applied (which are effectively no updates).
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rangeUpdate
// URL: Not provided
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

    vector<int> update(n + 1, 0);
    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x; // l,r are 0-based indexes
        update[l] += x;
        update[r + 1] -= x;
    }

    // propagate all updates and finally update the real array
    arr[0] += update[0];
    for (int index = 1; index < n; index++) {
        update[index] += update[index - 1];
        arr[index] += update[index];
    }

    for (const int val : arr)
        cout << val << " ";
    cout << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-22 09:21:08*
