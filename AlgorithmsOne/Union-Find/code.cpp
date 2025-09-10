#include <bits/stdc++.h>
using namespace std;

/*
 * Steps to developing a usable algorithm ->
 * 1. Model the problem
 * 2. Find an algorithm to solve it
 * 3. Fast enough? Fits in memory?
 * 4. If not, figure out why
 * 5. Find a way to address the problem
 * 6. Iterate until satisfied
 */

/*

Dynamic Connectivity Problem

Given a set of N objects
1. Union command -> connect two objects
2. Find/Connected query -> is there a path connecting two objects?

Modeling the Objects
Applications of Union-Find involves manipulating objects of all types
When programming, it's convenient to name objects 0 to N-1
This allows us to use objects as indexes into arrays and then quickly access information
relevant to each object
This also suppresses details about the objects not relevant to union-find

Modeling the Connections
We assume "is connected to" is an equivalence relation:
1. Reflexive -> p is connected to p
2. Symmetric -> If p is connected to q, then q is connected to p
3. Transitive -> If p is connected to q and q is connected to r, then p is connected to r

When we have an equivalence relation on the connections between a set of objects, the set of objects can be
divided into subsets called connected components
A connected component is a maximal set of objects that are mutually connected

Implementing the operations ->
1. Find query -> Check if two objects are in the same component
2. Union command -> Replace components containing two objects with their union

Union-find data type (API)
Goal -> Design efficient data structure for union-find
1. Number of objects N can be huge
2. Number of operations M can be huge
3. Find queries and union commands may be intermixed

*/

class UnionFind {
  public:
    virtual explicit UnionFind(int n);        // initialize union-find data structure with n objects (0 to n-1)
    virtual void unite(int p, int q) = 0;     // add connection between p and q
    virtual bool connected(int p, int q) = 0; // are p and q in the same component?
};

// Quick-Find (eager approach)
// Data Structure ->
// Integer array id[] of size n
// Interpretation -> p and q are connected iff they have the same id
class QuickFind : public UnionFind {
  private:
    vector<int> id;
    bool validate(const int x) const { return x >= 0 && x < id.size(); }

  public:
    explicit QuickFind(const int n) {
        if (n <= 0)
            return;
        id.resize(n);
        for (int r = 0; r < n; r++)
            id[r] = r; // initially, all objects are in their own components since there are no connections initially
    }

    // check if p and q have the same ID
    explicit bool connected(const int p, const int q) override {
        if (!validate(p) || !validate(q))
            return false;
        return id[p] == id[q];
    }

    // to merge components containing p and q, change all entries whose id equals id[p] to id[q]
    explicit void unite(const int p, const int q) override {
        if (!validate(p) || !validate(q))
            return;
        const int idp = id[p];
        const int idq = id[q];
        for (int &val : id)
            if (val == idp)
                val = idq;
    }
};

// Quick-Union (lazy approach -> avoids doing work until we have to)
// Data Structure
// 1. Integer array id[] of size n
// 2. Each component is a tree rooted at some object (called the root of that tree/component)
// 3. Interpretation -> id[r] is the parent of r in the tree of its component for non-root nodes and id[r] = r for root nodes of components
// 3. Root of r is id[id[...id[r]...]] <- keep going until it doesn't change (the algorithm ensures no cycles)
class QuickUnion : public UnionFind {
  private:
    vector<int> id;
    int root(const int x) const {
        while (x != id[x])
            x = id[x];
        return x;
    }
    bool validate(const int x) const { return x >= 0 && x < id.size(); }

  public:
    explicit QuickFind(const int n) {
        if (n < 0)
            return;
        id.resize(n);
        for (int r = 0; r < n; r++)
            id[r] = r;
    }

    // find operation -> check if p and q have the same root
    bool connected(const int p, const int q) override {
        if (!validate(p) || !validate(q))
            return false;
        return root(p) == root(q);
    }

    // union -> to merge components containing p and q, set the id of p's root to the id of q's root
    void unite(const int p, const int q) override {
        if (!validate(p) || !validate(q))
            return false;
        id[root(p)] = root(q);
    }
};

// Weighted Quick-Union
// Modify quick-union to avoid tall trees
// Keep track of the sizes of each tree (number of objects)
// Balance by linking root of the smaller tree to root of the larger tree

