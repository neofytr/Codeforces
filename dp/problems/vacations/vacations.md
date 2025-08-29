# vacations

```markdown
# Code Documentation: Vacations Problem

This document provides a comprehensive analysis of the provided C++ code solution for the "Vacations" problem found on Codeforces (https://codeforces.com/problemset/problem/698/A).

## 1. Problem Description

The problem describes a scenario where you have `n` days of vacation. Each day offers different activities: rest, contest, or sport (gym). However, there are constraints on which activities can be performed each day based on the availability of the gym and contests.  The goal is to minimize the number of rest days taken during the vacation, given the schedule of available activities.

Specifically:

*   **Each day is assigned a number from 0 to 3:**
    *   0:  Only rest is possible.
    *   1:  Only contest is possible.
    *   2:  Only sport (gym) is possible.
    *   3:  Both contest and sport are possible.

*   **You cannot perform the same activity on two consecutive days.**

The objective is to determine the minimum number of rest days to enjoy your vacation adhering to the above constraints.

## 2. Approach Explanation

The code utilizes dynamic programming to solve this optimization problem.

*   **State Definition:**
    The core idea is to define a `dp[r][k]` table where:
    *   `r` represents the number of days considered (from 1 to `n`).
    *   `k` represents the activity performed on the `r`th day:
        *   `k = 0`: Rest
        *   `k = 1`: Sport (gym)
        *   `k = 2`: Contest
    *   `dp[r][k]` stores the minimum number of rest days up to day `r`, ending with activity `k` on day `r`.

*   **Base Cases:**
    The base cases are initialized for the first day (`r = 1`). The number of rest days for the first day depends on what activities are possible on that day:

    *   `dp[1][0] = 1`: Resting on the first day always incurs 1 rest day.
    *   If contest is possible on day 1 (`arr[1] == 2 || arr[1] == 3 || arr[1] == 4`), then `dp[1][2] = 0` (no rest day).
    *   If sport is possible on day 1 (`arr[1] == 3 || arr[1] == 4`), then `dp[1][1] = 0` (no rest day).

*   **Transitions:**
    The code iterates from day 2 to `n`, calculating the optimal number of rest days for each possible activity `k` on that day. The transitions ensure that the same activity isn't performed on consecutive days.

    *   **If only rest is possible on day `r` (`arr[r] == 1`)**:
        `dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;`
        We have to rest, so we add 1 to the minimum rest days of the previous day, regardless of what we did then.

    *   **If contest is possible on day `r` (`arr[r] == 2`)**:
        `dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;`
        `dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);`
        We can rest (similar to above), or we can participate in the contest if we rested or did sport the previous day.

    *   **If sport is possible on day `r` (`arr[r] == 3`)**:
        `dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;`
        `dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);`
        We can rest, or we can do sport if we rested or did contest the previous day.

    *   **If both contest and sport are possible on day `r` (`arr[r] == 4`)**:
        `dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;`
        `dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);`
        `dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);`
        We can rest, or we can do sport or contest as long as we didn't do the same activity the previous day.

*   **Final Result:**
    The minimum number of rest days is the minimum value among `dp[n][0]`, `dp[n][1]`, and `dp[n][2]`.  This represents the minimum number of rest days after considering all `n` days, ending in rest, sport, or contest, respectively.

## 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:** This is the core technique. The problem exhibits optimal substructure (the optimal solution for `n` days can be constructed from the optimal solutions for `n-1` days) and overlapping subproblems (the same subproblems are solved multiple times).  DP is a natural fit for this kind of problem.

*   **State Representation:** The careful choice of the state `dp[r][k]` is crucial. It encodes the information needed to make decisions at each step (day) while remembering the history (previous activities) sufficiently to avoid repeating activities.

*   **Careful Transition Logic:**  The transitions from `dp[r-1][...]` to `dp[r][...]` are the heart of the DP solution.  They correctly enforce the constraint that the same activity cannot be performed on consecutive days and consider the availability of activities on each day.

*   **Initialization:** Correct initialization with `LLONG_MAX` except for the base cases prevents incorrect results due to uninitialized values affecting the `min()` operations.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The code iterates through `n` days and for each day, it iterates through the 3 possible activities. Therefore, the time complexity is O(n * 3) which simplifies to O(n).

*   **Space Complexity:** The code uses a `dp` table of size (n+1) x 3. Therefore, the space complexity is O(n * 3) which simplifies to O(n).

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is a common practice in competitive programming to avoid integer overflow issues, especially when dealing with large input values or intermediate calculations.

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines optimize input/output operations, making the code run faster.  They disable synchronization between the C++ standard input/output streams and the C standard input/output streams.

*   **Using `LLONG_MAX` for initialization:** Initializing the `dp` array with `LLONG_MAX` ensures that the `min()` operations work correctly.  Any path that is not possible will effectively be ignored.

*   **`arr[index]++;`**: This clever trick offsets the activity indices to be 1-indexed instead of 0-indexed. This simplifies the subsequent logic by allowing activities to be represented as 1 (contest), 2 (sport), 3 (both), or 4 (both), which simplifies later calculations and conditionals. It maps the problem's original 0, 1, 2, 3 inputs to an easier to manage 1, 2, 3, 4 input.

## 6. Any Edge Cases Handled

*   **Empty vacation (n=0):** Although not explicitly handled by an `if (n==0)` check, the loops work correctly when n=0, resulting in a vector of size `1` and an accurate result of 0.
*   **Impossible schedules:** The code implicitly handles cases where it's impossible to perform any activity due to constraints. In such scenarios, the final `min()` operation will return a very large value, reflecting that no valid solution exists with a low rest count.  If the problem had a specific requirement to detect "impossible" schedules (e.g., print -1), then a check for `LLONG_MAX` in the final result would be necessary.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: vacations
// URL: https://codeforces.com/problemset/problem/698/A
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
        arr[index]++;
    }

    // dp[r][k] is the minimum number of rest days in the initial r days with the rth day having kth work
    // k = 0 for rest, 1 for sport and 2 for contest
    vector<vector<int>> dp(n + 1, vector<int>(3, LLONG_MAX));
    dp[1][0] = 1;
    if (arr[1] == 2)
        dp[1][2] = 0;
    if (arr[1] == 3)
        dp[1][1] = 0;
    if (arr[1] == 4) {
        dp[1][1] = 0;
        dp[1][2] = 0;
    }

    for (int r = 2; r <= n; r++) {
        if (arr[r] == 1) {
            // gym is closed and there is no contest
            // this is a rest day
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
        } else if (arr[r] == 2) {
            // gym is closed but the contest is carried out
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);
        } else if (arr[r] == 3) {
            // gym is open but contest is not carried out
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
        } else {
            // both gym and contest are open
            dp[r][0] = min(dp[r - 1][0], min(dp[r - 1][1], dp[r - 1][2])) + 1;
            dp[r][1] = min(dp[r - 1][0], dp[r - 1][2]);
            dp[r][2] = min(dp[r - 1][0], dp[r - 1][1]);
        }
    }

    cout << min(dp[n][0], min(dp[n][1], dp[n][2])) << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-29 17:06:52*
