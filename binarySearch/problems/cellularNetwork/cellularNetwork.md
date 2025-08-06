# cellularNetwork

```markdown
## Documentation for Cellular Network Problem

This document provides a comprehensive analysis of the provided C++ code, which solves the "Cellular Network" problem on Codeforces (https://codeforces.com/contest/702/problem/C).

### 1. Problem Description

The problem involves two sets of locations: cities and cellular towers.  Given the positions of *n* cities and *m* towers along a line (integers), the goal is to find the minimum radius *r* such that every city is within distance *r* of at least one tower.  The positions of cities and towers are given in non-decreasing order.

### 2. Approach Explanation

The code employs a binary search algorithm to efficiently find the minimum radius *r*. The core idea is that if a radius *r* works (i.e., every city is within distance *r* of a tower), then any radius greater than *r* will also work. Conversely, if a radius *r* doesn't work, any radius less than *r* will also not work. This "monotonicity" property enables the use of binary search.

The `works(r, cities, towers)` function checks if a given radius *r* is sufficient to cover all cities.  For each city, it finds the closest tower using `lower_bound` (another binary search) in the `towers` vector.  It considers the tower found by `lower_bound` and the tower immediately before it (if it exists). It then determines the minimum distance between the city and these two towers. If this minimum distance is greater than *r*, the function returns `false` (meaning *r* is not sufficient). If all cities are covered by the radius *r*, the function returns `true`.

The `main` function performs the binary search on the possible values of *r*. It initializes `left` to -1 and `right` to 2e9. The binary search continues until `right == left + 1`. The `right` variable then holds the minimum radius that works.

### 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search:** The core algorithmic technique is binary search on the possible radius values. This is applicable due to the monotonic property of the problem.
*   **`lower_bound`:**  The `lower_bound` function from the `<algorithm>` header is crucial for efficiently finding the closest tower to each city. `lower_bound(first, last, val)` returns an iterator to the first element in the range `[first, last)` that is not less than `val`.
*   **Monotonicity:** The key insight is the monotonic property: if radius *r* works, any radius greater than *r* also works.
*   **Optimization:** Setting `ios_base::sync_with_stdio(false)` and `cin.tie(NULL)` at the beginning of `main` optimizes input/output operations, which can be crucial for performance in competitive programming.
*   **Edge Case Handling within `works` function:** The code correctly handles the edge cases where the `lower_bound` iterator points to the end of the `towers` vector (no tower is greater than or equal to the city's position) or when it points to the beginning (no tower is less than the city's position) inside the `works` function.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   The `works` function has a time complexity of O(n log m), where n is the number of cities and m is the number of towers. This is because it iterates through each city (O(n)) and performs a binary search (using `lower_bound`) on the towers (O(log m)).
    *   The binary search in `main` iterates O(log (2e9 + 1)) times, which is approximately O(log 2e9).
    *   Therefore, the overall time complexity is O(n log m * log(2e9)). Since the constant factor log(2e9) is relatively small, the time complexity is often approximated to **O(n log m)**, assuming the range of radius is not extremely large.

*   **Space Complexity:**
    *   The code uses vectors `cities` and `towers` to store the city and tower positions, which have sizes n and m respectively.
    *   Therefore, the space complexity is **O(n + m)**.

### 5. Important Code Patterns or Tricks Used

*   **Binary Search Template:**  The code demonstrates a standard binary search template:

    ```cpp
    int left = -1;
    int right = 2e9;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (works(mid, cities, towers))
            right = mid;
        else
            left = mid;
    }
    ```

    This template is useful for finding the minimum value that satisfies a certain condition (in this case, the minimum radius *r*). The use of `left = -1` and `right = 2e9` establishes the bounds for the search space. This is a common trick that ensures all possible values are considered.

*   **`lower_bound` Usage:** The use of `lower_bound` to find the closest tower is a crucial optimization, reducing the complexity from O(m) (linearly searching for the closest tower) to O(log m).

*   **Type Alias `int long long`:** The `#define int long long` statement is used to prevent integer overflow issues, especially when dealing with large input values. Using `long long` provides a larger range for integer values.

*   **I/O Optimization:** `ios_base::sync_with_stdio(false); cin.tie(NULL);` are used to speed up input and output, which can be critical for avoiding time limit exceeded errors.

### 6. Any Edge Cases Handled

*   **Empty `towers` Vector:** The code doesn't explicitly handle the case where the `towers` vector is empty. If the `towers` vector is empty, `lower_bound` will always return `towers.end()`. The `works` function should theoretically return `false` in this scenario, and the binary search will find the minimum acceptable radius as `2e9`. This is acceptable, as this means an extremely large radius is necessary to make sure all cities are within range of some tower.
*   **Edge Cases Inside `works` function:** The `works` function handles the boundary conditions for when a city is located before the first tower, or after the last tower in `towers` by using conditions `if (it != towers.end())` and `if (it != towers.begin())` to ensure there isn't any out of bounds access.

This documentation provides a thorough understanding of the code, including its purpose, approach, algorithmic techniques, complexity, and important details.
```

## Original Code
```cpp
#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

// Problem: cellularNetwork
// URL: https://codeforces.com/contest/702/problem/C
// Difficulty: hard
// Tags:
// Strategy:

#define int long long

bool works(int r, const vector<int> &cities, const vector<int> &towers) {
    for (int city : cities) {
        // find the closest tower using binary search
        auto it = lower_bound(towers.begin(), towers.end(), city);
        int dist = LLONG_MAX;

        if (it != towers.end())
            dist = min(dist, abs(city - *it));
        if (it != towers.begin())
            dist = min(dist, abs(city - *prev(it)));

        if (dist > r)
            return false;
    }
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> cities(n);
    for (int &val : cities)
        cin >> val; // in non-decreasing order

    vector<int> towers(m);
    for (int &val : towers)
        cin >> val; // in non-decreasing order

    // now we are sure that r = -1 won't work
    // also, we are fairly certain that r = 1e9 would work
    // also, if some distance r = x works, then distance r = x + 1 also works
    // so, there must be an r = y such that any r = x such that x < y won't work and any r = x where x >= y will work
    // since r = 0 doesn't work and r = 1e9 does

    int left = -1;
    int right = 2e9;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (works(mid, cities, towers))
            right = mid;
        else
            left = mid;
    }

    cout << right << endl;

    return EXIT_SUCCESS;
}
```

---
*Documentation generated on 2025-08-06 17:12:23*
