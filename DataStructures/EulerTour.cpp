#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

// -----------------------------------------------------------------------------
// EULER TOUR TREE FLATTENING (ENTER + EXIT VERSION)
//
// idea:
// run a dfs on the tree and record each node twice:
//   1) when we ENTER the node
//   2) when we EXIT the node
//
// this produces a linear array that represents the walk of the dfs.
// every edge of the tree is traversed twice, so the array size ≈ 2 * n.
//
// why we do this:
// many tree problems become much easier once the tree is mapped to an array.
// once flattened, we can apply classical range data structures:
//
//   - prefix sums
//   - fenwick tree (bit)
//   - segment tree
//   - range minimum / maximum queries
//
// the key property created by this flattening:
//
//   the entire subtree of a node v becomes a contiguous segment
//   in the euler array.
//
// specifically:
//
//   subtree(v) ↔ indices [ pre[v], post[v] ] in lin[]
//
// this lets us convert subtree queries into simple range queries.
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// lin[] : stores the euler tour of the tree.
//
// during dfs:
//   entry of node  -> store value
//   exit of node   -> store value again
//
// so every node appears exactly twice.
//
// example tree:
//
//        1
//      /   \
//     2     3
//    / \
//   4   5
//
// euler tour (node ids):
//
//   1 2 4 4 5 5 2 3 3 1
//
// lin[] stores the value of the node at that time.
// -----------------------------------------------------------------------------
int lin[2 * MAX + 1];


// -----------------------------------------------------------------------------
// pre[v] : entry time of node v in the euler tour
//
// this is the index where we FIRST encounter the node.
//
// important observation:
//
//   when dfs enters v, we begin exploring the entire subtree of v.
//
// therefore:
//
//   pre[v] marks the start of the subtree segment in lin[].
// -----------------------------------------------------------------------------
int pre[MAX + 1];


// -----------------------------------------------------------------------------
// post[v] : exit time of node v
//
// this is recorded AFTER all children of v have been processed.
//
// important observation:
//
//   when dfs exits v, the entire subtree of v has already been visited.
//
// therefore:
//
//   subtree(v) corresponds to the contiguous range:
//
//       lin[ pre[v] ... post[v] ]
//
// this is the central property exploited by most subtree query problems.
// -----------------------------------------------------------------------------
int post[MAX + 1];


// -----------------------------------------------------------------------------
// adjacency list representation of the tree
//
// tree[u] contains all neighbors of node u.
// since this structure represents a tree:
//
//   number of edges = n - 1
//
// dfs uses this list to traverse children.
// -----------------------------------------------------------------------------
vector<int> tree[MAX + 1];


// -----------------------------------------------------------------------------
// val[v] : value stored at node v
//
// depending on the problem this could represent:
//
//   - weight of the node
//   - color
//   - cost
//   - xor value
//   - frequency contribution
//
// during the euler tour we store this value into lin[].
// -----------------------------------------------------------------------------
int val[MAX + 1];


// -----------------------------------------------------------------------------
// global timer used to index the euler array
//
// acts like a "dfs clock".
//
// every time we record something in lin[],
// this counter increases.
//
// starting from 1 keeps arrays naturally 1-indexed.
// -----------------------------------------------------------------------------
int time = 1;


// -----------------------------------------------------------------------------
// dfs(node, parent)
//
// performs the euler tour traversal and constructs:
//
//   pre[]
//   post[]
//   lin[]
//
// parameters:
//   node   -> current node being visited
//   parent -> node we came from (prevents traversing the edge backward)
// -----------------------------------------------------------------------------
void dfs(int node, int parent) {

	// record the moment we ENTER the node
	// this becomes the start index of the subtree interval
	pre[node] = time;

	// store the node value in the flattened array
	// represents the dfs entering this node
	lin[time++] = val[node];

	// explore all adjacent nodes (children in the tree)
	for (int v : tree[node])

		// skip the parent to avoid going back up the tree
		if (v != parent)

			// recursively process the child's subtree
			dfs(v, node);

	// at this point all descendants of "node" have been visited

	// record the EXIT time of this node
	post[node] = time;

	// store the node again to represent leaving it
	lin[time++] = val[node];
}


// -----------------------------------------------------------------------------
// important observations about the constructed structure:
//
// 1) subtree interval
//
//    for every node v:
//
//       subtree(v) ↔ lin[ pre[v] ... post[v] ]
//
//    therefore:
//
//       subtree query → range query
//
//
//
// 2) typical use cases
//
//    - sum of subtree values
//    - xor of subtree
//    - maximum value in subtree
//    - counting nodes with a property inside a subtree
//
//    these can be solved with:
//
//       segment tree or fenwick tree on lin[]
//
//
//
// 3) note about double appearances
//
//    since each node appears twice, some problems adjust the stored values.
//    a common trick:
//
//       entry  → +value
//       exit   → -value
//
//    this allows prefix sums to correctly represent subtree sums.
//
//
//
// 4) complexity
//
//    dfs construction:  O(n)
//    each node visited once
//    each edge traversed twice
//
//
//
// 5) when to think of this technique
//
//    whenever a problem involves:
//
//       - subtree queries
//       - subtree updates
//       - converting tree problems to range queries
//
//    this euler tour flattening is often the first step.
//
// -----------------------------------------------------------------------------