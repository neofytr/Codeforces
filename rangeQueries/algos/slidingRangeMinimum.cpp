#include <bits/stdc++.h>
using namespace std;

// Let n, k >= 1
// Suppose you have a sequence of values v[1, n]

// Suppose, at each step i, starting from 1 and reaching till k, you want
// min { v[j] + f(j) | L(i) <= j <= R(i)}
// , where, 
// 1. R(i) increases by exactly 1 as i increases by 1
// 2. L(i) never decreases as i increases
// 3. f(j) is a function of j only and does not depend on i

// This is the sliding window minimum problem
// We solve this using a monotonic deque that maintains the following invariants
// during each step:

// 1. The deque's front doesn't have any expired indices (i.e., indices not in the current window)
// 2. The deque is sorted (in non-decreasing order) from front to the back according
//	  to the value of (v + f) at the index in the deque

// This ensures that the front of the deque contains the index of the minimum of (v + f) inside the 
// current window

deque<int> dq;
for (int i = 1; i <= k; i++) {	
	int right = R(i);
	int left = L(i);

	// insert first
	while (!dq.empty() && (v[dq.back()] + f(dq.back())) >= v[right] + f(right))
		dq.pop_back();
	dq.push_back(right);

	// delete expired elements later
	while (!dq.empty() && dq.front() < left)
		dq.pop_front();

	if (!dq.empty()) {
		int mIdx = dq.front();
		int mVal = v[mIdx] + f(mIdx); // minimum of the window at step i 
	}
}