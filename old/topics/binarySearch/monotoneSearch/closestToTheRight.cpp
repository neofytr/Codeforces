#include <bits/stdc++.h>
using namespace std;

int search(const vector<long long> &arr, const long long target) {
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
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    long long target;
    while (k--) {
        cin >> target;
        int ans = search(arr, target);
        if (ans == n) {
            cout << 0 << endl;
        } else {
            cout << ans + 1 << endl;
        }
    }

    return EXIT_SUCCESS;
}
