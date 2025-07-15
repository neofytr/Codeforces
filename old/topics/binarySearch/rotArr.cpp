#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // arr is sorted but maybe rotated clockwise at some pivot (doesn't have duplicates)
    // the array is first increasing, then possibly decreases once, then increasing again

    int left = 0;
    int right = n - 1;

    // these invariants hold at the start of each iteration (after calculation of mid)
    // invariant: if the target exists, it is inside the interval [left, right]
    // invariant: at least one of the subarrays [left, mid] or [mid, right] is sorted (increasing)
    // this invariant holds initially because the entire array is considered at first

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            cout << mid << endl;
            return EXIT_SUCCESS;
        }

        if (arr[mid] >= arr[left]) {
            // [left, mid] is sorted because no rotation occurs between left and mid

            if (target >= arr[left] && target <= arr[mid]) {
                // target lies within [left, mid] because it is between arr[left] and arr[mid]
                // moving right to mid preserves the invariant that target ∈ [left, right]
                right = mid;
            } else {
                // target does not lie within [left, mid]
                // it must lie within [mid, right] if it exists
                // moving left to mid preserves the invariant
                left = mid;
            }
        } else {
            // [mid, right] is sorted because no rotation occurs between mid and right

            if (target >= arr[mid] && target <= arr[right]) {
                // target lies within [mid, right]
                // moving left to mid preserves the invariant
                left = mid;
            } else {
                // target does not lie within [mid, right]
                // it must lie within [left, mid] if it exists
                // moving right to mid preserves the invariant
                right = mid;
            }
        }

        // note: left or right is assigned to mid, not mid ± 1
        // this ensures that we do not accidentally skip the target if it lies at mid
    }

    // if we exit the loop, it means target was not found
    cout << -1 << endl;
    return EXIT_SUCCESS;
}
