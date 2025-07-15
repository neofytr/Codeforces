#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    int left = 0, right = n - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            found = true;
            break;
        }

        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            // cannot determine sorted side, shrink boundaries
            left++;
            right--;
        } else if (arr[left] <= arr[mid]) {
            // left to mid is sorted
            if (arr[left] <= target && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else {
            // mid to right is sorted
            if (arr[mid] < target && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    if (found)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
