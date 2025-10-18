#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Let n ≥ 2.
// Let S = {a₁, a₂, ..., aₙ} be a finite totally ordered set, 
// where a₁ < a₂ < ... < aₙ. 
//
// Define a function f: S → {0, 1}.
//
// We assume f is *monotone non-decreasing* on S, i.e.,
// ∀ i, j ∈ {1, ..., n},  if aᵢ < aⱼ  ⇒  f(aᵢ) ≤ f(aⱼ).
//
// In words: once f(x) attains the value 1, it remains 1 for all larger elements.
//
// ---------------------------------------------------------------------------
// Structural Properties of f
// ---------------------------------------------------------------------------
//
// If there exist indices r, s ∈ {1, ..., n} such that f(a_r) = 0 and f(a_s) = 1, 
// then by monotonicity we must have:
//
// (1) r < s
//
// (2) There exists an index k with r ≤ k < s such that
//        - f(a_x) = 0 for all r ≤ x ≤ k
//        - f(a_x) = 1 for all k < x ≤ s
//     i.e. aₖ marks the *last zero region* before the transition.
//
// (3) Equivalently, there exists k with r < k ≤ s such that
//        - f(a_x) = 0 for all r ≤ x < k
//        - f(a_x) = 1 for all k ≤ x ≤ s
//     i.e. aₖ marks the *first one region* after the transition.
//
// ---------------------------------------------------------------------------
// Hence, there are exactly three mutually exclusive possibilities for f:
//
// (a) f(aᵢ) = 0  ∀ i  (f is identically zero)
// (b) f(aᵢ) = 1  ∀ i  (f is identically one)
// (c) There exists a unique index 1 ≤ r < n such that
//        - f(aᵢ) = 0 for all 1 ≤ i ≤ r
//        - f(aᵢ) = 1 for all r < i ≤ n
//
// In case (c), a_r is the *last zero element* and a_{r+1} is the *first one element*.
//
// The principal computational problem is to locate this boundary efficiently.
//
// ---------------------------------------------------------------------------
// Binary Search Template (General Form)
// ---------------------------------------------------------------------------
//
// Suppose f is monotone on S and we wish to find the *least* element x ∈ S 
// such that f(x) = 1, i.e.
//         x* = min { aᵢ ∈ S | f(aᵢ) = 1 }.
//
// If no such x exists, then f is identically 0.
// If every x satisfies f(x) = 1, then f is identically 1.
//
// Otherwise, there exists a unique x* as described above, 
// and binary search finds it in O(log n) queries to f.
//

bool func(int x) {
    // Example monotone function (replace as needed)
    // For instance, suppose S = {1, 2, ..., n} and threshold = 7
    // Then f(x) = [x >= 7].
    return x >= 7;
}

void bin() {
    // Suppose S = {a₁, a₂, ..., aₙ} is sorted in increasing order.
    // We maintain two "virtual" boundaries L and R satisfying:
    //     f(L) = 0 (known false side)
    //     f(R) = 1 (known true side)
    //
    // The invariant preserved:
    //     f(L) = 0 and f(R) = 1,
    // and the transition (the first 1) always lies in the open interval (L, R].
    //
    // At termination, R = L + 1, and thus R identifies the first aᵢ such that f(aᵢ) = 1.

    int L = 0;   // Left boundary (could represent a₀, fictitious, where f(a₀)=0)
    int R = 10;  // Right boundary (could represent aₙ₊₁, fictitious, where f(aₙ₊₁)=1)

    while (R != L + 1) {
        int mid = L + (R - L) / 2;  // Midpoint respecting integer domain

        if (func(mid))
            R = mid;   // The transition lies at or before mid
        else
            L = mid;   // The transition lies strictly after mid
    }

    // Upon termination, R is the least x such that f(x) = 1.
    cout << "Boundary element a* = " << R << "\n";
}

int32_t main() {
    bin();
}

// Another, sometimes better (if a predicate isn't immediately obvious) way to do binary search
//
// Suppose you want to find some value satisfying some property P in an array or over an integer range.
//
// The key idea is to **maintain an invariant** — a statement that is always true about the current search interval [left, right].
// Typically, the invariant is that "there exists at least one valid answer (an index or value satisfying P) within [left, right]".
//
// Then, in each iteration, you pick a midpoint, use information from it to decide which half
// of the interval still *must* contain at least one valid answer, and discard the other half.
// This process continues until the interval becomes a single element, which by the invariant, must be a valid answer.
//
// Maintaining the invariant while halving the search space is the central principle here.
//
// -------------------------------------------------------------
// General Format:
// -------------------------------------------------------------
//
// 1. Define your invariant clearly:
//    "There exists at least one valid index/value in [left, right]."
//
// 2. Initialize [left, right] so that the invariant is true initially.
//
// 3. While (left < right):
//        mid = left + (right - left) / 2
//        if (some condition based on P(mid)) {
//            // The right half still satisfies the invariant
//            left = mid + 1;        // or left = mid, depending on the logic
//        } else {
//            // The left half still satisfies the invariant
//            right = mid;           // or right = mid - 1, depending on the logic
//        }
//
// 4. When the loop terminates (left == right), by the invariant,
//    [left, right] contains exactly one element, which must satisfy P.
//
// 5. Return or output 'left' (or the corresponding value).
//
// -------------------------------------------------------------
// Example: Finding a local minima
// -------------------------------------------------------------
//
//   - In the array [+∞, a1, a2, ..., an, +∞], there is always at least one local minima.
//   - So the invariant is: "There exists a local minima in [left, right]".
//   - We start with left = 1, right = n.
//   - Depending on whether arr[mid] > arr[mid + 1] or arr[mid] < arr[mid + 1],
//     we shrink the interval to [left, mid] or [mid + 1, right] respectively,
//     while preserving the invariant.
//   - Eventually, left == right, which must be a local minima.


// General template in code form:

int binary_search_with_invariant(int left, int right) {
    // Invariant: There exists at least one valid answer in [left, right]
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (/* condition showing the answer lies in the right half */) {
            left = mid + 1;
        } else {
            right = mid;  // Invariant still true in this subrange
        }
    }
    return left;  // or right — both are equal here
}

// A good example of this type of binary search usage:
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