#include <bits/stdc++.h>
using namespace std;

#define int long long
#define X 0
#define Y (int)(1e9)

// Binary Search M1

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