#include <bits/stdc++.h>
using namespace std;

#define int long long
#define X 0
#define Y (int)(1e9)

// Binary Search Methods

// x and y are integers such y >= x
// The search space is [x, y]

int left = X; // initialize with the minimum value in the search space
int right = Y; // initialize with the maximum value in the search space

// Its guaranteed that one of the following two is true:
// 1. f(r) = T for all r in [x, y]
// 2. y > x and there is a k in [x, y] such that
//    f(r) = T for all x <= r <= k and f(r) = F for all y >= r > k
// 3. f(r) = F for all r in [x, y]

// We are to find the last T
while (left < right) {
	int mid = (left + right + 1) / 2;

	if (f(mid))
		left = mid; // due to left being "unchanging", if we do floor division here and only two elements are left,
					// the search won't ever terminate
	else 
		right = mid - 1;
}
// if (f(left) == T) left contains the first T
// otherwise, there is no T in the search space

// We are to find the first F
while (left < right) {
	int mid = (left + right) / 2;

	if (f(mid))
		left = mid + 1;
	else 
		right = mid; // due to right being "unchanging", if we do ceil division here, and only two elements are left in the search space
					// the search won't ever terminate
}
// if (f(right) == F) right contains the first F
// otherwise, there is no F in the search space

// left <= (left + right) / 2 < right since its floor division and the equality holds when right = left + 1
// left < (left + right + 1) / 2 <= right since its ceil division and the equality holds when right = left + 1

// During each iteration of the while loop of the binary search, we should reduce the search space by atleast one

// In the first binary search, we do either left = mid or right = mid - 1
// The latter case reduces the search space by 1 always
// Let mid = (left + right) / 2
// Now left <= mid < right since left < right
// The equality holds iff right = left + 1
// So, if right = left + 1, the case left = mid doesn't reduce the search space, resulting in an infinite loop
// So, we should do mid = (left + right + 1) / 2 since then
// left < mid <= right since left < right and both the cases (left = mid and right = mid - 1) reduce the
// search space by atleast 1

// In the second binary search, we do either left = mid + 1 or right = mid.
// The first case (left = mid + 1) always reduces the search space by at least 1.
// Let mid = (left + right + 1) / 2 (i.e., ceiling division).
// Then left < mid <= right since left < right.
// If right = left + 1, the case right = mid does not reduce the search space,
// because mid becomes equal to right, causing left and right to remain unchanged, leading to an infinite loop.
// Hence, we should use floor division mid = (left + right) / 2,
// because then left <= mid < right, ensuring that both cases
// (left = mid + 1 and right = mid) reduce the search space by at least one on every iteration.

// Floor (left) or ceiling (right): Should lean towards the "changing" side (rule of thumb)

int ans = -1; // a value that is not in the search space

// Find the last T
while (left <= right) {
	int mid = (left + right) / 2;

	if (f(mid)) {
		ans = mid;
		left = mid + 1;
	} else {
		right = mid - 1;
	}
}
if (ans != -1) // ans contains the last T
else // all the elements in the search space are F

// Find the first F
while (left <= right) {
	int mid = (left + right) / 2;

	if (f(mid)) {
		left = mid + 1;
	} else {
		ans = mid;
		right = mid - 1;
	}
}
if (ans != -1) // ans contains the first F
else // all the elements of the search space are T

// No element is checked in the range [left, right] at the beginning of each iteration - (1) (this is because, when we check an element, we ensure to remove it from the next search space)
// Here, left <= right as left < right would skip checking the last element
// When right = left + 1 and we move the left pointer forward, we get right = left and we exit
// and we never check the last element right = left (right is never checked due to (1) being true in the last iteration)
// Similarly, when right = left + 1 and we move the right pointer backward, we get right = left and we
// exit and we never check the last element right = left (left is never checked due to (1) being true in the last iteration)

// Best Binary Search Implementation

// We define f(x - 1) = T and f(y + 1) = F (this maintains the monotonicity of f)
// We ensure right > left + 1 initially, and the iteration stops as soon as right = left + 1
// We ensure that f(left) = T and f(right) = F at the beginning of each iteration (invariant)

left = X - 1; // initialize left with one less than the minimum value in the search space
right = Y + 1; // initialize right with one more than the maximum value in the search space

while (right > left + 1) {
	int mid = left + (right - left) / 2; // this is simply floor((left + right) / 2)

	// Since right > left + 1, we have
	// left < mid < right
	// So, in both of the following cases, we reduce the search space by atleast one (so the algorithm terminates after a finite number of iterations)
	// The search terminates as soon as right = left + 1
	if (f(mid))
		left = mid;
	else
		right = mid;
	// The above assignments ensure that our invariant holds
}

// loop exits when right = left + 1
// Let m = left

// f(m) = T and f(m + 1) = F
// Thus, by the monotonicity of f, f(r) = T for all x <= r <= m and f(r) = F for all y >= r >= m + 1
// Thus, left is the last true and right is the first false

// For binary search on real numbers, the number of iterations k is given by
// k = log2((max - min) / e) + 1
// where max is the maximum value taken by right pointer, min is the minimum value taken by left pointer
// and e is the required precision

// Also, do setprecision(24) before couting the answer
// Also, use #define double long double