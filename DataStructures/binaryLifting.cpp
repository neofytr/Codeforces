#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define LOG (18)
// 2^18 = 262144 > 2e5
// so storing ancestors up to level 18 is sufficient
// because maximum depth in worst case (chain tree) is n-1 <= 2e5


// ------------------------------------------------------------
// global structures
// ------------------------------------------------------------

vector<int> tree[MAX + 1];
// adjacency list representation of the tree

int depth[MAX + 1];
// depth[u] = distance from root to u
// depth[root] = 0
// depth increases by 1 along each edge away from root

int tab[LOG + 1][MAX + 1];
// tab[i][u] = 2^i-th ancestor of node u
//
// meaning:
// tab[0][u] = parent of u
// tab[1][u] = 2nd ancestor
// tab[2][u] = 4th ancestor
// ...
//
// invariant after preprocessing:
// for every node u and every i,
// tab[i][u] correctly stores the 2^i-th ancestor
// or -1 if no such ancestor exists


// ------------------------------------------------------------
// walk(u, k)
// move node u upward by exactly k edges
// ------------------------------------------------------------
int walk(int u, int k) {

	// invariant:
	// curr is always equal to original u moved upward
	// by sum of processed powers of two
	int curr = u;

	// binary decomposition of k
	// if kth bit is set, jump 2^i upward
	for (int i = 0; i <= LOG; i++) {

		if (k & (1ll << i)) {

			// jump exactly 2^i edges upward
			// correctness:
			// tab[i][curr] stores 2^i-th ancestor
			curr = tab[i][curr];

			// if we moved above root
			if (curr == -1) break;
		}
	}

	return curr;
}


int lca(int u, int v) {

	/*
	Induction Proof of Correctness of This Function.

	Let L be the true lowest common ancestor of the original nodes u and v.

	------------------------------------------------------------
	Part 1: Equalizing depths
	------------------------------------------------------------

	after possibly swapping, depth[u] >= depth[v].

	we replace u by walk(u, depth[u] - depth[v]).
	this moves u upward exactly the depth difference.

	claim 1:
	this operation does not change L.

	proof:
	if u is below L, then every ancestor of u on the path to root,
	up to and including L, lies on the same root path.
	lifting u upward along its ancestor chain cannot skip over L,
	because L is also an ancestor of u.
	thus after lifting, L remains a common ancestor of u and v.

	also depth[u] == depth[v].

	if u == v now, then one node was ancestor of the other,
	and that node is exactly L, so returning u is correct.

	so from now on assume:
	depth[u] == depth[v]
	u != v
	both are strictly below L.

	------------------------------------------------------------
	Part 2: Simultaneous (Greedy) Lifting
	------------------------------------------------------------

	we iterate i from LOG down to 0.

	define the loop invariant:

	for the current u and v at the start of each iteration i:

	(1) depth[u] == depth[v]
	(2) u != v
	(3) both u and v are descendants of L
	(4) for every k > i, tab[k][u] == tab[k][v]

	------------------------------------------------------------
	Base case:
	------------------------------------------------------------

	before the first iteration (i = LOG):

	(1) holds from part 1.
	(2) holds since we already handled u == v.
	(3) holds since lifting in part 1 never crossed L.
	(4) is vacuously true because there is no k > LOG.

	so the invariant holds initially.

	------------------------------------------------------------
	Induction step:
	------------------------------------------------------------

	assume invariant holds at start of iteration i.

	there are two cases:

	case a: tab[i][u] == tab[i][v]

	we do nothing.
	then:

	- depth[u] == depth[v] remains true.
	- u != v remains true.
	- both remain below L.
	- for k >= i, tab[k][u] == tab[k][v] still holds.
	  for k > i it was already true,
	  and for k == i it holds by condition of this case.

	so invariant holds for next iteration (i-1).

	case b: tab[i][u] != tab[i][v]

	then L cannot be at or below the 2^i-th ancestor of u,
	because if L were at or below that level,
	then tab[i][u] and tab[i][v] would be equal
	(since L is common ancestor).

	thus L is strictly above both tab[i][u] and tab[i][v].

	we update:
	u = tab[i][u]
	v = tab[i][v]

	then:

	- depth[u] == depth[v], since both jumped equal distance 2^i.
	- u != v, since we only jump when their ancestors differ.
	- both remain strictly below L, because we proved L is above these nodes.
	- for any k > i, tab[k][u] == tab[k][v] still holds,
	  since those ancestors were already equal before the jump
	  and jumping equal distances preserves equality at higher levels.

	so invariant holds for next iteration (i-1).

	------------------------------------------------------------
	Termination:
	------------------------------------------------------------

	after loop finishes (i = -1):

	from invariant with i = -1:

	(1) depth[u] == depth[v]
	(2) u != v
	(3) both are strictly below L
	(4) for all k >= 0, tab[k][u] == tab[k][v]

	in particular for k = 0:
	tab[0][u] == tab[0][v]

	let p = tab[0][u].

	then p is a common ancestor of both u and v.

	since u and v are strictly below L,
	and we never jumped across L,
	u and v are immediate children (in possibly different subtrees)
	of L at this point.

	therefore p == L.

	the function returns tab[0][u],
	which equals L,
	the true lowest common ancestor.

	------------------------------------------------------------
	conclusion:
	------------------------------------------------------------

	by induction on loop iterations,
	the invariant holds throughout,
	and at termination the returned node
	is exactly the lowest common ancestor.

	hence the function lca(u, v) correctly returns
	the lowest common ancestor of u and v.
	*/

	if (depth[u] < depth[v]) swap(u, v);

	u = walk(u, depth[u] - depth[v]);

	if (u == v) return u;

	for (int i = LOG; i >= 0; i--) {
		if (tab[i][u] != tab[i][v]) {
			u = tab[i][u];
			v = tab[i][v];
		}
	}

	return tab[0][u];
}

