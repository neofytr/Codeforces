/*
===============================================================================
GENERIC BINARY HEAP
===============================================================================

OVERVIEW
--------
This file implements a fully generic binary heap using:
- a template type T
- a user-provided comparator Compare

The heap is implemented as an ARRAY-BASED COMPLETE BINARY TREE
using 1-indexing for clean parent/child arithmetic.

This is a *fundamental* data structure that supports:
- insertion in O(log n)
- removal of the top element in O(log n)
- access to the top element in O(1)
- construction from an array in O(n)

-------------------------------------------------------------------------------
WHAT IS A BINARY HEAP?
-------------------------------------------------------------------------------

A binary heap is defined by two properties:

1) STRUCTURAL PROPERTY (complete binary tree)
   - all levels are fully filled except possibly the last
   - last level is filled from left to right
   - this guarantees height = O(log n)

2) HEAP INVARIANT (ordering property)
   - defined using a comparator
   - for every node i > 1:
         parent(i) is NOT worse than i

   Formally, if cmp(a, b) means "a is worse than b", then:
         cmp(parent(i), i) == false

   Examples:
   - max heap:
         cmp(a, b) = (a < b)
         invariant => parent >= child
   - min heap:
         cmp(a, b) = (a > b)
         invariant => parent <= child

Everything in this implementation exists solely to maintain this invariant.

-------------------------------------------------------------------------------
ARRAY REPRESENTATION 
-------------------------------------------------------------------------------

We store the heap in a vector v using 1-based indexing.

Index relationships:
- parent(i)     = i / 2
- left child    = 2 * i
- right child   = 2 * i + 1

Very important observation:
- nodes with indices in range [n/2 + 1, n] are LEAVES
- reason: smallest index that can have a child satisfies 2*i <= n
          => i <= n/2

This observation is the key to O(n) heap construction.

-------------------------------------------------------------------------------
HEAP INVARIANT (THE CORE RULE)
-------------------------------------------------------------------------------

For every node i > 1:

    cmp(v[parent(i)], v[i]) == false

Meaning:
- the parent is not worse than the child
- the "best" element according to comparator is always at the root

If this invariant holds everywhere, the structure is a valid heap.

-------------------------------------------------------------------------------
WHY INSERT IS O(log n)
-------------------------------------------------------------------------------

Insertion steps:
1) append the new element at the end of the array
   - preserves completeness of the tree
2) only the path from the new node to the root can violate the invariant
3) repeatedly compare the node with its parent
4) swap upward while invariant is broken

Each swap moves one level up.
Maximum height = O(log n).
Therefore insertion is O(log n).

This process is called "sift-up".

-------------------------------------------------------------------------------
WHY REMOVE-TOP IS O(log n)
-------------------------------------------------------------------------------

Removal steps:
1) swap the root with the last element
2) remove the last element
3) only the root may now violate the invariant
4) repeatedly swap downward with the best child

Each swap moves one level down.
Maximum height = O(log n).
Therefore removal is O(log n).

This process is called "sift-down" or "heapify".

-------------------------------------------------------------------------------
WHY BUILD-HEAP IS O(n)
-------------------------------------------------------------------------------

Heap construction from an array works as follows:

- nodes from indices [n/2 + 1, n] are leaves
- leaves already satisfy the heap invariant
- we only need to heapify nodes from n/2 down to 1

Cost analysis:
- nodes near the bottom have very small height
- only the root has height O(log n)
- total work is the sum of heights of all nodes
- this sum is O(n), NOT O(n log n)

This is a classic amortized analysis result.

-------------------------------------------------------------------------------
COMPARATOR REQUIREMENTS
-------------------------------------------------------------------------------

The comparator Compare must satisfy:

- strict weak ordering
- transitivity
- consistency
- irreflexivity: cmp(x, x) == false

Interpretation:
- cmp(a, b) returns true if a is WORSE than b
- "better" elements rise toward the root

If these properties are violated, heap behavior is undefined.

-------------------------------------------------------------------------------
FUNCTION-BY-FUNCTION LOGIC
-------------------------------------------------------------------------------

heapify(r):
- assumes left and right subtrees of r are already heaps
- finds the best among r and its children
- swaps once if needed
- continues downward
- restores invariant globally

insert(x):
- append x
- sift upward
- restores invariant along insertion path

top():
- returns root
- root is always the best element by invariant

pop():
- swap root with last
- remove last
- heapify from root

-------------------------------------------------------------------------------
MENTAL MODEL
-------------------------------------------------------------------------------

- heap is not fully sorted
- only parent-child relationships matter
- the root is special: it is always optimal
- updates only affect a single root-to-leaf path

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Compare>
struct Heap {
	int n;
	vector<T> v;
	Compare cmp;

	Heap() : n(0) {
		v.resize(1); // 1-indexed
	}

	Heap(int sz, vector<T> &arr) : n(sz) {
		v.resize(n + 1);
		for (int i = 1; i <= n; i++)
			v[i] = arr[i];

		for (int i = n / 2; i >= 1; i--)
			heapify(i);
	}

	void heapify(int r) {
		while (true) {
			int best = r;
			int l = 2 * r;
			int rr = 2 * r + 1;

			if (l <= n && cmp(v[best], v[l]))
				best = l;
			if (rr <= n && cmp(v[best], v[rr]))
				best = rr;

			if (best == r) break;

			swap(v[r], v[best]);
			r = best;
		}
	}

	void insert(const T &x) {
		v.push_back(x);
		n++;

		int i = n;
		while (i > 1 && cmp(v[i / 2], v[i])) {
			swap(v[i], v[i / 2]);
			i /= 2;
		}
	}

	const T& top() const {
		if (!n)
			throw runtime_error("heap is empty");
		return v[1];
	}

	void pop() {
		if (n == 0) return;

		swap(v[1], v[n]);
		v.pop_back();
		n--;

		if (n > 0)
			heapify(1);
	}

	bool empty() const {
		return n == 0;
	}

	int size() const {
		return n;
	}
};