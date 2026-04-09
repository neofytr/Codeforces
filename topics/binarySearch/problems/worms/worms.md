# worms

```markdown
# Problem: Worms (Codeforces Problem 474B)

This document provides a detailed analysis of a C++ solution to the "Worms" problem on Codeforces (https://codeforces.com/problemset/problem/474/B).

## 1. Problem Description

The problem states that there are `n` piles of worms in a row.  The `i`-th pile contains `pile[i]` worms. We are given `m` queries. Each query represents a juicy worm numbered from 1 to the total number of worms. For each query worm, we need to determine which pile it belongs to and output the pile number.

Formally:

*   Input:
    *   `n`: The number of piles.
    *   `pile[i]`: The number of worms in the i-th pile (0-indexed).
    *   `m`: The number of juicy worms to find.
    *   `juicy[k]`: The juicy worm's number we are looking for (1-indexed).

*   Output:
    *   For each `juicy[k]`, print the pile number (1-indexed) it belongs to.

## 2. Approach Explanation

The solution uses a prefix sum-like approach combined with binary search to efficiently determine the pile to which each juicy worm belongs.

1.  **Preprocessing (Prefix Sum Calculation):**  The code calculates the starting index of each pile.  It creates a `start` vector where `start[i]` stores the index of the first worm in the `i`-th pile.  This is analogous to a prefix sum, but it represents the starting points instead of cumulative sums. `start[0]` is initialized to 0, and `start[i] = start[i-1] + pile[i-1]` for `i > 0`.

2.  **Query Processing (Binary Search):** For each juicy worm `juicy[k]`, the code performs a binary search on the `start` vector.  The goal is to find the largest index `r` such that `juicy[k] >= start[r]`.  This means `juicy[k]` falls within the `r`-th pile.

3.  **Pile Number:** Since the index is 0-indexed, and the problem requires the pile number (1-indexed), the result `left + 1` (where `left` is the result of binary search) is printed for each query.

## 3. Key Insights and Algorithmic Techniques Used

*   **Prefix Sum Concept:** The `start` vector effectively calculates the starting index of each pile, enabling efficient lookup of pile membership.  It's a subtle but crucial optimization.  Without this, we would potentially need to iterate through the `pile` array for each query.

*   **Binary Search:** Binary search is the core algorithmic technique used to efficiently find the pile for each worm.  It leverages the fact that the `start` vector is monotonically increasing, allowing us to quickly narrow down the search space. Specifically, it finds the *last* index whose start is not *greater* than the juicy worm number.

*   **Monotonicity:** The `start` vector is monotonically increasing. This is because each element is built by adding the number of worms of a pile, which by definition, cannot be negative. Monotonicity allows us to use binary search.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Preprocessing (calculating `start`): O(n)
    *   Query processing (binary search for each worm): O(m log n)
    *   Overall: O(n + m log n)
    Since `n` and `m` are independent, the overall time complexity is O(n + m log n).

*   **Space Complexity:**
    *   `pile` vector: O(n)
    *   `juicy` vector: O(m)
    *   `start` vector: O(n)
    *   Overall: O(n + m)

## 5. Important Code Patterns or Tricks Used

*   **Binary Search Implementation:** The binary search implementation uses `left = -1` and `right = n` as initial bounds. This avoids boundary issues when the target is smaller than `start[0]` or larger than or equal to the last pile. The condition `right != left + 1` guarantees the search terminates correctly.  The choice to update `left = mid` when `elt >= start[mid]` and `right = mid` otherwise ensures correct convergence.

*   **1-based vs 0-based indexing:** The problem uses 1-based indexing for the worm numbers, while the code uses 0-based indexing for array accesses.  The code correctly handles the conversion by decrementing `val` before storing it in the `juicy` vector and adding 1 to the final result `left + 1`.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:**  These lines are standard optimizations in competitive programming to speed up input/output operations by disabling synchronization between the C and C++ standard streams.

## 6. Any Edge Cases Handled

*   **Empty Pile(s):** The problem doesn't explicitly disallow empty piles (piles with zero worms). The code correctly handles this case because the `start` vector will simply have consecutive equal values in the case of empty piles, and the binary search will still function correctly.

*   **Juicy worm number less than 1:** The problem statement indicates juicy worm numbers are 1-indexed, so they should be greater than or equal to 1. The code decrements these numbers by 1, so the internal representation is 0-indexed. If `juicy[k]` is 1, then `elt` becomes 0, and the binary search will search for the right most pile whose start index is <= 0.

*   **Juicy worm number exceeding total worms:** If `juicy[k]` is greater than the total number of worms in all the piles, the binary search will correctly find the last pile (`left = n-1`).
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: worms
// URL: https://codeforces.com/problemset/problem/474/B
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> pile(n);
    for (int &val : pile)
        cin >> val;

    int m;
    cin >> m;
    vector<int> juicy(m);
    int val;
    for (int index = 0; index < m; index++) {
        cin >> val;
        val--;
        juicy[index] = val;
    }

    vector<int> start(n);
    start[0] = 0;
    // start[r] = start[r - 1] + pile[r - 1];
    for (int i = 1; i < n; i++) {
        start[i] = start[i - 1] + pile[i - 1];
    }

    // we are to find the max index r such that juicy[k] >= start[r]
    // start is monotonic

    for (int k = 0; k < m; k++) {
        int elt = juicy[k];

        int left = -1;
        int right = n;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (elt >= start[mid])
                left = mid;
            else
                right = mid;
        }

        cout << left + 1 << endl;
    }

    return 0;
}
```

---
*Documentation generated on 2025-08-11 07:16:07*
