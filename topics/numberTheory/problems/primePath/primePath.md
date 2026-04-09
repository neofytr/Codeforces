# primePath

```markdown
# Competitive Programming Solution Documentation: Prime Path

This document provides a detailed explanation of the provided C++ solution for the "Prime Path" problem.

## 1. Problem Description (Inferred from Code and Comments)

The problem, accessible at [https://open.kattis.com/problems/primepath](https://open.kattis.com/problems/primepath), requires finding the minimum number of steps to transform a four-digit prime number `a` into another four-digit prime number `b`. In each step, we can change only one digit of the current prime number, and the resulting number must also be a four-digit prime.  If it is not possible to convert `a` to `b` return `Impossible`. The problem involves several test cases.

## 2. Approach Explanation

The solution employs Breadth-First Search (BFS) to find the shortest path between the starting prime number `a` and the target prime number `b`.

1.  **Prime Number Generation:** A sieve of Eratosthenes is used to precompute a boolean array `primes` indicating whether a number is prime within a range of 0 to `MAX` (defined as 10000).

2.  **BFS Implementation:**
    *   A `dist` array is used to store the minimum distance (number of steps) from the starting node to each prime number. Initially, all distances are set to -1, meaning unvisited.
    *   A queue `q` is used for the BFS traversal.
    *   The starting prime number `a` is pushed into the queue, and its distance is set to 0.
    *   The algorithm iteratively processes nodes from the queue:
        *   For the current prime number `cur`, the code iterates through each of its four digits.
        *   For each digit position, it tries replacing the current digit with all digits from '0' to '9'.
        *   If the resulting number `nxt` is a four-digit prime number (i.e., greater than or equal to 1000 and marked as prime in the `primes` array) and has not been visited yet (i.e., `dist[nxt]` is -1), its distance is updated to `dist[cur] + 1`, and it is enqueued.
        * If `nxt` is equal to target `b`, we return the distance to `nxt`.
        * After processing all possible single-digit changes, the original digit is restored.
    *   If the target prime number `b` is reached, the function returns the distance to `b`.
    *   If the queue becomes empty before reaching `b`, it means there is no path from `a` to `b`, so the function returns -1.

## 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):** BFS is the core algorithm used to find the shortest path in an unweighted graph, which is suitable for this problem since each transformation has a cost of 1.
*   **Sieve of Eratosthenes:**  An efficient algorithm for generating prime numbers up to a specified limit.  It precomputes a boolean array indicating which numbers are prime, which is used to quickly check if a candidate number is prime during the BFS.
*   **String Manipulation:** The solution cleverly uses string manipulation to generate neighboring prime numbers.  Converting integers to strings makes it easier to modify individual digits.
*   **State Space Representation:** The set of four-digit prime numbers represents the state space of the search problem.  Each valid transformation between prime numbers represents an edge in the implicit graph being explored by the BFS.
*   **Implicit Graph:**  The solution implicitly creates a graph where nodes are four-digit prime numbers, and edges connect numbers that differ by one digit while still being prime. The BFS algorithm explores this graph.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   Sieve of Eratosthenes: O(N log log N), where N = `MAX`.
    *   BFS: In the worst case, BFS might visit all four-digit prime numbers (less than 10000). For each node, the code iterates through the 4 digits and tries all 10 possible replacements, so for each node O(4 * 10) operations.
    *   Total:  O(N log log N) + O(V * E') where V is the number of primes and E' is the number of possible transformations from each prime. V is approximately `MAX / ln(MAX)` which is roughly 1000. E' for each prime is fixed (4 digits to change, each digit can change to 10, checking takes constant time).
    *   The overall time complexity is dominated by O(N log log N) + O(number of primes * 40), so it can be considered close to O(N log log N).  Since MAX is 10000, it is reasonable.
*   **Space Complexity:**
    *   `primes` array: O(N) = O(10000)
    *   `dist` array: O(N) = O(10000)
    *   Queue: In the worst case, the queue might contain all four-digit prime numbers, which is O(N).
    *   Total: O(N) = O(10000)

## 5. Important Code Patterns or Tricks Used

*   **`#define int long long`:** This is a common trick in competitive programming to prevent integer overflow issues, especially when dealing with large numbers of calculations.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization is used to speed up input/output operations by disabling synchronization between the C and C++ standard input/output streams.
*   **String Conversion and Manipulation:** Using `to_string` and `stoi` to efficiently modify digits of the prime numbers.
*   **Clear Initialization:** The `dist` array is initialized to -1 to easily track visited nodes in the BFS.
*   **Restoring Original State:** The code ensures that the original digit is restored after exploring potential transformations, preventing unintended side effects.

## 6. Edge Cases Handled

*   **`start == target`:** The code explicitly checks if the starting and target prime numbers are the same and returns 0 in that case.
*   **`Impossible`:** The BFS returns -1 if no path exists from the starting prime number to the target prime number, which is then handled to output "Impossible".
*   **Four-digit number Check (`nxt >= 1000`):** The code only considers prime numbers that are four digits long.
*   **Duplicate Digits:** The code explicitly ensures that the new digit is different from the original digit (`if (d == orig) continue;`), avoiding unnecessary computations.


## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 10000

// Problem: primePath
// URL: https://open.kattis.com/problems/primepath
// Difficulty: hard
// Tags: 
// Strategy: 

vector<bool> sieve() {
    vector<bool> primes(MAX, true);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i < MAX; i++) {
        if (primes[i]) {
            for (int j = i * i; j < MAX; j += i)
                primes[j] = false;
        }
    }
    return primes;
}

int bfs(int start, int target, const vector<bool> &primes) {
    if (start == target) return 0;

    vector<int> dist(MAX, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        string s = to_string(cur);

        for (int pos = 0; pos < 4; pos++) {
            char orig = s[pos];
            for (char d = '0'; d <= '9'; d++) {
                if (d == orig) continue;

                s[pos] = d;
                int nxt = stoi(s);

                if (nxt >= 1000 && primes[nxt] && dist[nxt] == -1) {
                    dist[nxt] = dist[cur] + 1;
                    if (nxt == target) return dist[nxt];
                    q.push(nxt);
                }
            }
            s[pos] = orig; // restore
        }
    }

    return -1; // impossible
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto primes = sieve();

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int ans = bfs(a, b, primes);
        if (ans == -1)
            cout << "Impossible\n";
        else
            cout << ans << "\n";
    }
}
```

---
*Documentation generated on 2025-10-01 18:39:21*
