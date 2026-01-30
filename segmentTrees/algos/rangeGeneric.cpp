#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
    segment tree with lazy propagation (range update, point query)
    --------------------------------------------------------------

    we maintain a segment tree over an array A[1..n] that supports:

    1) update(l, r, v):
       for every index i in [l, r], apply:
           A[i] = A[i] op v

    2) get(i):
       returns the current value of A[i]

    ------------------------------------------------------------
    algebraic requirements on the operation `op`
    ------------------------------------------------------------

    the operation `op` must satisfy:

    1) associativity:
           (a op b) op c = a op (b op c)

       this allows multiple pending updates to be composed safely.

    2) identity element:
       there must exist an element `id` such that:
           a op id = id op a = a

       the identity element is required to:
       - represent "no pending update"
       - initialize all lazy nodes
       - avoid special-case handling during propagation

    3) commutativity is NOT required:
           a op b != b op a   (allowed)

       correctness relies on preserving update order, not reordering.

    ------------------------------------------------------------
    core idea
    ------------------------------------------------------------

    - the base array A[i] is stored separately.
    - the segment tree stores ONLY pending operations (lazy values).
    - no segment stores an aggregated value of A[].

    during a point query, all pending operations affecting that index
    are collected (in order) and applied to the base value.

    ------------------------------------------------------------
    lazy propagation invariant (critical)
    ------------------------------------------------------------

    each node represents a segment [L, R] and stores a lazy value that
    represents ALL updates that should be applied to every element in
    that segment, but have not yet been pushed downward.

    CRITICAL INVARIANT:
    - lazy operations are stored and applied in the EXACT
      chronological order in which updates were issued.

    this guarantees correctness even for non-commutative operations.

    ------------------------------------------------------------
    update behavior
    ------------------------------------------------------------

    - range updates are applied lazily.
    - if a node is fully covered, its lazy value is composed with v.
    - if partially covered, the node's pending operation is pushed
      to its children BEFORE recursing.

    ------------------------------------------------------------
    query behavior
    ------------------------------------------------------------

    - point queries traverse root -> leaf.
    - along the path, all lazy operations are accumulated in order.
    - final value = base_value op (all pending operations).

    ------------------------------------------------------------
    complexity
    ------------------------------------------------------------

    update(l, r): O(log n)
    get(i):       O(log n)

    ------------------------------------------------------------
    summary
    ------------------------------------------------------------

    - supports range updates and point queries
    - requires associative operation with identity
    - does NOT require commutativity
    - preserves strict update ordering
    - uses lazy propagation efficiently
*/


// 1-indexed generic segment tree
template <typename T>
class SegmentTree {
private:
    int n;

    // tree[idx] stores the pending operation for this segment
    vector<T> tree;

    // base array values
    vector<T> arr;

    // identity element of the operation
    T identity;

    // associative operation
    function<T(T, T)> combine;

    // build initializes all lazy values to identity
    void build(int idx, int l, int r) {
        tree[idx] = identity;
        if (l == r) return;

        int m = l + (r - l) / 2;
        build(2 * idx, l, m);
        build(2 * idx + 1, m + 1, r);
    }

    // propagate pending operation to children
    void push(int idx) {
        // apply current pending operation to children
        tree[2 * idx]     = combine(tree[2 * idx], tree[idx]);
        tree[2 * idx + 1] = combine(tree[2 * idx + 1], tree[idx]);

        // clear current node's pending operation
        tree[idx] = identity;
    }

    // range update: apply op val on [ql, qr]
    void update(int idx, int l, int r, int ql, int qr, T val) {
        // no overlap
        if (qr < l || r < ql) return;

        // fully covered segment
        if (ql <= l && r <= qr) {
            // compose operation in chronological order
            tree[idx] = combine(tree[idx], val);
            return;
        }

        // partial overlap: push before going down
        push(idx);

        int m = l + (r - l) / 2;
        update(2 * idx, l, m, ql, qr, val);
        update(2 * idx + 1, m + 1, r, ql, qr, val);
    }

    // point query: collect all pending operations affecting index i
    T query(int idx, int l, int r, int i) {
        // if leaf, return its pending operation
        if (l == r) return tree[idx];

        int m = l + (r - l) / 2;
        T res;

        // go to the correct child
        if (i <= m)
            res = query(2 * idx, l, m, i);
        else
            res = query(2 * idx + 1, m + 1, r, i);

        // apply current node's operation AFTER child
        // this preserves update ordering
        return combine(res, tree[idx]);
    }

public:
    // constructor
    SegmentTree(int size, const vector<T>& input,
                function<T(T, T)> op, T id)
        : n(size), identity(id), combine(op) {

        tree.resize(4 * n + 1);
        arr.resize(n + 1);

        for (int i = 1; i <= n; i++)
            arr[i] = input[i];

        build(1, 1, n);
    }

    // apply op val on range [l, r]
    void update(int l, int r, T val) {
        update(1, 1, n, l, r, val);
    }

    // get current value of A[i]
    T get(int i) {
        // base value combined with all pending operations
        return combine(arr[i], query(1, 1, n, i));
    }
};
