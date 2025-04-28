#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // we are to find whether target exists in the array or not
    bool found = false;
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        const int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            found = true;
            break;
        }

        if (arr[mid] == arr[left] == arr[right]) {
            // undecidable which of the two subarrays is increasing
            left++;
            right--;
        } else if (arr[mid] >= arr[left]) {
            // [left, mid] is sorted
            if (target < arr[mid] && target >= arr[left]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            // [right, mid] is sorted
            if (target < arr[mid] && arr[right] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    if (found) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    // finding the min element in the array
    int mini = arr[0];
    left = 0;
    right = n - 1;

    while (left <= right) {
        const int mid = left + (right - left) / 2;

        if (arr[mid] == arr[left] == arr[right]) {
            mini = min(mini, arr[mid]);
            left++;
            right--;
        } else if (arr[mid] >= arr[left]) {
            // [left, mid] is increasing
            mini = min(mini, arr[left]);
            left = mid + 1;
        } else {
            // [mid, right] is increasing
            mini = min(mini, arr[mid]);
            right = mid - 1;
        }
    }

    cout << mini << endl;
    return EXIT_SUCCESS;
}
