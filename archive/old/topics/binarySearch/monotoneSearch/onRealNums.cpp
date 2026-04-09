#include <bits/stdc++.h>
using namespace std;

// rope cutting problem using binary search — full explanation

// problem statement:
// you are given n ropes, with lengths a₁, a₂, ..., aₙ
// you must cut exactly k pieces of the same length
// find the maximum possible length of each piece

// how to model the problem:
// - model it with a function isGood(x)
// - isGood(x) returns true if we can cut at least k pieces of length x
// - otherwise, it returns false
// - very important: isGood(x) is monotonic
//   - if isGood(x) is true, then isGood(y) is true for all y ≤ x
//   - if isGood(x) is false, then isGood(y) is false for all y ≥ x
// - this monotonicity allows us to use binary search

// binary search approach:
// 1. initialize search boundaries
//    - left = 0 (pieces can't have negative length)
//    - right = maximum rope length (can't cut longer pieces than this)
// 2. binary search loop:
//    - calculate mid = (left + right) / 2
//    - if isGood(mid) is true:
//        move left = mid (try larger pieces)
//    - else:
//        move right = mid (try smaller pieces)
// 3. termination:
//    - since real numbers are continuous, there is no "next" number
//    - stop when (right - left) < eps, where eps is a very small number like 1e-7
//    - alternatively, use a fixed number of iterations to guarantee termination

// floating-point issues:
// - computers represent real numbers with finite precision (like double)
// - rounding errors occur
// - mid can become exactly left or right when they are very close
// - this can cause infinite loops if termination is not handled properly

// how to avoid floating-point problems:
// - use a precision threshold eps (e.g., 1e-7)
// - use a fixed number of iterations (e.g., 100 iterations)
// - never compare floating-point numbers using ==
// - instead, use abs(a - b) < eps

// complexity analysis:

// time complexity:
// - in each iteration, binary search halves the interval
// - number of iterations needed = log2((initial right - initial left) / eps)
// - in each iteration, we run isGood(x) which takes O(n) time
// - total time = O(n * log2(maxRope / eps))

// space complexity:
// - storing the ropes array takes O(n) space
// - no extra significant memory used

// maximum number of iterations needed:
// - after each iteration, interval size becomes (1/2)^k of initial size
// - we want (1/2)^k < eps / initial size
// - taking log base 2:
//   k > log2(initial size / eps)
// - example:
//   if initial size = 10^4 and eps = 10^-6
//   log2(10^10) ≈ 33
// - so about 33–40 iterations are enough
// - running 100 iterations is very safe

// practical tips:
// - print enough decimal places when outputting the answer
// - be careful about off-by-one mistakes
// - debug by printing left, right, mid at each step if needed
// - always test on edge cases: single rope, large values, small values

// now we will implement the solution

// function to check if we can cut at least k pieces of length x
bool canCut(const vector<double> &ropes, int k, double x) {
    // if length x is non-positive, it is invalid
    if (x <= 0) return false;

    int pieces = 0; // total pieces we can cut

    // iterate through all ropes
    for (double rope: ropes) {
        // number of pieces from this rope = floor(rope / x)
        pieces += static_cast<int>(rope / x);

        // optimization: if already enough pieces, return early
        if (pieces >= k) return true;
    }

    // after checking all ropes, return whether we have at least k pieces
    return pieces >= k;
}

// function to solve the rope cutting problem
double solveRopeCutting(const vector<double> &ropes, int k, double eps = 1e-7) {
    // edge case: if no pieces are needed
    if (k == 0) return 0;

    // find maximum rope length
    double maxRope = 0;
    for (double rope: ropes) {
        maxRope = max(maxRope, rope);
    }

    double left = 0; // minimum possible length
    double right = maxRope; // maximum possible length

    // binary search loop
    for (int iteration = 0; iteration < 100; iteration++) {
        double mid = left + (right - left) / 2; // calculate mid carefully

        if (canCut(ropes, k, mid)) {
            // if we can cut, try to increase the piece length
            left = mid;
        } else {
            // if we cannot cut, decrease the piece length
            right = mid;
        }

        // optional early termination if desired precision is reached
        if (right - left < eps) {
            break;
        }
    }

    // after binary search, left will contain the answer
    return left;
}

int main() {
    // input the number of ropes
    int n;
    cout << "enter number of ropes: ";
    cin >> n;

    vector<double> ropes(n); // array to store rope lengths

    cout << "enter rope lengths: ";
    for (int i = 0; i < n; i++) {
        cin >> ropes[i];
    }

    // input the number of pieces needed
    int k;
    cout << "enter number of pieces needed: ";
    cin >> k;

    // solve the problem
    double result = solveRopeCutting(ropes, k);

    // output the result with 6 digits after decimal
    cout << "maximum possible length: " << fixed << setprecision(6) << result << endl;

    return 0;
}

// final notes:

// summary of important points:
// - we used binary search because the function isGood(x) is monotonic
// - floating-point numbers require careful precision handling
// - complexity is O(n * log2(maxRope / eps))
// - we avoid infinite loops by limiting iterations and checking precision
// - we never compare doubles with == (use doubleOne - doubleTwo < eps)

// why floating-point problem arises:
// - real numbers are infinite and continuous
// - computers can only store a finite number of real values
// - double has limited precision (~15-17 digits)
// - rounding errors accumulate
// - small differences between numbers can disappear

// general case summary:
// - binary search works whenever a monotonic property exists
// - precision must be controlled for floating-point binary search
// - fixed number of iterations is a safe technique to ensure termination
