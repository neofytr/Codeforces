#include <bits/stdc++.h>
using namespace std;

int searchLeeq(const vector<long long> &arr, const long long target) {
    // we are to find the maximum element in arr that is less than equal to target (if there are multiple such elements, we get the maximum index among them)
    // so the element next to this supposed element should be strictly greater than target

    int left = -1; // arr[left] <= target
    int right = static_cast<int>(arr.size()); // arr[right] > target

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            left = mid;
        } else {
            right = mid;
        }
    }

    return left;
}

int searchGreq(const vector<long long> &arr, const long long target) {
    // we are to find the minimum element in arr that is greater than equal to target (if there are multiple such, find the one with the min index)

    int left = -1; // arr[left] < target
    int right = arr.size(); // arr[right] >= target

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return right;
}


int main() {
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    sort(arr.begin(), arr.end()); // sort in ascending order
    int k;
    cin >> k;
    while (k--) {
        long long l, r;
        cin >> l >> r;

        // we are to find the number of values inside the arr between values l and r (BOTH INCLUSIVE)
        // we have to find the min index in the array with arr[index] >= l
        // we have to find the max index in the array with arr[index] <= r

        int left = searchGreq(arr, l);
        if (left == -1) {
            // all elements are less than l
            // we are done
            cout << 0 << endl;
        } else {
            // found the min index with arr[index] >= l
            int right = searchLeeq(arr, r);
            if (right == n) {
                // all elements are greater than r
                // we are done, no element
                cout << 0 << endl;
            } else {
                cout << right - left + 1 << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}
