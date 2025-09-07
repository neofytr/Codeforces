# approximating

```markdown
# Competitive Programming Solution Documentation

This document provides a comprehensive analysis of the provided C++ code, focusing on its algorithmic approach, time complexity, and key insights.

## 1. Problem Description (Approximating)

Based on the code and comments, this solution addresses the "Approximating" problem from Codeforces Round #333 (Div. 2).  The URL provided is: [https://codeforces.com/contest/602/problem/B](https://codeforces.com/contest/602/problem/B).

The problem (inferred from the code) requires finding the length of the longest subarray within a given array such that the difference between the maximum and minimum elements in that subarray is at most 1.

## 2. Approach Explanation

The code utilizes a sliding window approach with a `multiset` to efficiently track the minimum and maximum elements within the current window. The core idea is to expand the window (increase `r`) as long as the difference between the maximum and minimum values within the window is no more than 1.  If the difference exceeds 1, the window is shrunk from the left (increase `l`) until the condition is satisfied again. The maximum length of a valid window encountered during this process is then recorded and printed as the answer.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** This is the primary technique employed. The `l` and `r` pointers define the boundaries of the current subarray (window).
*   **`multiset` for Min/Max Tracking:**  The `multiset` data structure is crucial. It automatically maintains its elements in sorted order, allowing efficient access to the minimum (`*m.begin()`) and maximum (`*m.rbegin()`) values in O(log N) time, where N is the size of the multiset (the current window size).  The `multiset` is also important because it handles duplicate values correctly, which is a requirement according to the problem statement.
*   **Maintaining the Invariant:**  The `while` loop inside the `for` loop is responsible for maintaining the invariant that the difference between the maximum and minimum elements in the current window (`arr[l...r]`) is always less than or equal to 1.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The outer loop iterates `n` times (for `r` from 0 to `n-1`).  The `multiset` insertion (`m.insert()`) and deletion (`m.erase()`) operations each take O(log n) time in the worst case. The inner `while` loop can also iterate a maximum of `n` times across the whole execution. Thus, the total time complexity is O(n log n).
*   **Space Complexity:** The `vector<int> arr` stores the input array, which takes O(n) space. The `multiset m` stores at most `n` elements in the worst case, also taking O(n) space.  Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a common optimization technique used in competitive programming to disable synchronization between the C and C++ standard input/output streams, which can significantly improve performance, especially for problems with a large amount of input/output.
*   **`#define int long long`:** This is a macro that redefines the `int` type to `long long`. This is done to prevent integer overflow issues, especially when dealing with large input values.
*   **`multiset::erase(multiset::find(value))`**:  When erasing elements from a `multiset`, it's crucial to use `m.erase(m.find(arr[l]))` instead of simply `m.erase(arr[l])`.  The latter will erase *all* occurrences of `arr[l]` from the `multiset`, whereas the former will only erase the *first* occurrence (the one pointed to by the iterator `m.find(arr[l])`). This is important because the sliding window approach requires removing only the leftmost element (`arr[l]`) from the window.
*   **`r >= l` check:**  The code includes `if (r >= l)`. It's used to avoid an empty window case when `l` might equal to `r`. The condition `r - l + 1` calculates the length of the current window, so this condition guards against unexpected behavior.

## 6. Any Edge Cases Handled

*   **Empty Input:**  The code implicitly handles the case where `n` is 0, as the loops won't execute, and `maxi` will remain `LLONG_MIN`. Although, the problem description might prevent `n` from being 0.
*   **All elements are the same:** If all elements in the array are the same, the difference between max and min will always be 0, which is less than or equal to 1. The sliding window will expand to the full array length `n`, and the output will be `n`.
*   **Elements differing by more than 1:** The sliding window logic automatically shrinks the window to only contain valid subarrays, ensuring the maximum difference is always less than or equal to 1.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: approximating
// URL: https://codeforces.com/contest/602/problem/B
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

    int l = 0;
    multiset<int> m;
    int maxi = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        m.insert(arr[r]);
        while (l <= r && *m.rbegin() - *m.begin() > 1)
            m.erase(m.find(arr[l])), l++;
        if (r >= l)
            maxi = max(maxi, r - l + 1);
    }
    cout << maxi << endl;
    return 0;
}
```

---
*Documentation generated on 2025-09-07 22:16:27*
