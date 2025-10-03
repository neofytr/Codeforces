# commonDiv

```markdown
## Common Divisor Problem Documentation

This document provides a comprehensive analysis of the provided C++ solution for the "Common Divisor" problem from CSES (https://cses.fi/problemset/task/1081).

### 1. Problem Description

The problem asks to find the largest common divisor (GCD) of a given set of `n` integers.  More formally: given an array `A` of `n` integers, find the largest integer `d` such that `d` divides at least two elements of `A`.

### 2. Approach Explanation

The solution employs a frequency-based approach combined with a reverse iteration to find the largest common divisor. The core idea is:

1. **Frequency Counting:**  Create a frequency array `freq` where `freq[i]` stores the number of times the integer `i` appears in the input array `A`.  The index of the `freq` array represents a potential divisor.

2. **Reverse Iteration:** Iterate from the maximum possible divisor (`MAX`) down to 1. For each potential divisor `r`, count how many numbers in the input array are divisible by `r`. This is done by iterating through multiples of `r` within the range [r, MAX] and summing their frequencies in the `freq` array.

3. **GCD Check:** If the count of numbers divisible by `r` is greater than or equal to 2, it means that `r` is a common divisor of at least two numbers in the input array.  Since we are iterating in reverse order (from largest to smallest), the first such `r` we encounter will be the largest common divisor.  We print this value and terminate.

### 3. Key Insights and Algorithmic Techniques Used

*   **Frequency Array:**  Using a frequency array `freq` is crucial for efficiently counting the occurrences of each number.  This avoids the need to repeatedly iterate through the original input array.
*   **Reverse Iteration and Early Exit:**  Iterating from `MAX` down to 1 allows us to find the *largest* common divisor as soon as a valid one is encountered. The `return 0;` statement ensures that the search terminates immediately upon finding the solution, improving efficiency.
*   **Divisibility Check using Multiples:**  The divisibility check is performed by iterating through multiples of the potential divisor `r` (`j = r; j <= MAX; j += r`). This is a common and efficient way to identify all numbers divisible by a given number within a specific range.  It avoids costly modulo operations.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Frequency counting: O(n), where n is the number of input integers.
    *   Reverse Iteration: O(MAX \* (Harmonic Number of MAX)). More precisely, the inner loop iterates over the multiples of 'r' up to MAX.  This is similar to the number of divisors function. Thus, the complexity of the nested loop is approximately O(MAX \* log(MAX)). Since MAX is defined as a constant (1000000), this can be considered linear in the size of the input numbers.

    Overall, the time complexity is dominated by O(MAX \* log(MAX)).

*   **Space Complexity:**
    *   `freq` array: O(MAX). Since MAX is a constant (1000000), the space complexity can be considered constant.
    *   Other variables: O(1)

    Overall, the space complexity is O(MAX), dominated by the `freq` array.

### 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This macro is commonly used in competitive programming to avoid integer overflow issues, especially when dealing with large numbers. It essentially makes the `int` type a `long long int`, providing a larger range of values.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** These lines are used to optimize input/output operations by disabling synchronization between the C and C++ standard input/output streams and un-tying `cin` from `cout`. This can significantly speed up the program, especially when dealing with large inputs.

### 6. Edge Cases Handled

*   **MAX Value:** The code assumes that all input integers are within the range `[1, MAX]`. It is important that the `MAX` value is chosen appropriately based on the problem constraints to ensure that the `freq` array is large enough to accommodate all possible input values.  If a number larger than MAX is present, it will not be tracked, potentially leading to an incorrect result if it influences the answer.
*   **No Common Divisor:** The code implicitly handles the case where there is no common divisor greater than 1 by correctly iterating to '1'.

**Potential Improvements:**

*   **Dynamic MAX:**  Instead of a fixed `MAX`, the solution could dynamically determine the maximum value in the input array and use that as the `MAX` for the frequency array. This would save memory if the input numbers are significantly smaller than the predefined `MAX`. However, this would involve an additional pass through the input array.
*   **GCD Calculation Optimization:** While this approach solves the problem efficiently given the constraints, an alternative approach would be to compute GCDs directly.  However, calculating GCDs of all possible pairs would lead to an O(n^2 log(MAX)) time complexity, which is likely to be slower than the current solution for large `n`.

This documentation provides a comprehensive understanding of the given C++ solution, including its underlying algorithm, complexity analysis, and key implementation details. It should serve as a valuable resource for learning and understanding the code.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: commonDiv
// URL: https://cses.fi/problemset/task/1081
// Difficulty: hard
// Tags: 
// Strategy: 

#include <bits/stdc++.h>
using namespace std;

#define MAX (1000000)

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    int val;
    vector<int> freq(MAX + 1, 0);
    for (int r = 1; r <= n; r++) {
        cin >> val;
        freq[val]++;
    }

    // divisor -> count
    int maxi; 
    for (int r = MAX; r >= 1; r--) {
        int cnt = 0;
        for (int j = r; j <= MAX; j += r) 
            cnt += freq[j];
        if (cnt >= 2) {
            cout << r << endl;
            return 0;
        }
    }
            
    cout << maxi << endl;
    return 0;
}
```

---
*Documentation generated on 2025-10-03 15:53:02*
