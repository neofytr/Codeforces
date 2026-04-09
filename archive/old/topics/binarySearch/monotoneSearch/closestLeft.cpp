#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // the array is sorted in increasing order

    // we are to find the largest element in arr that is less than or equal to target (if there are multiple such elements, we get the one with the highest index)
    // we maintain the following invariant
    // arr[left] <= x
    // arr[right] > x
    // we stop when right = left + 1
    // in this case, the element we are searching for is left
    // if there are no elements in the array that are less than or equal to target, i.e, all elements in the
    // array are strictly greater than target, then, left = -1 and right = 0

    int left = -1; // hypothetical element to the left of 0 that is <= x
    int right = n; // hypothetical element to the right of n - 1 that is > x
    int mid;
    while (right != left + 1) {
        mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (left == -1) {
        // not found
        cout << "NO" << endl;
    } else {
        cout << "YES " << arr[left] << endl;
    }

    return EXIT_SUCCESS;
}
