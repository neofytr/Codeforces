#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, target;
    cin >> n >> target;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    // the array is sorted
    // we want to find the min index in the array such that arr[index] > target

    // we maintain the invariant
    // arr[left] <= target
    // arr[right] > target

    long long left = -1;
    long long right = n;

    while (right != left + 1) {
        const long long mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (right == n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }

    return EXIT_SUCCESS;
}
