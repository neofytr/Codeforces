#include <bits/stdc++.h>
using namespace std;

// If every node of an undirected graph has at most two nodes, then for any connected component of the graph, only one of
// the following two are possible:
// 1. The component is a linear chain and the degree of all nodes except the ends (which have degree 1) of the chain have degree 2
// 2. The component is a pure cycle and the degree of all its node is 2
// 3. The component consists of a single node and the degree of all nodes in the component is 0

// So, a component of such a graph is a pure cycle iff all its nodes have degree 2