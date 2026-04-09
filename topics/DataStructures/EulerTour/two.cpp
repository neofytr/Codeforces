#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

// -----------------------------------------------------------------------------
// EULER TOUR TREE FLATTENING (ENTRY-ONLY VERSION)
//
// This is the MOST COMMON Euler tour variant used in competitive programming
// for subtree queries.
//
// Difference from the previous variant:
// - Each node is recorded ONLY ONCE (when entered).
// - We do NOT record the exit event.
//
// Because of this:
//     size of the flattened array = n
// instead of 2n.
//
// Core idea:
// During DFS, when we first visit a node we assign it a time index.
// DFS explores the entire subtree before returning, so all nodes in that
// subtree will receive consecutive indices.
//
// Therefore:
//
//     subtree(v) ↔ range [ pre[v], post[v] ] in lin[]
//
// This lets us convert subtree problems into simple array range queries.
//
// Once flattened, we can use:
//     • Prefix sums
//     • Fenwick Tree (BIT)
//     • Segment Tree
//     • Range queries
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// val[v]
// value stored at node v.
//
// This may represent:
//   - weight
//   - cost
//   - color
//   - xor value
//   - frequency contribution
//
// When we visit the node during DFS, we copy this value into lin[].
// -----------------------------------------------------------------------------
int val[MAX + 1];


// -----------------------------------------------------------------------------
// adjacency list of the tree
//
// tree[u] contains all neighbors of node u.
//
// since the structure is a tree:
//     number of edges = n - 1
//
// DFS uses this list to traverse children.
// -----------------------------------------------------------------------------
vector<int> tree[MAX + 1];


// -----------------------------------------------------------------------------
// lin[]
//
// flattened representation of the tree.
//
// When DFS enters a node, we store its value in lin[].
// Each node appears exactly once.
//
// Example tree:
//
//        1
//      /   \
//     2     3
//    / \
//   4   5
//
// DFS order:
//
//     1 2 4 5 3
//
// lin[] will contain:
//
//     [1,2,4,5,3] (values of those nodes)
//
// Subtrees become contiguous segments inside this array.
// -----------------------------------------------------------------------------
int lin[MAX + 1];


// -----------------------------------------------------------------------------
// pre[v] = time when DFS first visits node v
// The value of the node v is stored in lin[] at index pre[v].
//
// also commonly called:
//     tin[v]
//     discovery time
//
// this marks the START of the subtree interval in lin[].
// -----------------------------------------------------------------------------
int pre[MAX + 1];


// -----------------------------------------------------------------------------
// post[v]
//
// marks the LAST time index that belongs to the subtree of v.
//
// since DFS processes an entire subtree before returning,
// the timer will have advanced to the end of the subtree
// when we finish exploring v.
//
// therefore:
//
//     subtree(v) ↔ lin[ pre[v] ... post[v] ]
//
// This property is the key reason this technique is useful.
// -----------------------------------------------------------------------------
int post[MAX + 1];


// -----------------------------------------------------------------------------
// global timer used to assign indices during DFS
//
// t always represents the index of the LAST node inserted
// into the flattened array.
//
// Each time we visit a node we increment it.
//
// final value of t = number of nodes visited = n.
// -----------------------------------------------------------------------------
int t = 0;


// -----------------------------------------------------------------------------
// dfs(node, parent)
//
// performs the tree flattening.
//
// parameters:
//     node   = current node being visited
//     parent = node we came from (prevents traversing backwards)
//
// after this DFS finishes:
//
//     pre[v]  = start of subtree
//     post[v] = end of subtree
//
// and subtree queries become simple array range queries.
// -----------------------------------------------------------------------------
void dfs(int node, int parent) {

	// move the global timer forward
	// this becomes the index assigned to the current node
	++t;

	// record entry time of this node
	pre[node] = t;

	// place the node's value into the flattened array
	// this represents visiting the node in DFS order
	lin[t] = val[node];

	// explore all children of this node
	for (int v : tree[node])

		// skip the parent so DFS does not go back up the tree
		if (v != parent)

			// recursively process the subtree of the child
			dfs(v, node);

	// when DFS reaches this line, the entire subtree of "node"
	// has already been visited
	// therefore the current timer value is the end of the subtree
	post[node] = t;
}


// -----------------------------------------------------------------------------
// IMPORTANT OBSERVATIONS ABOUT THIS STRUCTURE
// -----------------------------------------------------------------------------
//
// 1) SUBTREE RANGE PROPERTY
//
//      subtree(v) ↔ indices [ pre[v], post[v] ] in lin[]
//
//    every node in v's subtree appears in this contiguous interval.
//
//
//
// 2) SUBTREE SUM QUERY
//
//    if we build prefix sums:
//
//        prefix[i] = sum of lin[1..i]
//
//    then:
//
//        subtree_sum(v) = prefix[post[v]] - prefix[pre[v]-1]
//
//
//
// 3) USING FENWICK TREE OR SEGMENT TREE
//
//    build the structure over lin[]
//
//    subtree query:
//
//        query(pre[v], post[v])
//
//    subtree update:
//
//        update_range(pre[v], post[v])
//
//
//
// 4) TIME COMPLEXITY
//
//    DFS preprocessing:  O(n)
//    subtree query with segment tree:  O(log n)
//
//
//
// 5) WHEN TO USE THIS TECHNIQUE
//
//    think of this whenever a problem involves:
//
//        • queries on subtree
//        • updates on subtree
//        • counting nodes in subtree
//        • sum/xor/max over subtree
//
//    because this converts:
//
//        TREE PROBLEM → ARRAY RANGE PROBLEM
//
// 6) The value of the node v is stored in lin[] at index pre[v].
// -----------------------------------------------------------------------------