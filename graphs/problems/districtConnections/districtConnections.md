# districtConnections

```markdown
## Code Documentation: Competitive Programming Solution for District Connections

This document provides a detailed analysis of the provided C++ code, which solves the "District Connections" problem (presumably [Codeforces 1433D](https://codeforces.com/problemset/problem/1433/D)).

### 1. Problem Description (Inferred)

Given `n` districts, each assigned to a gang, determine if it's possible to connect the districts with `n-1` roads such that:

*   Each district is reachable from every other district (the graph is connected).
*   No two districts belonging to the same gang are directly connected by a road.

If it is possible, output "YES" followed by the `n-1` edges (pairs of district indices). Otherwise, output "NO".

### 2. Approach Explanation

The solution aims to construct a spanning tree that avoids directly connecting districts of the same gang. The main idea is as follows:

1.  **Check for a Solution's Existence:** If all districts belong to the same gang, it's impossible to build a valid network, and the answer is "NO".

2.  **Handle the Case where solution Exists:**
    If there are at least two distinct gangs, a valid solution always exists.  The approach is to choose a district from one gang (let's call it the 'primary' gang) and connect it to districts from *all other* gangs. If the primary gang has more than one element, the remaining elements of the primary gang are then connected to an arbitrary element of the second gang.

3.  **Construction:** The `solve()` function implements this strategy.  It first finds a district in a specific gang and connects it to at least one member in other gangs. Then connects the remaining members of the primary gang to one of members of another gang. This ensures connectivity while avoiding direct connections within the same gang.

### 3. Key Insights and Algorithmic Techniques Used

*   **Spanning Tree Construction:** The core idea is to create a spanning tree (a connected graph with `n-1` edges) that fulfills the additional constraint of no direct connections within the same gang.
*   **Greedy Approach:** The solution uses a greedy approach. It picks a representative from one gang and attempts to connect it to members of all other gangs.  The remaining members of the primary gang are then connected to a member from another gang. This works because as long as there is more than one gang, a valid solution exists.
*   **Data Structures:** `unordered_set` is used to efficiently track the distinct gangs present. `unordered_map` stores the members belonging to each gang using gang ID as the key and the list of their district indices as a value.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   The loop to read input and populate the `gangs` and `members` structures takes O(n) time.
    *   The iteration over gangs to print the connections also takes O(n) time in the worst case, considering it might involve iterating through all members of gangs, but on average takes O(n).
    *   The rest of the operations like checking the size of the gangs take constant time.
    *   Overall, the time complexity of `solve()` is O(n).  Since `solve()` is called `t` times, the total time complexity is O(t * n).

*   **Space Complexity:**
    *   The `gangs` set can store at most `n` elements (in the extreme case where each district belongs to a different gang).
    *   The `members` map can store up to `n` elements in the worst case, and each vector within it can hold up to `n` elements.
    *   Overall, the space complexity is O(n).

### 5. Important Code Patterns or Tricks Used

*   **Using `unordered_set` for Distinct Elements:** `unordered_set` is efficient for checking the number of distinct gangs.
*   **Using `unordered_map` for Grouping:** `unordered_map` makes it easy to group districts by their gang affiliation.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: This is a standard optimization technique in C++ competitive programming to reduce the overhead of input/output operations.  It disables synchronization between the C and C++ standard streams and unties `cin` from `cout`, potentially leading to significant performance improvements, particularly when dealing with large input/output.
*   **`#define int long long`**: Defining int as long long is a common practice to avoid integer overflow issues in competitive programming.  It trades off memory usage for a wider range of representable values.

### 6. Edge Cases Handled

*   **Single Gang:** The code explicitly checks if all districts belong to the same gang (`gangs.size() < 2`). If they do, it correctly outputs "NO" because it's impossible to create a valid network. This is the critical edge case.
*   **Multiple Gangs:** For the case where there are multiple gangs, the solution creates edges between members of the first gang and at least one member of other gangs.
*   **Empty Input:** The code implicitly handles the case of `n=1` correctly, because if there are less than 2 gangs, it just print "NO" and exits.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

// Problem: districtConnections
// URL: https://codeforces.com/problemset/problem/1433/D
// Difficulty: medium
// Tags:
// Strategy:

void solve() {
    int n;
    cin >> n;

    unordered_set<int> gangs;
    unordered_map<int, vector<int>> members;

    int gang;
    for (int index = 1; index <= n; index++) {
        cin >> gang;
        gangs.insert(gang);
        members[gang].push_back(index);
    }

    if (gangs.size() < 2) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    int first = *gangs.begin();
    for (int i = 0; i < members[first].size(); i++) {
        if (!i) {
            // connect this to all other gangs
            for (int gng : gangs) {
                if (gng != first) {
                    for (int v : members[gng]) {
                        cout << members[first][i] << " " << v << endl;
                    }
                }
            }
        } else {
            int second = *(++gangs.begin());
            int elt = members[second][0];
            cout << members[first][i] << " " << elt << endl;
        }
    }

    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

---
*Documentation generated on 2025-08-16 10:30:44*
