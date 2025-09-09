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