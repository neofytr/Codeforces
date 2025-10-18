#include <bits/stdc++.h>
using namespace std;

#define int long long 

int n;
unordered_map<int, int> mp;
int query(int idx) {
	if (mp.contains(idx))
		return mp[idx];

	if (!idx || idx == n + 1)
		return LLONG_MAX;

	int val;
	cout << "? " << idx << endl;
	cin >> val;
	return mp[idx] = val; 
}

int32_t main() {
	cin >> n;

	// In any array [+INF, a1, ..., an, +INF], there is always a local minima in the
	// range [1, n]

	// We always maintain the invariant that there is a local minima 
	// of the array in the range [left, right]

	int left = 1;
	int right = n; // There is a local minima in the range [left, right] initially

	while (left < right) {
		int mid = left + (right - left) / 2;
    	int vmid = query(mid);
    	int vright = query(mid + 1);

		if (vmid < vright) {
			// Assuming there was a local minima in the range [left, right], then
			// in this case, there is always a local minima of the array in the
			// range [left, mid]

			// Assume there is no local minima in the range [left, mid]
			// Then, since arr[mid] < arr[mid + 1], it follows that
			// arr[left] < .. < arr[mid]

			// Now, either left = 1 or it has been set to left = mid' + 1 in 
			// some earlier iteration

			// If left = 1, we have a contradiction since left is a local minima
			// as arr[0] > arr[left] < arr[left + 1] (left + 1 exists because left < right)

			// Let left = mid' + 1 in some previous iteration
			// For this to occur, arr[mid'] > arr[mid' + 1] in that iteration
			// Thus arr[left - 1] > arr[left] < arr[left + 1] (left - 1 >= 1 since left != 1)
			// Thus, we have a contradiction
			right = mid;
		} else {
			// Assuming there was a local minima in the range [left, right], then,
			// in this case, there is always a local minima of the array in the range 
			// [mid + 1, right]

			// Assume there is no local minima of the array in [mid + 1, right]
			// Thus since arr[mid] > arr[mid + 1], it follows that
			// arr[mid] > arr[mid + 1] > .. > arr[right]

			// Either right = n or it has been put to right = mid' in some previous iteration
			// If right = n, we have a contradiction since then right is a local minima
			// Let right = mid' in some previous iteration

			// For this to occur, in that iteration, arr[mid'] < arr[mid' + 1], i.e,
			// arr[right - 1] > arr[right] < arr[right + 1], and thus right is a local minima and we have a contradiction
			// (right + 1 exists since right != n and right - 1 exists since right > left)
			left = mid + 1;
		}
	}

	cout << "! " << left << endl;
	return 0;
}

// -----------------------------------------------------------------------------
// PROOF OF TERMINATION
// -----------------------------------------------------------------------------
//
// We start with an interval [left, right] such that left < right.
// The loop condition is: while (left < right)
//
// Each iteration computes:
//     mid = left + (right - left) / 2
//
// -----------------------------------------------------------------------------
// 1. Property of mid:
// -----------------------------------------------------------------------------
// Since (right - left) / 2 is an integer division (truncated toward zero),
// we always have:
//
//      left <= mid < right
//
// Proof:
//   - (right - left) / 2 >= 0        ⇒ mid >= left
//   - (right - left) / 2 < (right - left) ⇒ mid < right
//
// Therefore, mid always lies strictly between left and right.
//
// -----------------------------------------------------------------------------
// 2. Invariant: There exists at least one valid answer in [left, right].
// -----------------------------------------------------------------------------
// We assume this invariant is true initially, and in every iteration,
// we update either left or right such that this property remains true.
// That is, we always keep at least one valid answer inside the interval.
//
// -----------------------------------------------------------------------------
// 3. Shrinking the interval:
// -----------------------------------------------------------------------------
// In each iteration, we perform one of the following updates:
//
//   Case A: right = mid
//       Since mid < right, the interval strictly shrinks on the right side.
//
//   Case B: left = mid + 1
//       Since mid >= left, mid + 1 <= right, the interval strictly shrinks
//       on the left side.
//
// Therefore, in both cases, (right - left) strictly decreases.
//
// -----------------------------------------------------------------------------
// 4. Progress guarantee (Termination proof):
// -----------------------------------------------------------------------------
// Let Δ = right - left  (the length of the current search interval).
//
// Initially, Δ = R - L > 0.
// Each iteration strictly reduces Δ since either left increases
// or right decreases.
//
// Because Δ is a nonnegative integer that decreases monotonically,
// it can only decrease a finite number of times before it becomes 0.
//
// When Δ = 0 ⇒ right - left = 0 ⇒ left == right.
//
// At this point, the loop condition (left < right) fails,
// and the binary search terminates.
//
// -----------------------------------------------------------------------------
// 5. Correctness at termination:
// -----------------------------------------------------------------------------
// By our invariant, the interval [left, right] always contains at least one
// valid answer. When left == right, this interval contains exactly one element,
// which must be the desired answer.
//
// -----------------------------------------------------------------------------
// Therefore:
//     - The invariant (a valid answer exists in [left, right]) holds throughout.
//     - The interval length strictly decreases each iteration.
//     - The loop terminates when and only when left == right.
//     - The final left (== right) corresponds to a valid solution.
// -----------------------------------------------------------------------------


