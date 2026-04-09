# bookShop

```markdown
## Documentation for Book Shop Problem

This document provides a detailed explanation of the competitive programming solution for the "Book Shop" problem found on CSES (https://cses.fi/problemset/task/1158).

### 1. Problem Description

A bookshop sells *n* different books.  The price and the number of pages for each book are known.  You have decided that the total price of your purchases will be at most *x*.  The task is to determine the maximum number of pages you can buy while staying within the budget *x*.

Formally:

*   Input:
    *   *n*: The number of books.
    *   *x*: The maximum allowed total price (budget).
    *   `price[i]`: The price of the i-th book (0-indexed).
    *   `pages[i]`: The number of pages in the i-th book (0-indexed).

*   Output: The maximum number of pages that can be purchased within the budget *x*.

### 2. Approach Explanation

The problem can be solved using dynamic programming.  We want to find the maximum number of pages we can obtain using books `[0, r]` with a maximum cost of `k`.

We use a 2D dynamic programming approach that's optimized into a 1D approach via rolling arrays.

*   **State:** `dp[k]` represents the maximum number of pages we can buy using books `[0, r]` such that the total cost is at most `k`. We use two 1D arrays (`prev` and `curr`) to represent the `dp` table for the current and previous row of books.

*   **Base Case:**  `prev[k]` is initialized for the first book. If `k >= price[0]`, then `prev[k] = pages[0]`, otherwise `prev[k] = 0`.

*   **Recurrence Relation:** For each book *r* from 1 to *n*-1, and each possible cost *k* from 1 to *x*, we have two options:

    1.  **Don't include the r-th book:**  The maximum number of pages is the same as using books `[0, r-1]` and a maximum cost of *k*, which is `prev[k]`.

    2.  **Include the r-th book:** If `k >= price[r]`, then we can include the r-th book. The maximum number of pages in this case is `prev[k - price[r]] + pages[r]`.

    Therefore, `curr[k] = max(prev[k - price[r]] + pages[r], prev[k])`.  If `k < price[r]`, then we cannot include the r-th book, so `curr[k] = prev[k]`.

*   **Final Answer:** The final answer is stored in `curr[x]`, which represents the maximum number of pages we can buy using all *n* books and a maximum cost of *x*.

### 3. Key Insights and Algorithmic Techniques Used

*   **Dynamic Programming:** The problem exhibits optimal substructure and overlapping subproblems, making dynamic programming an appropriate technique. The optimal solution for buying books with a budget *x* can be constructed from optimal solutions with smaller budgets.

*   **Knapsack Problem Variant:** This problem is a variation of the 0/1 knapsack problem, where we want to maximize the total value (number of pages) while staying within a weight limit (budget).

*   **Space Optimization (Rolling Arrays):**  Instead of storing the entire `n x x` DP table, we only need to keep track of the current row (`curr`) and the previous row (`prev`). This reduces the space complexity from O(n\*x) to O(x). This works because computing the current row only depends on the immediately previous row.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** The outer loop iterates *n* times (number of books), and the inner loop iterates *x* times (maximum cost).  Therefore, the time complexity is O(n\*x).

*   **Space Complexity:** We use two arrays, `prev` and `curr`, each of size *x* + 1. Hence, the space complexity is O(x).

### 5. Important Code Patterns or Tricks Used

*   **Rolling Arrays:**  Using `prev` and `curr` to represent the previous and current rows of the DP table, effectively reducing the space complexity.  The line `prev = curr` is crucial for updating the previous row with the calculated current row.

*   **Initialization:** The `prev` array is initialized with the values for the first book. This provides the base case for the dynamic programming recurrence.

*   **`ios_base::sync_with_stdio(false); cin.tie(nullptr);`:** This optimization improves the input/output performance in C++, especially important for competitive programming.

### 6. Any Edge Cases Handled

*   The code implicitly handles the case where the cost of a book is greater than the current budget `k`.  If `k < price[r]`, the `curr[k]` is simply set to `prev[k]`, indicating that we cannot include the current book.
*   The initialization implicitly handles the case where *x* is small.
*   The use of `long long` (`#define int long long`) prevents integer overflows for large values of `n`, `x`, `price`, and `pages`. This is crucial for passing test cases with large inputs.  It's important to include `int32_t main()` when using this definition.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (1001)
#define MAX_X (int)(1e5 + 1)

// Problem: bookShop
// URL: https://cses.fi/problemset/task/1158
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> price(n);
    vector<int> pages(n);

    for (int i = 0; i < n; i++)
        cin >> price[i];
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    // we are in a bookshop that sells n different books
    // we know the price and number of pages of each book

    // we have decided that the total price of your purchases will be at most x
    // what is the maximum number of pages we can buy?

    // dp[r][k] is the maximum number of pages we can buy using the books [0, r] and atmost k money
    vector<int> prev(x + 1, 0);
    vector<int> curr(x + 1, 0);

    for (int k = price[0]; k <= x; k++)
        prev[k] = pages[0];
    for (int r = 1; r < n; r++) {
        for (int k = price[r]; k <= x; k++)
            curr[k] = max(prev[k - price[r]] + pages[r], prev[k]); // should we even get the current book or not?
        for (int k = 0; k < price[r]; k++)
            curr[k] = prev[k];
        prev = curr;
    }

    cout << curr[x] << endl;
    return 0;
}
```

---
*Documentation generated on 2025-08-25 19:32:37*
