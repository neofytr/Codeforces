#include <bits/stdc++.h>
using namespace std;

int search(const vector<long long> &arr, const long long target) {
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
        if (ans == -1) {
            cout << 0 << endl;
        } else {
            cout << ans + 1 << endl;
        }
    }

    return EXIT_SUCCESS;
}
