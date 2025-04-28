#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, target;
    cin >> n >> target;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    // the array is sorted in non-decreasing order
    // we are to find the min index in the array such that arr[index] >= target

    // we initialize
    long long left = -1; // we assume that arr[-1] < target
    long long right = n; // we assume that arr[n] >= target

    // we maintain the invariant
    // arr[left] < target
    // arr[right] >= target

    // at the end, we have right = left + 1
    // in this case, if right == n, then left = n - 1 and all the elements in the array are less than target
    // otherwise, right is the min index in the array such that arr[index] >= target

    while (right != left + 1) {
        const long long mid = left + (right - left) / 2;
        if (arr[mid]) {
            right = mid;
        } else {
            left = mid;
        }
    }

    if (right == n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }

    return EXIT_SUCCESS;
}
