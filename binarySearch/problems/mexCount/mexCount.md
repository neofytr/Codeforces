# mexCount

```markdown
# Competitive Programming Solution Documentation

## 1. Problem Description

The problem, sourced from [Codeforces Problemset 2123E](https://codeforces.com/problemset/problem/2123/E), named "mexCount," asks to determine the number of possible MEX values after performing exactly *k* deletions from a given array of non-negative integers, for each *k* from 0 to *n* (inclusive), where *n* is the size of the array.  MEX (minimum excluded value) of an array is the smallest non-negative integer that is not present in the array.

## 2. Approach Explanation

The solution employs a strategy based on pre-calculating frequencies, determining the maximum consecutive sequence starting from 0, and then iterating through possible MEX values and deletion counts to determine if a particular MEX is achievable.

Here's a step-by-step breakdown:

1.  **Frequency Calculation:** An `unordered_map` named `freq` is used to store the frequency of each number in the input array.

2.  **Consecutive Sequence Length:** The variable `totalConsec` stores the length of the longest consecutive sequence of non-negative integers present in the array, starting from 0.  This is determined by iterating from 0 and checking if each number exists in the `freq` map until a number is not found.

3.  **Deletable Elements:** The `canDelete` variable keeps track of the total number of elements available for deletion. Initially, this is calculated based on the frequencies. Specifically, for numbers less than `totalConsec`, we can delete all but one instance.  For numbers greater than or equal to `totalConsec`, all instances can be deleted.

4.  **MEX Possibility Iteration:** The code then iterates through all possible deletion counts `k` (from 0 to *n*) and, within that loop, through all possible MEX values `c` (from 0 to `totalConsec`).  For each pair (k, c), it checks if `c` can be the MEX after *k* deletions.

5.  **MEX Achievability Check:** To determine if a MEX value `c` can be achieved after `k` deletions, two conditions must be met:

    *   The frequency of `c` must be less than or equal to `k` (i.e., `freq[c] <= k`). This ensures that we can delete enough occurrences of `c` to make it disappear from the array.

    *   The number of deletable elements must be greater than or equal to the number of deletions required to achieve the MEX `c` with *k* total deletions (i.e., `canDelete - freq[c] + 1 * (totalConsec - c)) >= (k - freq[c])`).  Breaking down the inequality:

        *   `k - freq[c]` is the number of additional deletions needed after deleting all `freq[c]` occurrences of the current mex candidate `c`.
        *   `canDelete - freq[c]` is the amount we can delete assuming we've already deleted `freq[c]` of our mex candidate.
        *   `totalConsec - c` is the number of elements in the range `(c, totalConsec]` and these can all be deleted (given we already deleted all instances of `c`). Since these elements were already counted, we need to add it back.
        *    The final inequality is checking if our initial number of possible deletions, minus what we used to delete the mex candidate, plus one extra deletion possible for all other `totalConsec` values is greater than equal to our total number of deletes.

6.  **Counting Possible MEXes:** For each `k`, the number of achievable MEX values is counted and printed.

## 3. Key Insights and Algorithmic Techniques Used

*   **Greedy Deletion:** The solution implicitly uses a greedy approach. For a given MEX value `c`, it attempts to delete all occurrences of `c` and then utilizes the remaining deletable elements to achieve the desired deletion count `k`.

*   **MEX Property Exploitation:** The critical insight is that the MEX can only be in the range `[0, totalConsec]`.  This drastically reduces the search space for possible MEX values.

*   **Frequency Counting:** Efficient frequency counting using `unordered_map` is crucial for determining the count of each number in the array.

*   **Inclusion-Exclusion Principle (Implicit):** When calculating the `canDelete` and the MEX feasibility, the solution effectively considers elements and their frequencies, adding and subtracting values to account for the elements needed for deletion and the remaining available deletions.  It involves thinking about total deletable items and then making adjustments for edge cases of the proposed MEX candidate.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Calculating frequencies: O(n)
    *   Finding `totalConsec`: O(n) in the worst case (if all numbers from 0 to n-1 are present).
    *   Calculating `canDelete`: O(n), iterating through the frequency map
    *   Outer loop for `k`: O(n)
    *   Inner loop for `c`: O(n) in the worst case (`totalConsec` can be up to n)
    *   Therefore, the overall time complexity is dominated by the nested loops: O(n * n) = O(n<sup>2</sup>).
    *   Because there are `t` test cases, the overall time complexity is O(t * n<sup>2</sup>).

*   **Space Complexity:**
    *   `freq` unordered\_map: O(n) in the worst case (all n elements are distinct).
    *   `arr` vector: O(n)
    *   Other variables: O(1)
    *   Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`unordered_map` for Frequency Counting:** Using `unordered_map` for fast frequency lookups is a common and effective technique.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  These lines disable synchronization between the C++ standard streams and the underlying C standard input/output, and untie cin from cout, respectively. This can significantly improve input/output performance, especially in competitive programming environments.
*   **Macro `int long long`:**  Using `#define int long long` can prevent integer overflow issues that might occur when dealing with large input values.  The `int32_t main()` is required if this definition is used.
*   **`auto& [val, f] : freq`:** The use of structured bindings in the range-based for loop provides a clean way to iterate through the key-value pairs in the `freq` map, using `val` for the key and `f` for the value.

## 6. Any Edge Cases Handled

*   **Empty Array (implicitly):** If the input array is empty (n=0), `totalConsec` becomes 0, and the loops work correctly, producing the expected output.
*   **All zeros:** The code handles the case where the input array contains only zeroes or a consecutive range starting with zero.
*   **Numbers greater than n:** Numbers greater than `n` are handled correctly. Since we are looking for `MEX <= n`, we are only concerned with values up to n, and larger numbers will simply contribute to the number of deletable elements.
*   **Duplicate numbers:** The frequency counting handles duplicate numbers, which is essential for calculating the number of deletable elements correctly. The logic correctly handles cases where you need to delete multiple instances of the same number to find the MEX.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

#define int long long

// Problem: mexCount
// URL: https://codeforces.com/problemset/problem/2123/E
// Difficulty: hard
// Tags:
// Strategy:

void solve() {
    int n;
    cin >> n;

    unordered_map<int, int> freq;
    vector<int> arr(n);
    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        arr[i] = val;
        freq[val]++;
    }

    int totalConsec = 0;
    for (int i = 0; i <= n; i++) {
        if (!freq[i])
            break;
        else {
            totalConsec++;
        }
    }

    // mex(arr) can only belong to the set {0, 1, ..., totalConsec - 1, totalConsec}, no matter how
    // many times we delete

    int canDelete = 0;
    for (auto &[val, f] : freq) {
        if (val < totalConsec)
            canDelete += (f - 1); // since we need atleast one
        else
            canDelete += f;
    }

    for (int k = 0; k <= n; k++) {
        if (!k) {
            cout << 1 << " ";
            continue;
        }

        int cnt = 0;
        for (int c = 0; c <= totalConsec; c++) {
            // we can make this mex after exactly k deletions iff freq[c] <= k and the values that we can delete >= (k - freq[c])
            if (freq[c] <= k && (canDelete - freq[c] + 1 * (totalConsec - c)) >= (k - freq[c])) // since we can delete anything  > c and < totalConsec one more time, we add one for them
                                                                                                // since we already deleted all c, we remove it from canDelete
                cnt++;
        }

        cout << cnt << " ";
    }
    cout << endl;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-11 22:38:04*