// Data Structure
// Same as quick-union, but maintain extra array size[r] to count the number of objects in the tree (subtree) rooted at r
class WeightedQuickUnion : public QuickFind {
  private:
    vector<int> id, sz;
    bool validate(const int x) const { return x >= 0 && x < id.size(); }
    int root(const int p) const {
        while (p != id[p])
            p = id[p];
        return p;
    }

  public:
    WeightedQuickUnion(const int n) {
        if (n < 0)
            return;
        id.resize(n), sz.resize(n);
        for (int r = 0; r < n; r++)
            id[r] = r, sz[r] = 1;
    }

    // identical to quick-union
    bool connected(const int p, const int q) override {
        if (!validate(p) || !validate(q))
            return false;
        return root(p) == root(q);
    }

    // union -> modify quick-union to
    // 1. Link root of smaller tree to root of larger tree
    // 2. Update the size[] array
    void unite(const int p, const int q) override {
        const int rootP = root(p);
        const int rootQ = root(q);
        if (rootP == rootQ)
            return;
        if (sz[rootP] > sz[rootQ]) { // attach rootQ to rootP
            id[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
        } else { // attach rootP to rootQ
            id[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        }
    }
};

// Let n >= 1
// Proposition: After any number of union operations in the WeightedQuickUnion Algorithm, the depth of any node x is at-most log2(n)
// Proof ->
// Initially, each node is in a tree of its own and thus, initially, each node has a depth = 0.
// The depth of a node can increase only during a union operation, and can only increase by exactly one and that too only
// when the tree the node is part of is attached to a larger tree.
// Thus, to increase the depth of any node by 1, the size of its tree at least doubles.
// This can be easily seen as follows ->
// Let p and q be nodes that are not in the same component. Let the size of the tree of p, denoted t(p) be <= t(p)
// Then, the root of p is attached to the root of q and the depth of p increases by one
// Thus, finally the size of the tree of p = t(p) + t(q) >= t(p) + t(p) = 2 * t(p)

// Hence, if a node has depth d, the size of its tree will be at least 2^d. However, since there are only n nodes,
// it follows that ->
// 2^d <= n or d <= log2(n)
// We thus have the proposition.

// Weighted Quick Union with Path compression
// Just after computing the root of p, set the id of each examined node to that root
// Two pass implementation -> add second loop to root() to set the id of each examined node to the root

class WeightedQuickUnionWithPathCompression {
  private:
    vector<int> id, sz;
    bool validate(const int x) const { return x >= 0 && x < id.size(); }
    int root(int p) const {
        int x = p;
        while (p != id[p])
            p = id[p];

        int tmp;
        while (x != id[x]) // path compression loop
            tmp = id[x], id[x] = p, x = tmp;
        return p;
    }

  public:
    explicit WeightedQuickUnionWithPathCompression(const int n) {
        id.resize(n), sz.resize(n);
        for (int r = 0; r < n; r++)
            id[r] = r, sz[r] = 1;
    }

    bool connected(const int p, const int q) const override {
        if (!validate(p) || !validate(q))
            return false;
        return root(p) == root(q);
    }
    void unite(const int p, const int q) override {
        const int rootP = root(p);
        const int rootQ = root(q);
        if (rootP == rootQ)
            return;
        if (sz[rootP] > sz[rootQ]) { // attach rootQ to rootP
            id[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
        } else { // attach rootP to rootQ
            id[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        }
    }
};

// Proposition: Starting from an empty data structure, any sequence of M union-find operations on N objects
// makes <= c (N + M log*(N)) array accesses.
// Analysis can be improved to N + M alpha(M, N)

// Linear-time algorithm for M union-find operations on N objects?
// We can prove that there is no such algorithm
// 1. Cost within constant factor of reading in the data
// 2. In theory, WQUPC is not quite linear
// 3. In practice, WQUPC is linear

int main() {
    // Dynamic Connectivity Client

    int n;
    cin >> n;

    UnionFind uf(n);
    int p, q;
    while (cin >> p >> q) {
        if (!uf.connected())
            uf.unite(p, q), cout << p << q << endl;
    }
    return 0;
}