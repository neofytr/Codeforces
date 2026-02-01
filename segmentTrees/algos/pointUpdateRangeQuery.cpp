#include <bits/stdc++.h>
using namespace std;

/*
    Generic Segment Tree (Range Query + Point Update)
    -------------------------------------------------

    This implementation maintains a 1-indexed segment tree over an
    array A[1..n]. It supports efficient range queries and point
    updates using a user-defined operation.

    ------------------------------------------------------------
    Supported Operations
    ------------------------------------------------------------

    1) query(l, r):
       Computes and returns:
           A[l] op A[l+1] op ... op A[r]

    2) set(idx, val):
       Updates the array by performing:
           A[idx] = val

    ------------------------------------------------------------
    Algebraic Requirements on the Operation
    ------------------------------------------------------------

    The binary operation `combine` must satisfy:

    1) ASSOCIATIVITY:
           (a op b) op c = a op (b op c)

       This property allows the segment tree to merge results from
       subsegments without ambiguity.

    2) IDENTITY ELEMENT:
       There must exist an element `identity` such that:
           a op identity = identity op a = a

       The identity element is required to:
       - Represent empty or non-overlapping query ranges
       - Initialize unused nodes safely
       - Avoid special-case handling during queries

    NOTE:
    - Commutativity is NOT required.
    - The order of combination is fixed by the tree structure.

    ------------------------------------------------------------
    Tree Structure and Indexing
    ------------------------------------------------------------

    - The segment tree is built over indices [1, n].
    - Each node represents a contiguous subarray [L, R].
    - Leaf nodes correspond to single elements of the array.
    - Internal nodes store the result of combining their children.

    The tree is stored in an array `tree` where:
        node i has children at 2*i and 2*i + 1.

    ------------------------------------------------------------
    Build Phase
    ------------------------------------------------------------

    - The build process constructs the tree in O(n) time.
    - Leaves are initialized from the input array.
    - Internal nodes are computed bottom-up using `combine`.

    ------------------------------------------------------------
    Query Behavior
    ------------------------------------------------------------

    - A query recursively traverses the tree.
    - If a node's range lies completely outside [l, r], the identity
      element is returned.
    - If a node's range lies completely inside [l, r], its stored
      value is returned.
    - Partial overlaps combine results from both children.

    This guarantees correctness due to associativity.

    ------------------------------------------------------------
    Update Behavior
    ------------------------------------------------------------

    - A point update modifies a single leaf.
    - The change is propagated upward, recomputing affected nodes.
    - Each update takes O(log n) time.

    ------------------------------------------------------------
    Time and Space Complexity
    ------------------------------------------------------------

    - Build time:      O(n)
    - Query time:      O(log n)
    - Update time:     O(log n)
    - Space usage:     O(n)

    ------------------------------------------------------------
    Summary
    ------------------------------------------------------------

    - Generic segment tree supporting range queries and point updates
    - Requires an associative operation with an identity element
    - Does not rely on commutativity
    - Clean, reusable template-based design
*/

// Time complexity analysis of range query
// ---------------------------------------
//
// Consider a segment tree built over an array of size n.
// The height of the tree is h = ⌈log2 n⌉.
//
// During a range query on [ql, qr], a node with segment [l, r]
// falls into exactly one of the following cases:
//
// 1) No overlap:     [l, r] ∩ [ql, qr] = ∅
//    The recursion stops immediately at this node.
//
// 2) Total overlap:  [l, r] ⊆ [ql, qr]
//    The node contributes its stored value and recursion stops.
//
// 3) Partial overlap: [l, r] ∩ [ql, qr] ≠ ∅ but [l, r] ⊄ [ql, qr]
//    We recurse into both children.
//
// Observation:
// At any fixed depth of the tree, the segments of all nodes
// form a partition of the array and are pairwise disjoint.
// Therefore, at that depth, there are at most two nodes whose
// segments partially overlap with the query interval [ql, qr]:
// one containing ql and one containing qr (they may coincide).
//
// Hence, at each depth, the recursion continues from at most
// two nodes. Since the height of the tree is h = O(log n),
// the total number of nodes where recursion branches is O(log n).
//
// Each such node can contribute at most a constant number of
// additional visited nodes (its children).
//
// Therefore, the total number of nodes visited by the query
// operation is O(log n), and the query runs in O(log n) time.


