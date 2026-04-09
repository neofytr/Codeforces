#include <bits/stdc++.h>
using namespace std;

// Percolation
// A model of many physical systems:
// 1. NxN grid of sites
// 2. Each site is open with probability p (or blocked with probability 1 - p)
// 3. System percolated iff top and bottom rows are connected by open sites

// Likelihood of percolation
// Depends on the site vacancy probability p

// Percolation Phase Transition
// When N is large, literature guarantees a sharp threshold p*
// 1. p > p* -> a random NxN system will almost certainly percolate
// 2. p < p* -> a random NxN system almost certainly does not percolate
// No mathematical solution for determining the percolation threshold p* has yet been derived

// Monte Carlo Simulation
// 1. Initialize NxN whole grid to be blocked
// 2. Declare random sites open until top row connected to bottom row
// 3. Vacancy percentage estimates p*

// Dynamic Connectivity Solution to Estimate Percolation Threshold
// How to check whether an NxN system percolates?
// 1. Create an object for each site and name them 0 to N^2 - 1
// 2. Sites are in the same component iff they are connected by open sites
// 3. System percolates iff any site on the bottom row is connected to any site on the top row (brute-force algorithm: at most N^2 call to connected)
// 4. Clever Trick -> Introduce 2 virtual sites. Connect the first virtual site to each site on the top row
// and connect the second virtual site to each site on the bottom row. The system percolates iff the top and bottom
// virtual sites are connected.

// How to model opening a new site?
// Connect newly opened side to all of its adjacent open sites

class WeightedQuickUnionWithPathCompression {
  private:
    vector<int> id, sz;
    bool validate(const int x) const { return x >= 0 && x < id.size(); }
    int root(int p) {
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

    bool connected(const int p, const int q) {
        if (!validate(p) || !validate(q))
            return false;
        return root(p) == root(q);
    }
    void unite(const int p, const int q) {
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

class Percolation {
  private:
    WeightedQuickUnionWithPathCompression *uf;
    int size;
    bool validate(const int row, const int col) const { return row >= 0 && row < size && col >= 0 && col < size; }
    vector<vector<int>> opn;
    int numOpen;
    int virtualOne, virtualTwo;

  public:
    explicit Percolation(const int n) {
        size = n;
        uf = new WeightedQuickUnionWithPathCompression(n * n + 2);
        opn.resize(n, vector<int>(n, false));
        virtualOne = n * n;
        virtualTwo = n * n + 1;
        numOpen = 0;
        for (int r = 0; r < n; r++) {
            uf->unite(virtualOne, r);               // top row
            uf->unite(virtualTwo, (n - 1) * n + r); // bottom row
        }
    }

    void open(const int row, const int col) {
        if (!validate(row, col) || opn[row][col])
            return;

        opn[row][col] = true;
        numOpen++;

        const int dr[] = {-1, 0, +1, 0};
        const int dc[] = {0, -1, 0, +1};
        const int current = row * size + col;

        for (int r = 0; r < 4; r++) {
            const int nrow = row + dr[r];
            const int ncol = col + dc[r];
            if (validate(nrow, ncol) && opn[nrow][ncol]) {
                const int neighbor = nrow * size + ncol;
                uf->unite(current, neighbor);
            }
        }
    }

    bool percolates() const { return uf->connected(virtualOne, virtualTwo); }

    int getNumOpen() const { return numOpen; }
};


