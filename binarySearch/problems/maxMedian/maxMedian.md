# maxMedian

```markdown
# Competitive Programming Solution Documentation

## 1. Problem Description

The problem, as indicated by the comment `Problem: maxMedian` and the URL `https://codeforces.com/contest/1201/problem/C`, is Codeforces problem 1201C, which asks to maximize the median of an odd-sized array using at most `k` operations.  An operation consists of incrementing a chosen element of the array by 1. The median of an odd-sized array is the middle element after sorting the array in non-decreasing order.

## 2. Approach Explanation

The solution employs a binary search strategy to find the maximum possible median value. The core idea is that if we *can* make the median equal to `x` using at most `k` operations, then we *can* also make it equal to any value less than `x`. This property makes binary search applicable.

The `func(int x, int k, vector<int> &arr, vector<int> &prefix)` function checks if it's possible to make the median of `arr` equal to `x` using at most `k` operations. It does this by calculating the minimum number of operations required.  It finds the elements from the initial median to the largest element less than or equal to x. Then, it computes how many steps are required to raise all those elements to `x`. If the required steps exceed k, it returns false; otherwise, true.

In the main function, the code first sorts the array. It then creates a prefix sum array to facilitate quick calculation of the sum of elements within a given range. The binary search is conducted between a lower bound (the initial median) and an upper bound that is dynamically increased until the `func` function returns false. Finally the left value, representing the maximum possible median, is printed.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search on Answer:** The most crucial insight is recognizing that the problem can be solved using binary search on the possible values of the median. This significantly reduces the search space.
*   **Prefix Sums:**  The prefix sum array (`prefix`) allows for the efficient calculation of the sum of a contiguous sub-array. This is used to quickly determine the total increment needed to raise the elements between the initial median and `x` (or the largest element not greater than `x`) to `x`. Without prefix sums, calculating this sum would take O(n) time within the `func` function, impacting the overall efficiency.
*   **Monotonicity:** Binary Search relies on the monotonic property of the problem, namely that if a median value *x* can be achieved within *k* operations, then all median values less than *x* can be achieved too.  If we *cannot* make the median *x* within *k* operations, then we cannot make any value greater than *x*.
*   **Greedy Approach (Implicit):** The `func` function implicitly uses a greedy approach. It focuses on raising the elements *immediately to the right* of the original median to the target median `x`. This is optimal because incrementing any element *before* the original median will not directly contribute to increasing the median's value.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the array: O(n log n)
    *   Creating the prefix sum array: O(n)
    *   Binary Search: O(log M), where M is the range of possible median values.
    *   The `func` function takes O(log n) because of another binary search inside to find the largest element in array less than or equal to x.
    *   Therefore the entire complexity will be O(n log n + log(M) * log(n) ) which is approximately O(n log n + log(M) * log(n)), where M is the maximum possible value that could be taken by median.
    Since n is often small compared to M this term often dominates, but both terms are important. If the maximum input value is very large, the second term will become more prominent. If M is bounded by a polynomial in *n*, we can approximate it to O(n log n + log^2 n).

*   **Space Complexity:**
    *   `arr`: O(n)
    *   `prefix`: O(n)
    *   Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **Binary Search Implementation:** The code uses the `while (right != left + 1)` loop structure, which is a standard way to implement binary search. This structure is advantageous because it prevents infinite loops and ensures that the search terminates when the left and right pointers are adjacent.
*   **Prefix Sum Calculation:** The prefix sum calculation is a common pattern for optimizing range sum queries.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This is a standard optimization technique in C++ competitive programming to speed up input/output by disabling synchronization between the C and C++ standard input/output streams.

## 6. Edge Cases Handled

*   **`left < n / 2` in `func`:** This condition checks if the number of elements less than or equal to `x` is less than the median index. If this is the case, it's impossible to make `x` the median because the elements to the left of the current median cannot be sufficiently increased to shift the median to the right.
*   **Upper Bound in Binary Search:** The code cleverly finds an upper bound for the binary search by repeatedly doubling `x` until `func` returns false. This ensures that the binary search range is adequately large.  The `if (x <= 0) x++;` statement is probably a precaution against potential issues if the initial median is 0 or negative, preventing infinite loops when doubling the value. In the constraints given it should never happen but it is included in the code as a safety measure.
*   **Integer Overflow:** Using `long long` for all integer variables mitigates potential integer overflow issues, especially when performing calculations with large values of `k` and array elements.
*   **min function in line 25** The min function is used to prevent out-of-bounds access if *left* is beyond n-1. This can happen if there are very high values in the input vector, making all values less than or equal to *x*.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: maxMedian
// URL: https://codeforces.com/contest/1201/problem/C
// Difficulty: hard
// Tags:
// Strategy:

bool func(int x, int k, vector<int> &arr, vector<int> &prefix) {
    // we want to see if we can make the median x using atmost k operations
    int n = (int)arr.size();
    int currMedian = arr[n / 2];
    // x is the new median
    // we will find the largest element in the array such that its <= x; say its y
    // we have to increase all the elements from currMedian to y to be equal to atleast x
    // if it can be done in k operations, we return true, or we return false

    int left = -1;
    int right = n;
    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= x)
            left = mid;
        else
            right = mid;
    }

    if (left < n / 2) {
        // we can never make the median x
        return false;
    }

    int count = (min(n - 1, left) - (n / 2) + 1) * x - (prefix[min(n - 1, left) + 1] - prefix[n / 2]);

    return count <= k;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    // n is always odd
    // k is the maximum number of operations we can make

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we have an array of n integers, with n being odd
    // we can perform the following operation at most k times
    // choose one of the elements from the array (say a) and replace it with a + 1

    // we want to make the median of the array as large as possible using at most k such operations
    // the median of an odd-sized array is the middle element after the array is sorted in non-decreasing order

    // if we cannot make the median x after atmost k operations, we cannot make it x + 1
    // we can binary search on answer then

    sort(arr.begin(), arr.end());
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }

    int left = arr[n / 2]; // we can make the median this using atmost k operations

    // get an upper bound
    int x = left;
    while (func(x, k, arr, prefix)) {
        if (x <= 0)
            x++;
        else
            x *= 2;
    }
    int right = x + 1;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (func(mid, k, arr, prefix))
            left = mid;
        else
            right = mid;
    }

    cout << left << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-10 15:52:36*
