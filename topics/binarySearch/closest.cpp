#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // we need to find the smallest element in arr that is greater than or equal to target
    // i.e., all the elements to the left of it are strictly less than
    // and all elements to its right (including itself) are greater than or equal to target
    // we maintain the following invariant
    // arr[left] < target
    // arr[right] >= target
    // we stop when right == left + 1
    // in this case, the element we are searching for is arr[right]
    // if there are no elements in the arr that are greater than or equal to the target, i.e, all
    // elements in the arr are smaller than target, then, right = n and left = n - 1

    int left = -1; // hypothetical element to the left of 0 that is less than target
    int right = n; // hypothetical element to the right of n - 1 that is greater than or equal to target
    int mid;
    while (left < right) {
        mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (right == n) {
        // such an element doesn't exist
        cout << "NO" << endl;
    } else {
        // such an element exists
        cout << "YES " << arr[right] << endl;
    }

    return EXIT_SUCCESS;
}
