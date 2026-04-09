# substringSwap

```markdown
# Competitive Programming Solution Documentation: Substring Swap

This document analyzes a C++ solution for the "substringSwap" problem from AtCoder Beginner Contest 419 (Task D).

## 1. Problem Description

The problem, accessible at [https://atcoder.jp/contests/abc419/tasks/abc419_d](https://atcoder.jp/contests/abc419/tasks/abc419_d), asks us to modify a string `s` based on a series of substring swap operations. We are given two strings, `s` and `t`, of length `n`. We are also given `m` operations. Each operation consists of two indices `l` and `r` (0-indexed).  For each operation, we're supposed to "swap" the characters `s[i]` and `t[i]` for all indices `i` between `l` and `r` (inclusive). After performing all the swaps, we need to output the resulting string `s`.  Crucially, the swaps should happen only when an odd number of operations overlap on index `i`.

## 2. Approach Explanation

The solution uses a difference array technique to efficiently track the number of overlapping operations at each index. Instead of iterating through each operation to swap characters within a given range, we create a `diff` array of size `n + 1`.

For each operation `(l, r)`, we increment `diff[l]` and decrement `diff[r + 1]`. After processing all `m` operations, we compute the prefix sum of the `diff` array. The value of `diff[i]` after calculating prefix sum represents the number of times the index `i` is included in the specified ranges of operations.

Finally, we iterate through the string `s`, and for each index `i`, we check if `diff[i]` is odd. If it is, it indicates an odd number of operations overlap on index `i`, which requires us to swap `s[i]` and `t[i]`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Difference Array:** The core technique employed is the use of a difference array. Difference arrays allow us to apply the same update (increment or decrement) to an entire range of elements in O(1) time per update. This is significantly faster than naive O(n) range updates, especially when dealing with numerous updates.
*   **Prefix Sum:** After applying updates to the difference array, a prefix sum calculation transforms the `diff` array into an array representing the cumulative number of operations at each index.
*   **Parity:** The solution utilizes the concept of parity to determine whether a swap is necessary. If the number of operations overlapping at an index is odd, the swap occurs; otherwise, it doesn't.  This simplification avoids explicitly tracking and managing multiple swaps at a single index.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Reading input: O(n + m)
    *   Updating the difference array: O(m)
    *   Calculating the prefix sum: O(n)
    *   Swapping characters: O(n)
    Therefore, the overall time complexity is **O(n + m)**.

*   **Space Complexity:**
    *   `s` and `t`: O(n)
    *   `diff`: O(n)
    Therefore, the overall space complexity is **O(n)**.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimization disables synchronization between C++ iostreams and the C standard input/output streams, and unties `cin` from `cout`, resulting in faster input/output operations. This is crucial in competitive programming where execution time is often limited.
*   **`#define int long long`**:  This macro redefines `int` as `long long`. This pattern prevents integer overflow issues, especially when dealing with large numbers.
*   **Zero-based indexing:** The code consistently uses zero-based indexing for strings and arrays, a standard convention in C++ programming.
*   **In-place swap:** The standard `swap(s[r], t[r])` function performs an in-place swap of characters, avoiding the need for temporary variables.

## 6. Any Edge Cases Handled

*   The code implicitly handles the case where no operations are provided (`m = 0`). In this case, the `diff` array remains all zeros, and no swaps occur, resulting in the original string `s` being outputted.
*   The increment `diff[l] += 1` and decrement `diff[r+1] -= 1` pattern implicitly handles the boundary case for the last index. When `r` is equal to `n - 1`, the decrement `diff[r+1] -=1` translates to `diff[n] -= 1`, which is a valid element given `diff`'s size of `n+1`.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: substringSwap
// URL: https://atcoder.jp/contests/abc419/tasks/abc419_d
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    int l, r;
    vector<int> diff(n + 1);
    while (m--) {
        cin >> l >> r;
        l--, r--;
        diff[l] += 1;
        diff[r + 1] -= 1;
    }
    for (int r = 1; r <= n; r++)
        diff[r] += diff[r - 1];

    for (int r = 0; r < n; r++)
        if (diff[r] & 1)
            swap(s[r], t[r]);
    cout << s << endl;
    return 0;
}
```

---
*Documentation generated on 2025-09-08 13:01:04*