// ------------------------------------------------------------
// distance between two nodes
// ------------------------------------------------------------
int dist(int u, int v) {

	// property of trees:
	// distance(u,v) =
	// depth[u] + depth[v] - 2 * depth[lca(u,v)]
	return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}


int32_t main() {

	int n;
	cin >> n;

	// read tree edges
	int u, v;
	for (int i = 1; i <= n - 1; i++) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	// initialize depth as unvisited
	for (int i = 1; i <= n; i++)
		depth[i] = -1;

	// initialize ancestor table
	for (int i = 0; i <= LOG; i++)
		for (int j = 0; j <= n; j++)
			tab[i][j] = -1;

	int root = 1;
	queue<int> que;

	// bfs to compute:
	// depth and immediate parent

	depth[root] = 0;
	tab[0][root] = -1;
	que.push(root);

	while (!que.empty()) {

		int x = que.front();
		que.pop();

		for (int nxt : tree[x]) {

			if (depth[nxt] == -1) {

				depth[nxt] = depth[x] + 1;
				tab[0][nxt] = x;
				que.push(nxt);
			}
		}
	}

	// build binary lifting table
	// recurrence:
	// 2^i-th ancestor =
	// 2^(i-1)-th ancestor of
	// (2^(i-1)-th ancestor)

	for (int i = 1; i <= LOG; i++) {
		for (int j = 1; j <= n; j++) {

			if (tab[i - 1][j] != -1)
				tab[i][j] = tab[i - 1][ tab[i - 1][j] ];
			else
				tab[i][j] = -1;
		}
	}

	return 0;
}


/*
============================================================
formal correctness proof of lca algorithm
============================================================

definition:
lca(u, v) = deepest node that is ancestor of both u and v.

------------------------------------------------------------
proof structure
------------------------------------------------------------

1) correctness of equalizing depths

after:
    u = walk(u, depth[u] - depth[v])

we guarantee:
    depth[u] == depth[v]

if u == v:
    then one was ancestor of other,
    so returning u is correct.


2) key invariant in second phase

let L = true lca(u_original, v_original)

before second loop:
    depth[u] == depth[v]
    u != v
    both nodes are at same depth
    both are descendants of L


3) why greedy largest jump works

we iterate i from LOG down to 0.

consider any level i:

case A:
    tab[i][u] == tab[i][v]

this means their 2^i ancestors coincide.
so L is at or below that ancestor.
jumping would overshoot L.
so we do NOT jump.

case B:
    tab[i][u] != tab[i][v]

this means their 2^i ancestors differ.
so L must be strictly above that level.
jumping keeps both below L.
so jump is safe.

thus we always jump the largest safe distance.


4) why we cannot skip L

suppose we skipped over L.

that would mean:
    we jumped from below L
    to above L

but jump only happens when
    tab[i][u] != tab[i][v]

if jump crosses L,
then their 2^i ancestors would have been equal
(because above L paths merge),
contradiction.

thus we never cross L.


5) final state after loop

after loop:
    for all i,
    tab[i][u] == tab[i][v]

this means:
    u and v are distinct
    but their parents are equal

so:
    tab[0][u] == tab[0][v] == L

therefore returning parent gives correct lca.


------------------------------------------------------------
time complexity
------------------------------------------------------------

preprocessing:
    bfs: O(n)
    table build: O(n log n)

query:
    walk: O(log n)
    lca: O(log n)

total per query: O(log n)

------------------------------------------------------------
binary lifting is correct because:
    ancestor relation is transitive
    binary decomposition covers all jump sizes
    greedy largest safe jump never crosses lca
============================================================
*/