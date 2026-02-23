#include <bits/stdc++.h>
using namespace std;

// we redefine int to long long so that m*x+c does not overflow
// this is purely for safety and does not affect the algorithm
#define int long long

// the x-domain is fixed and known in advance
// the li chao tree is built over x in [LEFT, RIGHT]
#define LEFT 0
#define RIGHT (int)(2 * 1e5)

// this represents "no line"
// it must be much larger than any possible m*x+c value
#define INF (int)(1e17)

// a line is represented as y = m*x + c
// first  -> slope (m)
// second -> intercept (c)
typedef pair<int, int> Line;

// segment tree array
// IMPORTANT: this is a segment tree over x-values
// each node corresponds to some interval [l, r]
// each node stores EXACTLY ONE line
Line tree[4 * RIGHT + 1];


// evaluates a line at a given x
// this is the only operation we ever perform on lines
int val(const Line &l, int x) {
	return l.first * x + l.second;
}


// initializes the segment tree
// every node initially stores "no line"
// this means: no line has reached this node yet
void init(int l = LEFT, int r = RIGHT, int idx = 1) {
	tree[idx] = {INF, INF};

	// if this is a leaf, stop
	if (l == r) return;

	int m = (l + r) >> 1;

	// recursively initialize children
	init(l, m, idx << 1);
	init(m + 1, r, (idx << 1) | 1);
}


/*
	insert(L, l, r, idx)

	what this function does conceptually:

	- we are inserting a line L into the li chao tree
	- the node idx corresponds to x-interval [l, r]
	- the midpoint of this interval is mid = (l+r)/2

	CRITICAL INVARIANT (this is the heart of li chao tree):

		for every node representing [l, r],
		tree[idx] stores the line which is MINIMUM at mid
		among all lines that were ever passed into this node.

	"passed into this node" means:
	- insertion recursion actually reached this node with that line
	- not all lines in the structure, only those that were not discarded earlier
*/
void insert(Line L, int l = LEFT, int r = RIGHT, int idx = 1) {

	// if no line has ever reached this node before,
	// then L is trivially the best line here
	// the invariant is immediately satisfied
	if (tree[idx].first == INF) {
		tree[idx] = L;
		return;
	}

	// midpoint of the current interval
	int m = (l + r) >> 1;

	/*
		we compare the incoming line L with the stored line at mid

		WHY mid?

		because the invariant is defined at mid:
		the node MUST store the line that is best at mid

		if L is better at mid, then the stored line is wrong
		and must be replaced
	*/
	bool mid = (val(L, m) < val(tree[idx], m));
	if (mid) swap(L, tree[idx]);

	/*
		after this point, VERY IMPORTANT FACT:

		- tree[idx] is guaranteed to be the best line at mid
		- L is guaranteed to be worse at mid

		this is now true regardless of whether a swap happened or not
	*/

	// if this is a leaf [x, x],
	// then mid == l == r == x
	// since the stored line is best at this x,
	// no further action is needed
	if (l == r) return;

	/*
		now we must decide what to do with the worse line L

		KEY GEOMETRIC FACT:
		two lines intersect at most once

		since L is worse at mid, it can only be better:
		- either somewhere in [l, m]
		- or somewhere in [m+1, r]
		- or nowhere at all

		it is IMPOSSIBLE for L to be better on both sides
	*/

	// check if L is better at the left endpoint l
	// if yes, then the intersection lies in [l, m]
	// so L may still be useful in the left child
	if (val(L, l) < val(tree[idx], l)) {
		insert(L, l, m, idx << 1);
	}
	// otherwise, check if L is better at the right endpoint r
	// if yes, then the intersection lies in [m+1, r]
	// so L may still be useful in the right child
	else if (val(L, r) < val(tree[idx], r)) {
		insert(L, m + 1, r, (idx << 1) | 1);
	}
	/*
		else:
		- L is worse at l
		- L is worse at mid
		- L is worse at r

		since two lines can intersect at most once,
		this implies L is worse EVERYWHERE in [l, r]

		therefore, L can NEVER be the minimum for any x in this interval
		and it is SAFE to discard it completely

		this is what keeps the structure efficient
	*/
}


/*
	query(x, l, r, idx)

	goal:
		find the minimum value among ALL inserted lines at x

	HOW QUERY WORKS (this is the subtle part):

	- we walk from the root down to the leaf [x, x]
	- at every node on this path, we evaluate the line stored there
	- we return the minimum of all these evaluations

	WHY THIS IS CORRECT:

	any line that can possibly be optimal at x is GUARANTEED
	to be stored at SOME node on this path

	this guarantee is a direct consequence of how insertion works
*/
int query(int x, int l = LEFT, int r = RIGHT, int idx = 1) {

	// if no line ever reached this node,
	// it contributes nothing to the answer
	if (tree[idx].first == INF) return INF;

	/*
		evaluate the line stored at this node at x

		NOTE:
		this line may or may not be the global minimum at x
		it is only guaranteed to be minimum at THIS NODE'S midpoint
	*/
	int res = val(tree[idx], x);

	// if this is the leaf [x, x],
	// then this node is the last possible place where a relevant line could exist
	if (l == r) return res;

	int m = (l + r) >> 1;

	/*
		now we recurse into exactly one child:
		the one whose interval contains x

		WHY THIS IS ENOUGH:

		consider the true minimum line L* at x

		during insertion of L*:
		- at each node, either L* was stored there
		- or it was worse at mid and pushed into the ONLY child
		  where it could still possibly beat the stored line

		crucially, L* is NEVER pushed away from the side that contains x

		therefore, L* must appear at SOME node along this path
		from root to leaf [x, x]

		by checking all nodes on this path, we are guaranteed to see L*
	*/
	if (x <= m)
		return min(res, query(x, l, m, idx << 1));
	else
		return min(res, query(x, m + 1, r, (idx << 1) | 1));
}