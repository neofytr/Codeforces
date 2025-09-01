#include <bits/stdc++.h>
using namespace std;

#define int long long
int32_t main() {
    // Let G be a graph of n vertices
    // G is a tree
    //  - iff G is connected and acyclic
    //  - iff G is connected and has n - 1 edges
    //  - iff G is acyclic and has n - 1 edges
    //  - iff G has a unique path between any two different vertices
    //  - iff G is maximally acyclic
    //  - iff G is minimally connected

    // Let G be a tree
    // Then, for every node except the root, there is a unique parent

    // ---------------------------------------------------------------
    // Tree DP:
    // ---------------------------------------------------------------
    // Tree DP means defining a DP state on the tree structure,
    // usually something like:
    //   dp[u] = some answer for the subtree rooted at node u
    //
    // Typical transitions:
    //   dp[u] is computed by combining the dp[v] values
    //   of all children v of u.
    //
    // Example:
    //   - Size of subtree rooted at u
    //   - Longest path down from u
    //   - Number of ways to partition the subtree, etc.

    // ---------------------------------------------------------------
    // Why we usually don’t need memoization or a dp[] array:
    // ---------------------------------------------------------------
    // In normal DP, we memoize results because we might reach the
    // same state multiple times via different paths.
    //
    // But in a tree:
    //   - There are no cycles
    //   - Each subtree is disjoint (except for the parent connection)
    //   - Each node is visited exactly once in a DFS
    //
    // Hence, if you do a DFS and compute dp[u] using its children,
    // you never recompute the same dp[u] again.
    //
    // This is why a simple recursive DFS function that "returns"
    // the needed value is often enough — no explicit dp[] or
    // memoization is necessary.
    //
    // Of course, if you need to reuse results later (e.g. rerooting DP),
    // then storing dp[u] in an array is useful. But for many subtree-based
    // problems, just returning the value from DFS works fine.
    return EXIT_SUCCESS;
}
