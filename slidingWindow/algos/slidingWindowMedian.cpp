#include <bits/stdc++.h>
using namespace std;

#define int long long

// We need to find the median of every sliding window in an array efficiently
// Challenge ->
// 1. Sorting the window at each step is too slow (O(k log k) for each window).
// 2. We need a structure that supports fast insertion, fast deletions, and fast median retrieval.

// We split the window into two parts
// 1. Lower half (lo) -> contains the smaller elements
// 2. Upper half (hi) -> contains the larget elements

// This split lets us quickly access the median because in sorted order, the median is either the middle element (for
// odd window size) or the smaller of the two central elements (for even window size).
// By always ensuring that ->
// 1. size(lo) >= size(hi)
// 2. size(lo) - size(hi) <= 1
// 2. each element of lo <= each element of hi
// 3. lo and hi are themselves sorted
// the median can be directly accessed from the top of lo, since
// the sum of the sizes of lo and hi is a constant (k)

multiset<int> lo, hi;

// Balance the sets:
// If lo is too large (lo.size() > hi.size() + 1), we move the largest element from lo to hi.
// If hi is larger (lo.size() < hi.size()), we move the smallest element from hi to lo.
void balance() {
    if (hi.size() > lo.size()) {
        const int elt = *hi.begin();
        hi.erase(hi.begin());
        lo.insert(elt);
    }
    if (lo.size() > hi.size() + 1) {
        const int elt = *lo.rbegin();
        lo.erase(lo.find(elt));
        hi.insert(elt);
    }
}

// When we insert a new number x into the window, we decide where it should go.
// If lo is empty, x goes into lo.
// Otherwise, we compare x with the current median ->
// 1. If x > current median, x goes into hi
// 2. Otherwise, x goes into lo
// We then balance both the sets
void insert(const int x) {
    if (lo.empty() || x > *lo.rbegin())
        hi.insert(x);
    else
        lo.insert(x);
    balance();
}

// When an element slides out the window, we need to remove it.
// We simply find where it belongs and remove one instance of it, and then balance the tree.
// If that element is in both the sets, it doesn't matter from which we delete the element, since balance will
// take care of maintaining the invariant.
void erase(const int x) {
    if (lo.contains(x))
        lo.erase(x);
    else
        hi.erase(x);
    balance();
}