// 1-indexed Generic Segment Tree
template<typename T>
class SegmentTree {
private:
    vector<T> tree;
    int n;
    T identity;
    function<T(T, T)> combine;
    
    void build(int node, int left, int right, vector<T>& arr) {
        if (left == right) {
            tree[node] = arr[left];
            return;
        }
        
        int mid = left + (right - left) / 2;
        build(2 * node, left, mid, arr);
        build(2 * node + 1, mid + 1, right, arr);
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
    
    // The time complexity of the query operation will be proportional
    // to the number of nodes that we visit during the call chain.

    // We only recurse into the subtrees of a node if the segment of the node
    // partially overlaps with [ql, qr]. Otherwise, we simply return from the node.
    // Partial overlap means that the node's segment either contains ql or qr (but not both).
    // Since on each layer, all the segments of the nodes are disjoint, there are at most two segments
    // on each layer that contain ql and qr, and since there are only log(n) layers, we have at most
    // 2 * log(n) such nodes where we recurse into the subtrees.
    // The tree formed by such a call chain would have at most 2 * log(n) internal nodes and thus
    // at most 2*log(n) + 1 leaf nodes.
    // Thus, the total number of nodes visited by the query function is at most 4 * log(n) + 1
    T query(int node, int left, int right, int queryLeft, int queryRight) {
        if (queryRight < left || right < queryLeft) 
            return identity;
        if (queryLeft <= left && right <= queryRight) 
            return tree[node];
        
        int mid = left + (right - left) / 2;
        T leftResult = query(2 * node, left, mid, queryLeft, queryRight);
        T rightResult = query(2 * node + 1, mid + 1, right, queryLeft, queryRight);
        return combine(leftResult, rightResult);
    }
    
    void update(int node, int left, int right, int pos, T val) {
        if (left == right) {
            tree[node] = val;
            return;
        }
        
        int mid = left + (right - left) / 2;
        if (pos <= mid) 
            update(2 * node, left, mid, pos, val);
        else 
            update(2 * node + 1, mid + 1, right, pos, val);
        
        tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    // constructor: size, input array, combine function, identity element
    SegmentTree(int size, vector<T>& input, function<T(T, T)> op, T id) 
        : n(size), combine(op), identity(id) {
        // the number of nodes in a segment tree with array length = 2^k for some k >= 1 is 2^(k + 1) - 1
        tree.resize(4 * n + 1, identity); // 4 * n + 1 >= 2 * next_power_of_two(n) - 1
        build(1, 1, n, input);
    }

    // The following both functions work for operations that
    // are associative and have an identity element
    // range query [l, r]
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    
    // point update: set arr[idx] = val
    void set(int idx, T val) {
        update(1, 1, n, idx, val);
    }
};

// point update range query
// the operation is assumed to be applied from left to right in the array
template <typename T>
class PURQ {
private:
    vector<T> tree;
    T identity;
    function<T(T, T)> op;
    int n;

    void build(int idx, int l, int r, vector<T> &arr) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(2*idx, l, m, arr);
        build(2*idx+1, m+1, r, arr);
        tree[idx] = op(tree[2*idx], tree[2*idx+1]);
    }

    T get(int idx, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return identity;
        if (ql <= l && r <= qr) return tree[idx];
        int m = l + (r - l) / 2;
        return op(
            get(2*idx, l, m, ql, qr),
            get(2*idx+1, m+1, r, ql, qr)
        );
    }

    void set(int idx, int l, int r, int i, T val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (i <= m) set(2*idx, l, m, i, val);
        else set(2*idx+1, m+1, r, i, val);
        tree[idx] = op(tree[2*idx], tree[2*idx+1]);
    }

public:
    PURQ(int n, vector<T> &arr, T identity, function<T(T,T)> op)
        : n(n), identity(identity), op(op) {
        tree.resize(4*n + 1, identity);
        build(1, 1, n, arr);
    }

    T query(int l, int r) {
        return get(1, 1, n, l, r);
    }

    void update(int i, T val) {
        set(1, 1, n, i, val);
    }
};
