# equation

```markdown
# Competitive Programming Solution Documentation

## 1. Problem Description

The problem, titled "equation" and found at [https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E](https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E), requires finding a real number `x` such that `x^2 + sqrt(x) = c`, where `c` is a given real number. The comments specify that `c >= 1`. Therefore, we are essentially solving an equation involving a quadratic term and a square root.

## 2. Approach Explanation

The solution employs a binary search algorithm to find the value of `x`.  The code defines a function `f(x) = x^2 + sqrt(x)`.  The key observation is that `f(x)` is a strictly increasing function for `x >= 0`. This property allows us to use binary search efficiently.

The binary search iteratively narrows down the range in which `x` could lie. It maintains two pointers, `left` and `right`, representing the lower and upper bounds of the search space, respectively. The code sets `left = 0` and `right = 1e12`. These initial bounds are chosen based on the problem constraints and the fact that we are searching for a real number `x >= 0`. The upper bound can be estimated by considering the case where x^2 is approximately equal to c. If c is at most 10^18, then x would be at most 10^9. The choice of 10^12 provides an ample margin.

In each iteration, the code calculates the midpoint `mid = left + (right - left) / 2`. It then evaluates `f(mid) = mid * mid + sqrt(mid)`. If `f(mid) >= c`, it means that the desired value of `x` must be less than or equal to `mid`, so the upper bound `right` is updated to `mid`. Otherwise, if `f(mid) < c`, it means that the desired value of `x` must be greater than `mid`, so the lower bound `left` is updated to `mid`.

The binary search continues for a fixed number of iterations (100 in this case) to achieve a sufficient level of precision. Finally, the code outputs the value of `right`, which represents the approximate solution for `x`.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search:** The core algorithm used is binary search. The function `f(x) = x^2 + sqrt(x)` is monotonically increasing for `x >= 0`. This ensures that binary search can be effectively applied to find the root.
*   **Monotonic Function:** Recognizing the monotonic nature of the function `f(x)` is crucial for using binary search. A monotonic function (either strictly increasing or strictly decreasing) guarantees that the search space can be halved in each iteration, leading to logarithmic time complexity.
*   **Numerical Precision:** The code uses a fixed number of iterations (100) in the binary search loop to achieve the required precision.  This is a common technique in numerical problems where it's difficult to determine an exact termination condition.  Setting the precision to 16 decimal places with `setprecision(16)` ensures a sufficiently accurate answer.
*   **Choosing Initial Bounds:** Selecting appropriate initial values for `left` and `right` is important for the correctness of the binary search. `left` is initialized to 0, as `x` cannot be negative. `right` is initialized to `1e12`, a large value that is guaranteed to be greater than the solution.
*   **Avoiding Integer Overflow:** The calculation `left + (right - left) / 2` is used instead of `(left + right) / 2` to avoid potential integer overflow issues when `left` and `right` are large.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** The time complexity of the solution is dominated by the binary search algorithm. The binary search loop runs for a fixed number of iterations (100). Therefore, the time complexity is O(log(range)), where `range` is the initial difference between the `right` and `left` bounds. However, because we have a fixed number of iterations, we can consider the time complexity to be O(1). Specifically, it's O(number of iterations), which is O(100) = O(1). The square root calculation `sqrt(mid)` takes constant time.
*   **Space Complexity:** The space complexity of the solution is O(1), as it uses only a constant amount of extra space to store variables such as `c`, `left`, `right`, and `mid`.

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This optimization is commonly used in competitive programming to disable synchronization between the standard input/output streams (stdio) and the C++ streams (iostream). This can significantly improve the input/output performance of the program, especially when dealing with large amounts of data.
*   **`setprecision(16)`:** This manipulator is used to set the precision of the output stream to 16 decimal places. This ensures that the solution is printed with sufficient accuracy, as required by the problem.
*   **Binary Search Implementation:** The implementation of the binary search algorithm is a standard approach that ensures correctness and efficiency. The use of `left + (right - left) / 2` to calculate the midpoint prevents potential integer overflow issues.
*   **Fixed Iteration Count:** Using a fixed iteration count instead of a delta-based termination condition is beneficial when calculating square roots and similar operations, because you may need to execute the operation more times until it results in the appropriate precision.

## 6. Any Edge Cases Handled

*   **Non-Negative x:** The code implicitly handles the edge case where `x` must be non-negative by initializing `left` to 0.  The problem statement does not explicitly state `x` must be non-negative, but since the equation includes `sqrt(x)`, `x` cannot be negative and this is the underlying reason.
*   **c >= 1:** The problem comment indicates that `c >= 1`. This implies that the solution `x` will always be greater than or equal to 0, preventing issues with the square root calculation. If c was less than 1, there'd be more restrictions on finding an initial value of right, which could get close to 0, increasing the run time in order to compute the value of x closer to 0. The initial bound of `right` ensures the search converges within the allocated iterations.
*   **Floating Point Errors:** The choice of 100 iterations accounts for and minimizes floating point precision errors, which can affect convergence. Using double-precision floating point numbers also helps.


## Original Code
```cpp
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

#define int long long

// Problem: equation
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double c;
    cin >> c;

    // we are to find an x such that x^2 + root(x) = c
    // such an x must be >= 0 since c is a real number
    // also x != 0 since c >= 1
    // let f(x) = x^2 + root(x) for x >= 0
    // f is a strictly increasing function
    // we find a point y such that f(r) >= c for all r >= y and f(r) < c for all r < y

    double left = 0;     // not possible
    double right = 1e12; // possible

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2;
        if (mid * mid + sqrt(mid) >= c)
            right = mid;
        else
            left = mid;
    }

    cout << setprecision(16) << right << endl;

    return 0;
}
```

---
*Documentation generated on 2025-08-08 09:22:47*
