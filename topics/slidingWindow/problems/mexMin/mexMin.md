# mexMin

```markdown
# Competitive Programming Solution Analysis: mexMin

This document analyzes a C++ solution for the "mexMin" problem, likely from a competitive programming contest. Based on the comments and code, we can infer the problem statement.

## 1. Problem Description

The problem, likely from [AtCoder Beginner Contest 194 E - mexMin](https://atcoder.jp/contests/abc194/tasks/abc194_e), asks to find the minimum MEX (Minimum EXcluded value) of all subarrays of length `m` in a given array `arr` of length `n`.

Formally:

*   **Input:** An array `arr` of `n` non-negative integers, and an integer `m` representing the subarray length.
*   **Output:** The minimum MEX value among all subarrays of `arr` with length `m`.

The MEX of a set of non-negative integers is the smallest non-negative integer that is *not* present in the set.

## 2. Approach Explanation

The code implements a sliding window approach to solve this problem efficiently.  It iterates through the array using a window of size `m`, calculating the MEX of each window, and keeping track of the minimum MEX encountered so far.

Here's a step-by-step breakdown:

1.  **Initialization:**
    *   `mex`: A `set` is used to store the potential MEX values. It's initialized with all non-negative integers from 0 to `n`, inclusive. This is because the MEX of any subset of the input array cannot be greater than `n`.
    *   `mp`: An `unordered_map` is used to store the frequency of each element within the current window.
    *   `l`: Left pointer of the sliding window, initialized to 0.
    *   `mini`: Stores the minimum MEX encountered, initialized to `LLONG_MAX`.

2.  **Sliding Window Iteration:**
    *   The code iterates using the right pointer `r` from 0 to `n-1`.
    *   For each element `arr[r]`, its frequency in the current window (`mp[arr[r]]`) is incremented.
    *   If `arr[r]` is currently a possible MEX value (i.e., `arr[r]` is present in the `mex` set), it's removed from the `mex` set because it's now present in the current window.
    *   When the window size reaches `m` (i.e., `r - l + 1 == m`):
        *   The current MEX value (which is the smallest element in the `mex` set, accessed via `*mex.begin()`) is compared with the current minimum MEX (`mini`), and `mini` is updated if necessary.
        *   The element at the left end of the window (`arr[l]`) is removed from the window: its frequency in `mp` is decremented.
        *   If the frequency of `arr[l]` becomes 0 after decrementing, it means `arr[l]` is no longer present in the current window, so it's re-inserted into the `mex` set as a potential MEX value.
        *   The left pointer `l` is incremented to slide the window forward.

3.  **Result:**
    *   After the iteration, `mini` contains the minimum MEX value among all subarrays of length `m`, which is printed to the console.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The core idea is to use a sliding window of size `m` to efficiently process each subarray. This avoids redundant calculations.
*   **Set for MEX Tracking:** The `set` data structure is crucial for efficiently tracking the potential MEX values. The `set` ensures that the elements are always sorted, allowing for quick retrieval of the smallest element (the MEX) using `*mex.begin()`. The `erase` and `insert` operations on a set have logarithmic time complexity, which is acceptable for this problem.
*   **Unordered Map for Frequency Counting:** The `unordered_map` efficiently stores the frequencies of elements within the current window. This allows for quick updates when adding or removing elements from the window.
*   **MEX Definition Application:**  The initial insertion of 0 to n into the `mex` set ensures that we cover all possible MEX values. Removing existing values and then re-inserting them when they are no longer in the current window are key to finding the minimum possible MEX.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Initializing the `mex` set takes O(n log n) time because `insert` operation in a `set` is O(log n).
    *   The sliding window iterates `n` times.
    *   Inside the loop, the operations `mp[arr[r]]++`, `mex.erase(arr[r])`, `mex.insert(arr[l])`, and `--mp[arr[l]]` take O(1) (amortized) for the `unordered_map` and O(log n) for the `set`.
    *   Therefore, the overall time complexity is O(n log n).
*   **Space Complexity:**
    *   The `arr` vector takes O(n) space.
    *   The `mex` set can store at most `n+1` elements, so it takes O(n) space.
    *   The `mp` `unordered_map` can store at most `n` elements, so it takes O(n) space.
    *   Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between the C++ standard input/output streams and the C standard input/output streams. It also unties the `cin` and `cout` streams, which can significantly improve input/output performance, particularly in competitive programming.
*   **`#define int long long`:** This macro redefines the `int` data type to `long long`. This is commonly used in competitive programming to prevent integer overflow issues when dealing with large numbers. It should be carefully considered if the memory constraint is very strict.
*   **Using `set` for MEX calculation:** A set automatically maintains elements in sorted order and provides efficient lookups and deletions, making it an ideal data structure for tracking potential MEX values. `*mex.begin()` gives the minimal element.

## 6. Any Edge Cases Handled

*   The code handles the edge case where all numbers from 0 to `n` are present in the array by initializing the `mex` set with values from 0 to `n`. If any of these numbers are not present in a subarray of size `m`, it will be the MEX.
*   The code implicitly handles the case where `m > n`. In this scenario, the loop `for (int r = 0; r < n; r++)` will run to completion without the inner `if (r - l + 1 == m)` ever being true. The initial value of `mini = LLONG_MAX` will be preserved. However, without an explicit check for `m > n`, the result is technically incorrect as the MEX is only defined for non-empty sets and here, no window of size `m` exists.  A check for `m > n` and returning 0 could be added for completeness and correctness, assuming the problem statement's requirement. The current solution would produce the incorrect output of a large number, equal to LLONG_MAX.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mexMin
// URL: https://atcoder.jp/contests/abc194/tasks/abc194_e
// Difficulty: hard
// Tags: sliding window, set, unordered_map, MEX
// Strategy: Use a sliding window of size 'm' and a set to efficiently track the MEX.

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    set<int> mex;
    for (int r = 0; r <= n; r++)
        mex.insert(r);

    unordered_map<int, int> mp;
    int l = 0;
    int mini = LLONG_MAX;

    for (int r = 0; r < n; r++) {
        mp[arr[r]]++;
        if (mex.find(arr[r]) != mex.end())
            mex.erase(arr[r]);
        if (r - l + 1 == m) {
            mini = min(mini, *mex.begin());
            if (!(--mp[arr[l]]))
                mex.insert(arr[l]);
            l++;
        }
    }
    cout << mini << endl;
    return 0;
}
```


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: mexMin
// URL: https://atcoder.jp/contests/abc194/tasks/abc194_e
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    set<int> mex;
    for (int r = 0; r <= n; r++)
        mex.insert(r);

    unordered_map<int, int> mp;
    int l = 0;
    int mini = LLONG_MAX;
    for (int r = 0; r < n; r++) {
        mp[arr[r]]++;
        if (mex.find(arr[r]) != mex.end())
            mex.erase(arr[r]);
        if (r - l + 1 == m) {
            mini = min(mini, *mex.begin());
            if (!(--mp[arr[l]]))
                mex.insert(arr[l]);
            l++;
        }
    }
    cout << mini << endl;
    return 0;
}
```

---
*Documentation generated on 2025-09-09 19:44:28*
