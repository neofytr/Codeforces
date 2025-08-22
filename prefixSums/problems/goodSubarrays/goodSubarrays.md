# goodSubarrays

```markdown
## Code Documentation: Good Subarrays

This document provides a comprehensive analysis of the provided C++ code, which solves the "goodSubarrays" problem.

**1. Problem Description:**

The problem (available on Codeforces at [https://codeforces.com/contest/1398/problem/C](https://codeforces.com/contest/1398/problem/C)) asks us to find the number of "good subarrays" within a given string of digits. A subarray is considered "good" if the sum of its digits is equal to the length of the subarray.

**2. Approach Explanation:**

The code uses a clever transformation to simplify the problem:

1. **Array Transformation:**  It creates an array `arr` where each element `arr[i]` is equal to `str[i] - '0' - 1`.  This transformation is crucial because it converts the problem into finding subarrays with a sum of 0 in `arr`. A good subarray [l, r] in the original string corresponds to a subarray [l, r] in `arr` with a sum of 0.

2. **Prefix Sums:** It computes the prefix sum array `prefix`. `prefix[i]` stores the sum of the first `i-1` elements of `arr` (from `arr[0]` to `arr[i-2]`). By definition, `prefix[0]` is initialized to 0.

3. **Prefix Sum Equality:**  A subarray `[l, r]` has a sum of 0 in `arr` if and only if `prefix[r + 1] - prefix[l] == 0`, which is equivalent to `prefix[r + 1] == prefix[l]`.  This significantly simplifies the problem.

4. **Counting Good Subarrays:** The code iterates through each possible right endpoint `r` (from 0 to n-1) of a subarray. For each `r`, it counts the number of left endpoints `l` (from 0 to r) such that `prefix[r + 1] == prefix[l]`.  It uses an `unordered_map` (`freq`) to efficiently keep track of the frequency of each prefix sum encountered so far.

**3. Key Insights and Algorithmic Techniques Used:**

*   **Transformation to Sum of Zero:** The transformation `arr[i] = str[i] - '0' - 1` is the core insight. It reframes the problem from comparing the sum of digits with the length of the subarray to finding subarrays with a sum of zero, which is easier to handle with prefix sums.
*   **Prefix Sums for Subarray Sums:** The use of prefix sums is a standard technique for efficiently calculating subarray sums.  The difference between two prefix sums `prefix[r + 1] - prefix[l]` directly gives the sum of the subarray `arr[l]` to `arr[r]`.
*   **Frequency Counting with `unordered_map`:** The `unordered_map` `freq` efficiently counts the number of times each prefix sum value has appeared. This allows for O(1) lookup of the count of prefix sums equal to the current `prefix[r + 1]`, directly giving the number of valid left endpoints `l`.

**4. Time and Space Complexity Analysis:**

*   **Time Complexity:** O(n), where n is the length of the string. The code iterates through the string once to create the `arr` array, once to compute the prefix sums, and once more to count the good subarrays.  The `unordered_map` operations (insert, lookup) are, on average, O(1).
*   **Space Complexity:** O(n) in the worst case. The `arr` and `prefix` arrays both take O(n) space. The `unordered_map` `freq` could potentially store n different prefix sum values, also taking O(n) space.

**5. Important Code Patterns or Tricks Used:**

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**:  This is a common optimization in competitive programming to speed up input/output by disabling synchronization between the C and C++ standard streams.
*   **`#define int long long`**: This redefines `int` as `long long` to avoid integer overflow issues, especially when dealing with large sums.  It's important to use `int32_t main()` instead of `int main()` after this macro.
*   **Use of `unordered_map` for frequency counting**: This provides efficient (average O(1)) access to the frequency of a value.

**6. Edge Cases Handled:**

*   **Empty Subarray (Implicitly):** When `r=0`, the algorithm checks for occurrences of the prefix sum at `r+1` which is `prefix[1]`. It correctly considers left endpoints `l` such that `prefix[l] = prefix[r+1]`. The `freq[0] = 1;` line ensures that the empty subarray (from index 0 to -1) is considered when `prefix[r+1]` is zero.
*   **Integer Overflow:** Using `#define int long long` mitigates potential integer overflow issues that could arise when calculating sums of digits. Although unlikely in this specific problem given the constraint that each digit `str[i]` is from 0 to 9, it is a good practice to use `long long` when dealing with potentially large sums.

**In Summary:**

This code provides an efficient and elegant solution to the "goodSubarrays" problem. Its key strengths lie in the clever problem transformation to finding subarrays summing to zero, the use of prefix sums for fast subarray sum calculation, and the efficient counting of prefix sum occurrences using an `unordered_map`. The code also demonstrates good practices for competitive programming, such as I/O optimization and the use of `long long` to avoid potential integer overflow issues.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: goodSubarrays
// URL: https://codeforces.com/contest/1398/problem/C
// Difficulty: hard
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

        string str;
        cin >> str;

        // a segment [l, r] of the string str is good iff the sum of the elements in this segment = the number of elements in the segment
        // we define an array arr of length n such that
        // arr[i] = str[i] - 1 for all 0 <= i < n

        // a segment [l, r] of the string str is good iff the sum of elements in the array arr segment [l, r] = 0
        //                                            iff prefix[r + 1] - prefix[l] = 0
        //                                            iff prefix[r + 1] = prefix[l]

        // any segment [l, r] where 0 <= l <= r < n of the string str is good iff prefix[r + 1] = prefix[l]
        // for each 0 <= r < n, we count all such 0 <= l <= r such that prefix[r + 1] = prefix[l]
        vector<int> arr(n);
        for (int index = 0; index < n; index++)
            arr[index] = str[index] - '0' - 1;
        vector<int> prefix(n + 1, 0);
        for (int index = 1; index <= n; index++)
            prefix[index] = prefix[index - 1] + arr[index - 1];

        unordered_map<int, int> freq;
        // for any 0 <= r < n, let
        // S(r) = {prefix[f] | 0 <=  f <= r}
        // T(r) = (prefix[0], ..., prefix[r])

        // we maintain that
        // at the start of any iteration r = k of the following loop
        // freq[x] is the number of times x appears in the sequence T(k) for all x in S(k)
        // for any 0 <= k < n

        freq[0] = 1; // maintain the invariant initially
        int count = 0;
        for (int r = 0; r < n; r++) {
            int x = prefix[r + 1];
            count += freq[x];
            freq[x]++;
        }
        cout << count << endl;
    }
}
```

---
*Documentation generated on 2025-08-22 17:56:10*
