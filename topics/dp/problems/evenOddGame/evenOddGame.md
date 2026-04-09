# evenOddGame

```markdown
# Code Documentation: Even-Odd Game

This document provides a comprehensive analysis of the provided C++ code, which solves the "Even-Odd Game" problem from Codeforces (Problem 1472D).

## 1. Problem Description

The "Even-Odd Game" (available at [https://codeforces.com/problemset/problem/1472/D](https://codeforces.com/problemset/problem/1472/D)) presents a game between Alice and Bob. Given an array `a` of `n` integers, they take turns picking elements from the array. Alice always goes first.

- On Alice's turn, she can only pick an even number. She gets points equal to the chosen even number.
- On Bob's turn, he can only pick an odd number. He gets points equal to the chosen odd number.
- After a player picks a number, it's removed from the array.

Both players play optimally to maximize their own score. The goal is to determine who wins the game ("Alice", "Bob", or "Tie").

## 2. Approach Explanation

The solution employs a greedy approach based on the observation that sorting the array in descending order and then iterating through the array to simulate the turns provides the optimal strategy for both players. The main steps are as follows:

1. **Input:** Read the number of test cases `t`, then for each test case, read the array size `n` and the array elements `a`.
2. **Sort:** Sort the array `a` in descending order.  This is crucial because the players want to pick the largest even (for Alice) and odd (for Bob) numbers whenever possible.
3. **Simulate Turns:** Iterate through the sorted array `a`.
   - If the current index `i` is even (Alice's turn), and the current number `a[i]` is even, add `a[i]` to Alice's score.
   - If the current index `i` is odd (Bob's turn), and the current number `a[i]` is odd, add `a[i]` to Bob's score.
4. **Determine Winner:** After the loop, compare Alice's score and Bob's score to determine the winner:
   - If Alice's score > Bob's score, output "Alice".
   - If Bob's score > Alice's score, output "Bob".
   - Otherwise, output "Tie".

## 3. Key Insights and Algorithmic Techniques Used

*   **Greedy Strategy:** The core idea is that both players want to pick the largest numbers possible that fit their criteria (even for Alice, odd for Bob). Therefore, sorting the array in descending order and then simulating the turns yields the optimal result.  Picking the largest possible value at each step maximizes the total score when constrained by the parity requirement.
*   **Sorting:** Sorting the array in descending order is a fundamental step to enable the greedy strategy. `sort(a.rbegin(), a.rend())` is used for this purpose.
*   **Bitwise Operations:** The code uses bitwise AND (`&`) to efficiently determine if a number is even or odd. `!(a[i] & 1)` checks if `a[i]` is even, and `a[i] & 1` checks if `a[i]` is odd.  The expression `i & 1` efficiently checks if the index `i` is odd.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sorting the array takes O(n log n) time.
    *   The iteration through the array takes O(n) time.
    *   The remaining operations (input, output, comparisons) take O(1) time per test case.
    *   Since the code iterates over `t` test cases, the overall time complexity is O(t * n log n).

*   **Space Complexity:**
    *   The array `a` stores `n` integers, so it takes O(n) space.
    *   Other variables take O(1) space.
    *   Therefore, the overall space complexity is O(n).

## 5. Important Code Patterns or Tricks Used

*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a common optimization technique in C++ competitive programming to speed up input/output by disabling synchronization between the C and C++ standard input/output streams.
*   **`#define int long long`**:  This macro is used to change the default `int` data type to `long long`, which helps prevent integer overflow issues, especially in problems where numbers can become large.  This is a common practice in competitive programming for problems where the inputs can exceed the range of a 32-bit integer.
*   **`sort(a.rbegin(), a.rend())`**: Sorts the vector `a` in descending order. `rbegin()` and `rend()` provide reverse iterators.
*   **Bitwise Operators:** Using `& 1` is a very efficient way to check parity.

## 6. Edge Cases Handled

*   **Tie Condition:** The code explicitly handles the case where Alice's score and Bob's score are equal, outputting "Tie".
*   **Empty array** The constraints specified `n` is a positive integer, meaning `n>=1`. Thus, an empty array case does not exist.
*   **Zero score** The code correctly handles cases where players end up with a zero score because no even or odd numbers were available for them to choose at their turn.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: evenOddGame
// URL: https://codeforces.com/problemset/problem/1472/D
// Difficulty: medium
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        // sort descending
        sort(a.rbegin(), a.rend());

        int alice = 0, bob = 0;
        for (int i = 0; i < n; i++) {
            if (!(i & 1)) { // Alice's turn
                if (!(a[i] & 1))
                    alice += a[i];
            } else { // Bob's turn
                if (a[i] & 1)
                    bob += a[i];
            }
        }

        if (alice > bob)
            cout << "Alice\n";
        else if (bob > alice)
            cout << "Bob\n";
        else
            cout << "Tie\n";
    }
    return 0;
}

```

---
*Documentation generated on 2025-08-30 09:08:08*
