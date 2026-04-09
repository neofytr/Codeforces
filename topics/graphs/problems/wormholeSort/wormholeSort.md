# wormholeSort

```markdown
# Wormhole Sort Problem Documentation

This document provides a comprehensive analysis of the provided C++ solution for the "Wormhole Sort" problem, available on the USACO website ([https://usaco.org/index.php?page=viewproblem2](https://usaco.org/index.php?page=viewproblem2)).

## 1. Problem Description

The "Wormhole Sort" problem involves `n` cows located at distinct positions from 1 to `n`. The goal is to sort the cows such that the cow `i` is at position `i`.  We are given `m` wormholes, each connecting two distinct positions and having a specific "strength" (weight). A cow can travel through a wormhole if the wormhole's strength is at least some value `x`. The problem asks for the maximum possible value of `x` such that all cows can be sorted to their correct positions using only wormholes with strength greater than or equal to `x`. If it's impossible to sort the cows even with all wormholes, the output should be -1.

## 2. Approach Explanation

The core idea is to use binary search to find the maximum possible strength `x`. For a given value of `x`, we can check if it is possible to sort the cows by considering only the wormholes with strength greater than or equal to `x`. The `can()` function implements this check.

Inside the `can()` function, a Disjoint Set Union (DSU) data structure is used to determine the connected components formed by the wormholes with strengths at least `x`. If, for every cow `i`, its initial position `location[i]` and its correct position `i` are in the same connected component, then it means the cow can reach its sorted position through the wormholes of strength at least `x`. In this case, we can sort the cows with the given `x`.

The binary search iteratively narrows down the range of possible `x` values until the maximum possible `x` is found.

## 3. Key Insights and Algorithmic Techniques Used

*   **Binary Search:** The problem's objective is to find the maximum value that satisfies a certain condition. Binary search is a powerful technique when dealing with monotonic search spaces, which is the case here (if it is possible to sort cows with strength `x`, it is also possible to sort them with any strength `y < x`).
*   **Disjoint Set Union (DSU):** DSU (also known as Union-Find) is crucial for efficiently determining connected components. In this problem, we use it to group positions connected by wormholes of sufficient strength.  The key operations are `unite()` (merging two sets) and `connected()` (checking if two elements are in the same set).
*   **Connected Components:** The ability to determine connected components using DSU allows us to check if a cow can reach its target position. If the initial and target positions are in the same connected component, then it's possible.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   DSU operations (unite and connected) take almost constant time with path compression and union by size (amortized O(α(n)), where α(n) is the inverse Ackermann function, which grows extremely slowly and can be considered O(1) for practical inputs).
    *   The `can()` function iterates through the edges and performs DSU operations.  So, the time complexity of `can()` is O(m).
    *   Binary search takes O(log(1e9 + 1)) iterations.
    *   Therefore, the overall time complexity is O(m * log(1e9)), since the `can` function is called O(log(1e9)) times by the binary search.

*   **Space Complexity:**
    *   The `disjointSetUnion` class stores `parent` and `size` vectors of size `n`, which takes O(n) space.
    *   The `edges` vector stores `m` edges, taking O(m) space.
    *   The `location` vector stores `n` locations, which takes O(n) space.

    *   Thus, the overall space complexity is O(n + m).

## 5. Important Code Patterns or Tricks Used

*   **Path Compression and Union by Size (or Rank):**  The DSU implementation includes path compression and union by size to improve efficiency. Path compression flattens the tree structure during the `root()` operation, and union by size attaches the smaller tree to the larger tree during the `unite()` operation. These optimizations make the DSU operations effectively constant time.
*   **Binary Search Implementation:** The binary search is implemented using a `while(right != left + 1)` loop, ensuring that the search space is narrowed down correctly.
*   **Convenient Data Structures:** The use of `pair<pair<int, int>, int>` to store edges and their weights is concise and makes it easy to iterate through the edges and access their properties.

## 6. Any Edge Cases Handled

*   **Impossible Sorting:** The code handles the case where it is impossible to sort the cows, even with all wormholes (i.e., when `left == 1e9`). In this scenario, it outputs -1, as required by the problem statement.
*   **Zero wormholes:** The code works correctly if `m` is 0. In this case, the `can` function will essentially check if the cows are already sorted. If any cow is out of place, the code handles this correctly.
*   **All wormholes are used to sort:** The code calculates the *maximum* possible wormhole strength. This means when all wormholes are used the correct answer is returned.
```

## Original Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: wormholeSort
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: hard
// Tags: 
// Strategy: 

class disjointSetUnion {
private:
    vector<int> parent;
    vector<int> size;
    int nodes;

    int root(int x) {
        int y = x;
        while(x != parent[x])
            x = parent[x];

        int tmp;
        while(y != parent[y])
            tmp = parent[y], parent[y] = x, y = tmp;
        return x;
    }
public:
    disjointSetUnion(int n) {
        nodes = n;
        parent.resize(n);
        size.resize(n);

        for (int r = 0; r < n; r++)
            parent[r] = r, size[r] = 1;
    }

    void unite(int x, int y) {
        int rootX = root(x), rootY = root(y);
        if (rootX == rootY)
            return;

        int sizeX = size[rootX];
        int sizeY = size[rootY];

        if (sizeX >= sizeY) {
            // attach y's root to x's root
            parent[rootY] = rootX;
            size[rootX] += sizeY;
        } else {
            parent[rootX] = rootY;
            size[rootY] += sizeX;
        }
    }

    bool connected(int x, int y) {
        return root(x) == root(y); 
    }
};

bool can(int sz, vector<int> &location, vector<pair<pair<int, int>, int>> &edges) {
    // can we sort the cows by taking only those edges which have weights >= sz?

    int k = location.size();
    disjointSetUnion dsu(k);

    for (auto &[v, w] : edges)
        if (w >= sz)
            dsu.unite(v.first, v.second);

    for (int i = 1; i <= k - 1; i++) {
        if (!dsu.connected(i, location[i]))
            return false;
    }
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;

    vector<pair<pair<int, int>, int>> edges;
    vector<int> location(n + 1); // cow to initial location
    for (int cow = 1; cow <= n; cow++)
        cin >> location[cow];

    int a, b, w;
    while(m--)
        cin >> a >> b >> w, edges.push_back({{a, b}, w});

    int left = 0;
    int right = 1e9 + 1;

    while(right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid, location, edges))
            left = mid;
        else 
            right = mid;
    }

    if (left == 1e9)
        cout << -1 << endl;
    else 
        cout << left << endl;
    return 0;
}
```

---
*Documentation generated on 2025-10-15 12:16:50*
