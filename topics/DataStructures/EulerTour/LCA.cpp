#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define LOG (19) // since the euler tour length is at most 2*n-1 ≈ 2e5
                 // and 2^19 > 2e5, this is enough levels for the sparse table

vector<int> graph[MAX + 1]; 
// adjacency list representation of the tree


/*
lin[] will store the euler tour of the tree.

important invariant:
lin[t] = node visited at time t during the euler tour

during dfs we record a node:
1) when we first enter it
2) every time we return to it from a child

so the tour length becomes 2*n-1 since we traverse each edge of the tree twice
*/
int lin[2 * MAX + 1];


/*
depth[node] = distance from the root (node 1)

important invariant:
depth increases by exactly 1 when moving from parent → child
*/
int depth[MAX + 1];


/*
pre[node] = first time node appears in euler tour
post[node] = last time node appears in euler tour

important invariant:
pre[node] <= pre[child] <= post[child] <= post[node]
so each subtree corresponds to a contiguous segment in the euler tour
*/
int pre[MAX + 1];
int post[MAX + 1];


// global timer for euler tour
int t = 0;

int n;


/*
sparse table

dp[i][j] stores the node with minimum depth in the euler tour
range:

[j , j + 2^i - 1]

important invariant:

dp[i][j] = argmin depth in the segment

lin[j ... j + 2^i - 1]
*/
int dp[LOG + 1][2 * MAX + 1];



/*
build sparse table over the euler tour

the sparse table answers:

rmq over depth along the euler tour
*/
void build() {

	int len = 2 * n; 
	// length of the euler tour (≈ 2*n-1)

	/*
	base case

	interval length = 1
	the minimum node in a single element interval is the element itself
	*/
	for (int i = 1; i <= len; i++)
		dp[0][i] = lin[i];


	/*
	build larger intervals

	interval size = 2^i

	observation:
	a segment of size 2^i can be split into two segments of size 2^(i-1)

	[j ...................... j + 2^i - 1]
	[j ......] [......]
	 2^(i-1)    2^(i-1)
	*/
	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j <= len; j++) {

			// assume left half contains minimum
			dp[i][j] = dp[i - 1][j];

			if (j + (1ll << (i - 1)) <= len) {

				int d1 = depth[dp[i - 1][j]];
				int d2 = depth[dp[i - 1][j + (1ll << (i - 1))]];

				// keep the node with smaller depth
				if (d2 < d1)
					dp[i][j] = dp[i - 1][j + (1ll << (i - 1))];
			}
		}
}



/*
core theorem used for lca:

let

first(u) = first occurrence of u in the euler tour
first(v) = first occurrence of v in the euler tour

then

LCA(u,v) = node with minimum depth in the euler tour segment

[first(u) , first(v)]

(assuming first(u) <= first(v))


why this is true:

consider the path taken by dfs from u to v in the euler tour.

when dfs moves from u toward v,
it must climb up the tree until reaching the lowest common ancestor,
then descend toward v.

so along the euler tour between these two occurrences:

depth decreases while climbing toward lca
depth reaches its minimum exactly at the lca
depth then increases while descending toward v

so the minimum depth node in this interval must be the lca.
*/
int lca(int u, int v) {

	// ensure u appears earlier in the euler tour
	if (pre[u] > pre[v]) swap(u, v);

	int l = pre[u];
	int r = pre[v];

	int len = r - l + 1;

	/*
	find largest power of two ≤ len
	*/
	int k = 63 - __builtin_clzll(len);

	/*
	we cover the interval using two overlapping segments

	[l ............... r]

	[l .........]
	          [......... r]

	both length = 2^k

	this works because the operation is min
	and min is idempotent
	*/
	int one = dp[k][l];
	int two = dp[k][r - (1ll << k) + 1];

	if (depth[one] < depth[two]) return one;
	return two;
}



/*
dfs builds the euler tour
*/
void dfs(int node, int parent) {

	/*
	enter node
	*/
	++t;
	pre[node] = t;
	lin[t] = node;

	/*
	invariant after this line:

	lin[t] = node
	pre[node] = t
	*/

	for (int v : graph[node])
		if (v != parent) {

			/*
			update depth for child
			*/
			depth[v] = depth[node] + 1;

			dfs(v, node);

			/*
			when returning from the child
			we record the parent again

			this step is crucial because it records
			the upward movement in the tree
			*/
			++t;
			lin[t] = node;
		}

	post[node] = t;
}



/*
program entry
*/
int32_t main() {

	cin >> n;

	int u, v;

	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v,
		graph[u].push_back(v),
		graph[v].push_back(u);

	/*
	root the tree at node 1
	*/
	depth[1] = 0;

	dfs(1, -1);

	build();

	return 0;
}