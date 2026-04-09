# vanya

```markdown
# Competitive Programming Solution Documentation: Codeforces Problem 492B - Vanya and Lanterns

This document provides a comprehensive analysis of a C++ solution to Codeforces problem 492B, "Vanya and Lanterns" ([https://codeforces.com/problemset/problem/492/B](https://codeforces.com/problemset/problem/492/B)).

## 1. Problem Description

Vanya walks late at night along a straight street of length *l*, lit by *n* lanterns. The coordinate system is such that 0 is the start of the street and *l* is the end of the street. The *r*-th lantern is at the point *arr[r]*. Each lantern lights all points of the street that are at a distance of at most *d* from it, where *d* > 0. The goal is to find the minimum *d* the lanterns should have to light the whole street.

## 2. Approach Explanation

The problem asks for the minimum distance *d* required for the lanterns to illuminate the entire street.  The core idea is to use binary search to find the optimal value of *d*.

1. **Binary Search:** We perform a binary search on the possible values of *d*. The lower bound is 0, and the upper bound can be a large number (e.g., 2e9+1) since the street length can be up to 1e9.

2. **Checking Feasibility (func function):** For each value of *d* being tested in the binary search, we need to check if the lanterns with radius *d* can cover the entire street. The `func` function does exactly this.  It iterates through the sorted lantern positions and keeps track of the current coverage.  If at any point, there's a gap between the current coverage and the next lantern's leftmost illuminated point (pos - d), the value of *d* is too small, and `func` returns `false`. Otherwise, it extends the coverage up to pos + d.

3. **Sorting:** The lantern positions `arr` are sorted initially to ensure efficient checking of coverage in the `func` function. Sorting allows us to iterate through the lanterns in increasing order of their position and incrementally extend the coverage.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search on Answer:** The problem lends itself well to a binary search approach because we are looking for a minimum value (*d*), and we can efficiently check if a given value of *d* is sufficient to cover the street. The search space is continuous, making binary search a natural choice.
*   **Greedy Coverage Check:** The `func` function uses a greedy approach to check if a given radius *d* is sufficient to cover the street. By sorting the lantern positions, we can incrementally extend the coverage from left to right. This is optimal because we always want to maximize the coverage with each lantern.
*   **Precision Consideration:** The problem requires a floating-point answer with high precision. Setting `cout << setprecision(12)` ensures sufficient decimal places in the output. The binary search is performed for a fixed number of iterations (100) to achieve the desired precision. Using fixed iterations, instead of a condition comparing `left` and `right`, can be more robust in floating-point comparisons.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the lantern positions: O(n log n)
    *   Binary search: O(log(R)), where R is the range of possible d values (2e9 in this case). We iterate 100 times which effectively makes it constant.
    *   The `func` function, which is called inside the binary search, iterates through the lantern positions: O(n)
    *   Overall: O(n log n) + O(100 * n) = O(n log n)

*   **Space Complexity:** O(n) due to the `arr` vector storing the lantern positions.

## 5. Important Code Patterns or Tricks Used

*   **Binary Search Implementation:** The implementation uses the standard binary search template:

    ```cpp
    double left = 0;
    double right = 2e9 + 1;

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2.0;
        if (func(mid, l, arr))
            right = mid;
        else
            left = mid;
    }
    ```

    The choice of `right = mid` and `left = mid` when the condition in `func` changes reflects a minimization problem where we are looking for the smallest value that satisfies the condition.

*   **Precision Setting:** `cout << setprecision(12)` is crucial for getting the correct answer as the problem requires high precision in the output.

*   **Using `ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization improves the input/output performance of the code, especially in competitive programming where time is critical.

## 6. Edge Cases Handled

*   **Empty Street (l = 0):** Although not explicitly handled, the code will work correctly in this case. If `l` is 0, `func` will always return true for any `d` because the condition `coverage >= l` will be immediately satisfied in the initial state where `coverage` is 0.  The binary search will converge to the smallest possible `d`, effectively 0.
*   **No Lanterns (n = 0):** If there are no lanterns, the `arr` vector will be empty.  `func` will always return `false` because the `if (pos - x > coverage)` will never be met because the loop never executes. Thus the binary search moves `left` up to 2e9+1 and outputs that.
*   **Lanterns at the endpoints (0 and l):** The solution works correctly even if the lanterns are exactly at the endpoints of the street.  The sorted order allows for correct extension of coverage.
*   **Large Street Length (l up to 1e9):** The upper bound of the binary search (2e9 + 1) is chosen to accommodate large values of *l*.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <climits>
#include <iomanip>
#include <vector>
using namespace std;

#define int long long

// Problem: vanya
// URL: https://codeforces.com/problemset/problem/492/B
// Difficulty: easy
// Tags:
// Strategy:

bool func(double x, double l, vector<int> &arr) {
    double coverage = 0.0;

    for (int pos : arr) {
        // if this lantern's left bound is beyond current coverage, gap exists
        if (pos - x > coverage)
            return false;

        // extend coverage
        coverage = max(coverage, pos + x);
        if (coverage >= l)
            return true; // already covered till end
    }

    return coverage >= l;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l;
    cin >> n >> l;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // vanya walks late at night along a straight street of length l, lit by n lanterns
    // the coordinate system is such that 0 is the start of the street and l is the end of the street
    // the rth lantern it at the point arr(r)
    // the lantern lights all points of the street that are at a distance of atmost d from it, where d > 0
    // what is the minimum d the lanterns should have to light the whole street
    sort(arr.begin(), arr.end());
    double left = 0;        // can't light the whole street with this
    double right = 2e9 + 1; // can light the whole street with this since the street length can be at most 1e9

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2.0;
        if (func(mid, l, arr))
            right = mid;
        else
            left = mid;
    }

    cout << setprecision(12) << right << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-11 06:45:47*
