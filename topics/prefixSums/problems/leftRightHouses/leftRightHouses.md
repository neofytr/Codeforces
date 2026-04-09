# leftRightHouses

```markdown
# Competitive Programming Solution Documentation: Left-Right Houses

This document analyzes a C++ solution for the "Left-Right Houses" problem found on Codeforces (https://codeforces.com/problemset/problem/1945/C).

## 1. Problem Description (Inferred)

The problem likely presents a street with *n* houses.  Each house *i* is occupied by a resident who either prefers to live on the left (represented by '0') or on the right (represented by '1'). The task is to find the optimal location for a dividing "road" (represented by an integer `road` between 0 and *n*) such that residents who want to live on the side of the road where they actually live are maximized. Specifically, a resident *i* (1 <= *i* <= *n*) prefers to live on the left if `arr[i]` is 0, and on the right if `arr[i]` is 1. The road divides the street into two sides: houses 1 to `road` are on the left, and houses `road` + 1 to *n* are on the right. The goal is to find the location `road` that minimizes `abs(2 * road - n)` from all the locations that satisfy the condition of having at least half of the people who want to live on that side to live on it.

## 2. Approach Explanation

The solution uses a brute-force approach to iterate through all possible positions of the dividing road (from 0 to *n*). For each position, it calculates the number of residents who are "happy" on both the left and right sides of the road.

Specifically, the `left` variable counts the number of residents on the left side of the road (houses 1 to `road`) who want to live on the left (have `arr[i]` == 0). Similarly, the `right` variable counts the number of residents on the right side of the road (houses `road` + 1 to *n*) who want to live on the right (have `arr[i]` == 1).

The solution then checks if at least half the residents on the left side prefer to live on the left ( `left >= (leftSide + 1) / 2`), and at least half the residents on the right side prefer to live on the right (`right >= (rightSide + 1) / 2`).  If both conditions are met, the road position is considered a potential solution.

The solution uses a `set` named `ans` to store the valid road positions. The `set` stores pairs of `(abs(2 * road - n), road)`. This allows the solution to automatically maintain the valid road positions in sorted order based on their proximity to the middle of the street (minimizing `abs(2 * road - n)`), and then the road itself, ensuring tie breaks always pick the smaller road number.

Finally, the solution outputs the road position of the smallest value `abs(2 * road - n)` that satisfies the condition from the beginning of the `ans` set.

## 3. Key Insights and Algorithmic Techniques Used

*   **Brute Force with Optimization:** The core approach iterates through all possible road positions.  This is feasible due to the constraint on *n*.
*   **Incremental Update of Counts:** The solution efficiently updates the `left` and `right` counts as the road position changes, avoiding recalculating them from scratch in each iteration.
*   **Set for Automatic Sorting and Deduplication:** The `set` data structure is used to automatically sort the valid road positions based on the primary criterion `abs(2 * road - n)` and the secondary criterion `road` . It avoids any explicit sorting step. Also, it guarantees uniqueness of potential road locations.
*   **Greedy based on Condition:** The problem is essentially a problem that combines a check of a condition and finding the location that matches it. This could be optimized by doing binary search, but this code takes an initial greedy approach.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The solution iterates through all *n* possible road positions in the `while (road <= n)` loop. Inside the loop, the calculations and set operations take constant time per iteration (on average for sets).  Therefore, the overall time complexity is O(*n*) per test case. The outer loop iterates over `t` test cases, thus the total time complexity is O(t * n).

*   **Space Complexity:** The `arr` vector requires O(*n*) space. The `set` `ans` can, in the worst-case, store all possible road positions, also requiring O(*n*) space. The other variables require constant space. Hence, the space complexity is O(*n*).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a standard optimization technique used in C++ competitive programming to disable synchronization between C and C++ streams, resulting in faster input/output.
*   **Using a `set` to automatically maintain sorted and unique results:** This simplifies the process of finding the optimal road position by automatically sorting potential solutions based on the defined criteria.
*   **Incremental Calculation:** The `left` and `right` counts are updated incrementally rather than recalculated from scratch in each iteration.
*   **`int long long`**:  using long long int is very important to avoid overflow problems in the calculation of `2 * road - n`.
*   **`(leftSide + 1) / 2`**: Using this is a good way to determine half of the road side, but if the road side is even, it must have the upper half of values to satisfy the condition.

## 6. Any Edge Cases Handled

*   The solution handles the edge cases where the optimal road position is at the very beginning (`road` = 0) or the very end (`road` = *n*) of the street. The condition `road <= n` takes care of that.
*   The problem statement implies that *n* can be 0. However, the given sample input does not include this, and the condition inside `while(road<=n)` prevents invalid memory accesses. However, a check for `n=0` would be added for more robust code.
* The set implicitly handles cases where multiple positions result in the same minimum `abs(2 * road - n)`. The set then chooses the smallest `road` as the solution.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: leftRightHouses
// URL: https://codeforces.com/problemset/problem/1945/C
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

        set<pair<int, int>> ans;
        vector<int> arr(n + 1);
        for (int index = 1; index <= n; index++)
            arr[index] = str[index - 1] - '0';

        int road = 0;  // road is between road and road + 1
        int left = 0;  // the number of residents on the left of the road that want to live on the left
        int right = 0; // the number of residents on the right of the road that want to live on the right

        for (int i = road + 1; i <= n; i++)
            if (arr[i])
                right++;
        while (road <= n) {
            int leftSide = road;
            int rightSide = n - leftSide;
            if ((left >= (leftSide + 1) / 2) && (right >= (rightSide + 1) / 2))
                ans.insert({abs(2 * road - n), road});
            road++;
            if (road <= n && !arr[road])
                left++;
            if (road <= n && arr[road])
                right--;
        }
        cout << ans.begin()->second << endl;
    }
    return 0;
}
```

---
*Documentation generated on 2025-08-23 10:26:24*
